#pragma once

#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <curl/curl.h>

class AsyncHTTPPOSTClient {
	CURL * const curl;
	std::thread requestThread;
	
public:
	class Request {
	public:
		std::string url;
		std::string postFields;
		
		Request(const std::string & url, const std::string & postFields);
	};
	
	AsyncHTTPPOSTClient();
	~AsyncHTTPPOSTClient();
	
	void queueRequest(const Request, const std::function<void(CURLcode)> callback);
};
