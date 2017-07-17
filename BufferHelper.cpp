#include "BufferHelper.hpp"

#include <cstring>
#include <byteswap.h>

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ && __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
	#error "Endianness not supported!"
#endif

template <typename any_int>
std::size_t BufferHelper::writeLE(std::uint8_t * const buf, const any_int integer) {
	any_int finalbytes;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	finalbytes = integer;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	switch (sizeof(any_int)) {
	case 1:
		finalbytes = integer;
		break;
	case 2:
		finalbytes = bswap_16(integer);
		break;
	case 4:
		finalbytes = bswap_32(integer);
		break;
	case 8:
		finalbytes = bswap_64(integer);
		break;
	}
#endif
	std::memcpy(buf, &finalbytes, sizeof(any_int));
	return sizeof(any_int);
}

template <typename any_int>
std::size_t BufferHelper::writeBE(std::uint8_t * const buf, const any_int integer) {
	any_int finalbytes;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	switch (sizeof(any_int)) {
	case 1:
		finalbytes = integer;
		break;
	case 2:
		finalbytes = bswap_16(integer);
		break;
	case 4:
		finalbytes = bswap_32(integer);
		break;
	case 8:
		finalbytes = bswap_64(integer);
		break;
	}
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	finalbytes = integer;
#endif
	std::memcpy(buf, &finalbytes, sizeof(any_int));
	return sizeof(any_int);
}


template <typename any_int>
any_int BufferHelper::readLE(std::uint8_t * const buf) {
	any_int finalbytes;
	std::memcpy(&finalbytes, buf, sizeof(any_int));
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	switch (sizeof(any_int)) {
	case 2:
		finalbytes = bswap_16(finalbytes);
		break;
	case 4:
		finalbytes = bswap_32(finalbytes);
		break;
	case 8:
		finalbytes = bswap_64(finalbytes);
		break;
	}
#endif
	return finalbytes;
}

template <typename any_int>
any_int BufferHelper::readBE(std::uint8_t * const buf) {
	any_int finalbytes;
	std::memcpy(&finalbytes, buf, sizeof(any_int));
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	switch (sizeof(any_int)) {
	case 2:
		finalbytes = bswap_16(finalbytes);
		break;
	case 4:
		finalbytes = bswap_32(finalbytes);
		break;
	case 8:
		finalbytes = bswap_64(finalbytes);
		break;
	}
#endif
	return finalbytes;
}
