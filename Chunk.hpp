#pragma once

#include <Serializable.hpp>

#include <cstdint>
#include <cstddef>
#include <memory>

class Chunk : public Serializable {
public:
	static constexpr std::size_t areaSize = 256;
	using coord_t = std::int32_t;
	using key_t = std::uint64_t;
	
	class Pixel {
	public:
		std::uint16_t rgb;
		
		Pixel(std::uint8_t r, std::uint8_t g, std::uint8_t b);
		Pixel(std::uint16_t rgb);
		
		std::size_t writeToBuf(std::uint8_t *);
	};
	
	coord_t const x;
	coord_t const y;
	
private:
	std::uint16_t pixels[areaSize * areaSize];
	std::uint32_t compressedImageSize;
	std::unique_ptr<std::uint8_t[]> compressedImage;
	bool outdatedCompressedImage;
	
public:
	Chunk(coord_t x, coord_t y, Pixel color);
	
	bool setPixel(std::uint8_t x, std::uint8_t y, Pixel color);
	Pixel getPixel(std::uint8_t x, std::uint8_t y);
	
	virtual std::size_t size() override;
	virtual std::size_t serialize(std::uint8_t *) override;
	
	constexpr static key_t key(coord_t x, coord_t y);
	
private:
	void updateCompressedImage();
};
