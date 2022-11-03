#pragma once
#include "includes.h"

class Surface
{
public:
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> sp;

	Surface(const std::string& filename);
	Surface(const void* data, int size);
	Surface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
	Surface(Uint32 flags, int width, int height, int depth, Uint32 format);
	Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
	Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 format);

	std::pair<int, int> getSize() const;

	Surface rotozoom(double angle, double zoom, bool smooth) const;
	Surface rotozoom(double angle, double zoomX, double zoomY, bool smooth) const;
	Surface zoom(double zoomX, double zoomY, bool smooth) const;
	Surface shrink(int factorX, int factorY) const;
	Surface rotate90(int clockwiseTurns) const;

	std::pair<int, int> rotozoomSize(double angle, double zoom) const;
	std::pair<int, int> rotozoomSize(double angle, double zoomX, double zoomY) const;
	std::pair<int, int> zoomSize(double zoomX, double zoomY) const;

	SDL_Rect copy(const Surface& s, const SDL_Rect& src, const SDL_Rect& dst);
	SDL_Rect copyTo(const Surface& s, const SDL_Rect& dst);
	void copyFill(const Surface& s, const SDL_Rect& src);
	void copyFullFill(const Surface& s);
	SDL_Rect copyScaled(const Surface& s, const SDL_Rect& src, const SDL_Rect& dst);
	SDL_Rect copyToScaled(const Surface& s, const SDL_Rect& dst);
	void copyFillScaled(const Surface& s, const SDL_Rect& src);
	void copyFullFillScaled(const Surface& s);

	Uint32 getColorKey() const;
	void setColorKey(bool enable, Uint32 key);

	Uint8 getAlphaMod() const;
	void setAlphaMod(Uint8 a);
	std::tuple<Uint8, Uint8, Uint8> getColorMod() const;
	void setColorMod(Uint8 r, Uint8 g, Uint8 b);
	SDL_BlendMode getBlendMode() const;
	void setBlendMode(SDL_BlendMode blend) const;

private:
	friend class Font;
	Surface(SDL_Surface* surf);
};
