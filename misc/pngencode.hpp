#pragma once

#include <cstdint>
#include <memory>

/* level = Z_DEFAULT_COMPRESSION */
std::unique_ptr<std::uint8_t[]> CompressPNG(void *img, int w, int h, int numchans, std::uint32_t &len_out, int level);
