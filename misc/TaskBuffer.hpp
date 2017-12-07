#pragma once

#include <functional>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <atomic>

class TaskBuffer {
	std::thread worker;
	std::atomic_flag shouldRun;
	std::condition_variable cv;
	std::mutex cvLock;
	std::mutex aTaskLock; /* For async tasks */
	std::mutex dTaskLock; /* For deferred tasks */
	std::vector<std::function<void(TaskBuffer &)>> asyncTasks; /* Expensive functions (run on another thread) */
	std::vector<std::function<void(TaskBuffer &)>> deferredTasks; /* Cheap functions (run when calling 'runDeferredTasks') */
	
public:
	TaskBuffer();
	~TaskBuffer();
	
	void runDeferredTasks();
	
	/* Thread safe */
	void async(std::function<void(TaskBuffer &)> &&);
	void defer(std::function<void(TaskBuffer &)> &&);
	
private:
	void executeTasks();
};
