#pragma once

#include <Serializable.hpp>

#include <uWS.h>
#include <cstdint>

class Player : public Serializable {
public:
	using coord_t = std::int32_t; /* Player (mouse) absolute coordinate */
	
private:
	NetworkState state;
	
	/*coord_t x;
	coord_t y;
	coord_t sentX;
	coord_t sentY;*/
	
public:
	Player();
};
