#include "TaskBuffer.hpp"

TaskBuffer::TaskBuffer() {
	//shouldRun = ATOMIC_FLAG_INIT;
	shouldRun.clear();
	shouldRun.test_and_set();
	worker = std::thread([this] { executeTasks(); });
}

TaskBuffer::~TaskBuffer() {
	shouldRun.clear();
	cv.notify_all();
	worker.join();
}

void TaskBuffer::runDeferredTasks() {
	/* .empty() is not thread safe, but this is the only
	 * function where items are removed from the queue.
	 */
	if (deferredTasks.empty()) {
		return; /* Avoid locking the mutex */
	}
	
	std::vector<std::function<void(TaskBuffer &)>> tasks;
	{
		std::lock_guard<std::mutex> lk(dTaskLock);
		std::swap(tasks, deferredTasks);
	}
	for (auto & func : tasks) {
		func(*this);
	}
}

void TaskBuffer::executeTasks() {
	std::unique_lock<std::mutex> uLock(cvLock);
	do {
		if (!asyncTasks.empty()) {
			std::vector<std::function<void(TaskBuffer &)>> tasks;
			{
				std::lock_guard<std::mutex> lk(aTaskLock);
				std::swap(tasks, asyncTasks);
			}
			for (auto & func : tasks) {
				func(*this);
			}
		} else {
			/* Only wait if the vector is empty */
			cv.wait(uLock);
		}
	} while (shouldRun.test_and_set());
}

void TaskBuffer::defer(std::function<void(TaskBuffer &)> && func) {
	std::lock_guard<std::mutex> lk(dTaskLock);
	deferredTasks.push_back(std::move(func));
}

void TaskBuffer::async(std::function<void(TaskBuffer &)> && func) {
	std::lock_guard<std::mutex> lk(aTaskLock);
	asyncTasks.push_back(std::move(func));
	cv.notify_one();
}
