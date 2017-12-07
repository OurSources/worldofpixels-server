#pragma once

#include <unordered_map>
#include <memory>

class WorldManager {
	std::unordered_map<std::string, std::weak_ptr<World>> worlds;
	
public:
	WorldManager();
	
	std::shared_ptr<World> getWorld(std::string const &, bool createIfNonExistant = false);
};
