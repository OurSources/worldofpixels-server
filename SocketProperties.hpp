#pragma once

#include <memory>
#include <uWS.h>

class SocketProperties {  
	uWS::WebSocket<uWS::SERVER> * ws;
	bool connected;
	std::shared_ptr<void> userData;

public:
	uWS::WebSocket<uWS::SERVER> * getWs();
	bool isConnected();
	void * getUserData();
	void setUserData(void *);
};
