#pragma once

#include <cstddef>
#include <cstdint>

class BufferHelper {
public:
	/* Writes any integer to a buffer in little endian order, returns sizeof(any_int) */
	template <typename any_int>
	static std::size_t writeLE(std::uint8_t *, any_int);
	
	template <typename any_int>
	static std::size_t writeBE(std::uint8_t *, any_int);
	
	
	/* Reads any int from a buffer with little/big endian order (converts to host endianness) */
	template <typename any_int>
	static any_int readLE(std::uint8_t *);
	
	template <typename any_int>
	static any_int readBE(std::uint8_t *);
};
