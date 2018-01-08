#include "pngencode.hpp"
#include <algorithm>
#include <byteswap.h>
#include <zlib.h>

// by alex evans, 2011.  released into the public domain.
// based on a first ever reading of the png spec, it occurs to me that a minimal png encoder should be quite simple.
// this is a first stab - may be buggy! the only external dependency is zlib and some basic typedefs (u32, u8)
//
// VERSION 0.02! now using zlib's crc rather than my own, and avoiding a memcpy and memory scribbler in the old one
// by passing the zero byte at the start of the scanline to zlib first, then the original scanline in place. WIN!
//
// more context at http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
//
// follow me on twitter @mmalex http://twitter.com/mmalex
//
// Modified to accept compression level, and return a unique_ptr
using u8 = std::uint8_t;
using u32 = std::uint32_t;

std::unique_ptr<u8[]> CompressPNG(void *img, int w, int h, int numchans, u32 &len_out, int level = Z_DEFAULT_COMPRESSION) {
	int p = w * numchans;
	z_stream z = {0};
	if (deflateInit(&z, level) != Z_OK) {
		return {};
	}
	u8 *zbuf = new u8[57 + (z.avail_out = deflateBound(&z, (1 + p) * h)) + 1];
	z.next_out = zbuf + 41;
	for (int y = 0; y < h; ++y) {
		Bytef zero = 0;
		z.avail_in = 1;
		z.next_in = &zero;
		deflate(&z, Z_NO_FLUSH);
		
		z.avail_in = p;
		z.next_in = ((Bytef*)img) + y * p;
		deflate(&z, (y == h - 1) ? Z_FINISH : Z_NO_FLUSH);
	}
	len_out = z.next_out - zbuf - 41;
	{
		static const u8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};
		u8 pnghdr[41] = {
			0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,
			0x00,0x00,0x00,0x0d,
			0x49,0x48,0x44,0x52,0,0,(u8)(w>>8),(u8)w,0,0,(u8)(h>>8),(u8)h,8,chans[numchans],0,0,0,
			0,0,0,0, // crc
			(u8)(len_out>>24),(u8)(len_out>>16),(u8)(len_out>>8),(u8)len_out,
			0x49,0x44,0x41,0x54
		};
		*(u32*)(pnghdr + 29) = bswap_32(crc32(0, pnghdr + 12, 17));
		std::copy_n(pnghdr, 41, zbuf);
	}
	static const char pngFooter[] = "\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82";
	std::copy_n(pngFooter, sizeof(pngFooter), z.next_out);
	*(u32*)z.next_out = bswap_32(crc32(0, zbuf + 41 - 4, len_out + 4));
	deflateEnd(&z);
	len_out += 57;
	
	return std::unique_ptr<u8[]>(zbuf);
}
