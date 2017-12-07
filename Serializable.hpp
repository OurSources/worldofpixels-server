#pragma once

#include <cstddef>
#include <cstdint>

class Serializable {
public:
	virtual std::size_t size() = 0;
	virtual std::size_t serialize(std::uint8_t *) = 0;
};
