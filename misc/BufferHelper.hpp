#pragma once

#include <cstddef>
#include <cstdint>

namespace BufferHelper {
	/* Writes any integer to a buffer in little/big endian order, returns sizeof(Number) */
	template <typename Number>
	std::size_t writeLE(std::uint8_t *, Number) noexcept;
	
	template <typename Number>
	std::size_t writeBE(std::uint8_t *, Number) noexcept;
	
	
	/* Reads any int from a buffer with little/big endian order (converts to host endianness) */
	template <typename Number>
	Number readLE(std::uint8_t *) noexcept;
	
	template <typename Number>
	Number readBE(std::uint8_t *) noexcept;
};

#include "BufferHelper.tpp"
