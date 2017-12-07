#pragma once

#include <Chunk.hpp>

#include <unordered_map>
#include <type_traits>
#include <cstdint>
#include <string>

class World {
public:
	using pxcoord_t = std::int32_t; /* Represents an absolute (pixel) coordinate */
	
	static constexpr pxcoord_t worldBorder = 0xFFFFFF;
	
private:
	std::string const name;
	std::unordered_map<Chunk::key_t, Chunk> chunks;
	//std::unordered_map<>
	
public:
	World(World const &) = delete;
	World(std::string const & name);
	World(std::string && name);
};
