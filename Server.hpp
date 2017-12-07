#pragma once

#include <cstdint>

class Server {
	std::string const baseDirectory;
	std::uint32_t playerCount;
	std::uint16_t const port;
	
public:
	Server(std::uint16_t port, std::string baseDir);
	
	void run();
};
