#pragma once
#include "includes.h"

class Color
{
public:
	uint8_t r, g, b, a;
	
	Color();
	Color(Uint8 R, Uint8 G, Uint8 B, Uint8 A);
	Color(const SDL_PixelFormat& format, Uint8 R, Uint8 G, Uint8 B);
	Color(const SDL_PixelFormat& format, Uint8 R, Uint8 G, Uint8 B, Uint8 A);
	Color(Uint32 pixel, const SDL_PixelFormat& format);
	Color(const SDL_Color& c);
	Color(Uint32 rgba);

	Color operator * (double percent) const;
	
	operator SDL_Color () const;
	operator Uint32 () const;

	static const Color Black, White, Red, Green, Blue, Yellow, Cyan, Magenta;
};
