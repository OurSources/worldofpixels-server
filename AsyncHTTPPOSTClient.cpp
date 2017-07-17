#include "AsyncHTTPPOSTClient.hpp"

#include <stdexcept>

AsyncHTTPPOSTClient::Request::Request(const std::string & url, const std::string & postFields)
: url(url),
  postFields(postFields) { }

AsyncHTTPPOSTClient::AsyncHTTPPOSTClient()
: curl(curl_easy_init()) {
	/* Nothing should happen if it's called two times, right...? */
	/*curl_global_init(CURL_GLOBAL_DEFAULT);*/
	if (!curl) {
		throw std::runtime_error("Couldn't initialize libCURL!");
	}
}

AsyncHTTPPOSTClient::~AsyncHTTPPOSTClient() {
	if (curl) {
		curl_easy_cleanup(curl);
	}
	/* Hmm, how should I fix this... */
	/* curl_global_cleanup(); */
}

void AsyncHTTPPOSTClient::queueRequest(const AsyncHTTPPOSTClient::Request req,
                                       const std::function<void(CURLcode)> callback) {
	
}
