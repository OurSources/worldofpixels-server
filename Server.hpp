#pragma once

#include <cstdint>
#include <string>
#include <uWS.h>

#include <SocketProperties.hpp>

class Server {
	std::string const baseDirectory;
	std::uint32_t playerCount;
	std::uint16_t const port;
	uWS::Hub hub;
	
public:
	Server(std::uint16_t port, std::string baseDir);
	
	void socketConnected(SocketProperties &);
	void socketDisconnected(SocketProperties &);

	void run();
};
