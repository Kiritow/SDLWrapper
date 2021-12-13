#include "Color.h"

Color::Color() :r(0), g(0), b(0), a(0)
{
}

Color::Color(Uint8 R, Uint8 G, Uint8 B, Uint8 A) : r(R), g(G), b(B), a(A)
{
}

Color::Color(const SDL_PixelFormat& format, Uint8 R, Uint8 G, Uint8 B) : Color(SDL_MapRGB(&format, R, G, B))
{

}

Color::Color(const SDL_PixelFormat& format, Uint8 R, Uint8 G, Uint8 B, Uint8 A) : Color(SDL_MapRGBA(&format, R, G, B, A))
{

}

Color::Color(Uint32 pixel, const SDL_PixelFormat& format)
{
	SDL_GetRGBA(pixel, &format, &r, &g, &b, &a);
}

Color::Color(const SDL_Color& c) : r(c.r), g(c.g), b(c.b), a(c.a)
{
}

Color::Color(Uint32 rgba) : r((rgba >> 24) & 0xF), g((rgba >> 16) & 0xF), b((rgba >> 8) & 0xF), a(rgba & 0xF)
{
}

Color Color::operator*(double percent) const
{
	return Color(r * percent, g * percent, b * percent, a);
}

Color::operator SDL_Color() const
{
	return SDL_Color{ r, g, b, a };
}

Color::operator Uint32() const
{
	return r << 24 | g << 16 | b << 8 | a;
}

const Color Color::Black = Color(0, 0, 0, 255);
const Color Color::White = Color(255, 255, 255, 255);
const Color Color::Red = Color(255, 0, 0, 255);
const Color Color::Green = Color(0, 255, 0, 255);
const Color Color::Blue = Color(0, 0, 255, 255);
const Color Color::Yellow = Color(255, 255, 0, 255);
const Color Color::Cyan = Color(0, 255, 255, 255);
const Color Color::Magenta = Color(255, 0, 255, 255);
