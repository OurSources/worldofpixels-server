#pragma once

#include <string>
#include <atomic>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <curl/curl.h>

class AsyncHTTPGETClient {
public:
	class Request {
	public:
		const std::string url;
		const std::string postFields;
		const std::function<void(const CURLcode, const std::string &)> callback;
		
		Request(const std::string & url, const std::string & postFields,
		        const std::function<void(const CURLcode, const std::string &)> callback);
	};
	
private:
	CURL * const curl;
	std::queue<Request> requestQueue;
	std::mutex queueLock;
	std::mutex waitLock;
	std::condition_variable cv;
	std::thread requestThread;
	std::atomic<bool> terminateThread;
	
public:
	AsyncHTTPGETClient();
	~AsyncHTTPGETClient();
	
	void queueRequest(const Request);
	
private:
	void processRequests();
};
