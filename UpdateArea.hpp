#pragma once

#include <Chunk.hpp>
#include <World.hpp>

#include <cstdint>
#include <unordered_map>
#include <unordered_set>

class UpdateArea {
public:
	/* Update areas must be chunk-aligned */
	static constexpr std::size_t areaSize = Chunk::areaSize * 16;
	using coord_t = std::int32_t;
	using rpxcoord_t = std::uint16_t; /* Relative pixel coordinate to the update area position. */
	using dpxcoord_t = std::int8_t; /* Delta for mouse move updates */
	
	coord_t const x;
	coord_t const y;
	
private:
	std::unordered_set<Player *> registeredPlayers;
	std::unordered_set<Player *> playersInside;
	
	std::unordered_map<rpxcoord_t, Chunk::Pixel> pixelUpdates;
	std::unordered_set<Player *> playerUpdates;
	
public:
	UpdateArea(UpdateArea const &) = delete;
	UpdateArea(coord_t x, coord_t y);
	
	void sendUpdates();
	void sendPlayerList(Player *);
	
	void pixelUpdated(World::pxcoord_t x, World::pxcoord_t y, Chunk::Pixel);
	void playerMoved(Player *);
	
	void unregisterPlayer(Player *);
	void registerPlayer(Player *);
};
