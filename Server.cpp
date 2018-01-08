#include "Server.hpp"

Server::Server(std::uint16_t port, std::string baseDir)
: baseDirectory(baseDir),
  playerCount(0),
  port(port),
  hub(uWS::PERMESSAGE_DEFLATE | uWS::NO_DELAY, false, 1) {
	
}