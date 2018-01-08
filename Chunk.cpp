#include "Chunk.hpp"

#include <misc/pngencode.hpp>
#include <misc/BufferHelper.hpp>

#include <algorithm>
#include <limits>

Chunk::Pixel::Pixel(std::uint8_t r, std::uint8_t g, std::uint8_t b)
: rgb((b >> 3 & 0x1f)
	| (g >> 2 & 0x3f) << 5
	| (r >> 3 & 0x1f) << 11) { }

Chunk::Pixel::Pixel(std::uint16_t rgb)
: rgb(rgb) { }

Chunk::Chunk(Chunk::coord_t x, Chunk::coord_t y, Chunk::Pixel color)
: x(x),
  y(y),
  compressedImageSize(0),
  outdatedCompressedImage(true) {
	for (std::size_t i = 0; i < Chunk::areaSize * Chunk::areaSize; i++) {
		pixels[i] = color.rgb;
	}
}

bool Chunk::setPixel(std::uint8_t x, std::uint8_t y, Chunk::Pixel color) {
	if (pixels[y * Chunk::areaSize + x] != color.rgb) {
		outdatedCompressedImage = true;
		pixels[y * Chunk::areaSize + x] = color.rgb;
		return true;
	}
	return false;
}

Chunk::Pixel Chunk::getPixel(std::uint8_t x, std::uint8_t y) {
	return pixels[y * Chunk::areaSize + x];
}

std::size_t Chunk::size() {
	if (outdatedCompressedImage) {
		updateCompressedImage();
	}
	
	return sizeof(Chunk::coord_t) * 2 + compressedImageSize;
}

std::size_t Chunk::serialize(std::uint8_t * arr) {
	if (outdatedCompressedImage) { /* Should never really happen anyways */
		updateCompressedImage();
	}
	std::uint8_t * start = arr;
	
	arr += BufferHelper::writeLE(arr, x);
	arr += BufferHelper::writeLE(arr, y);
	std::copy_n(compressedImage.get(), compressedImageSize, arr);
	arr += compressedImageSize;
	
	return arr - start;
}

constexpr Chunk::key_t Chunk::key(Chunk::coord_t x, Chunk::coord_t y) {
	return (Chunk::key_t) x << (std::numeric_limits<Chunk::coord_t>::digits + 1) | y;
}

void Chunk::updateCompressedImage() {
	compressedImage = CompressPNG(&pixels, Chunk::areaSize, Chunk::areaSize, 2, compressedImageSize, 4);
	outdatedCompressedImage = false;
}
