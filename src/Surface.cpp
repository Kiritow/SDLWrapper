#include "Surface.h"
#include "SDL2/SDL2_rotozoom.h"

Surface::Surface(const std::string& filename) : sp(IMG_Load(filename.c_str()), SDL_FreeSurface)
{

}

Surface::Surface(const void* data, int size) : sp(IMG_Load_RW(SDL_RWFromConstMem(data, size), 1), SDL_FreeSurface)
{

}

Surface::Surface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
	: sp(SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask, Amask), SDL_FreeSurface)
{

}

Surface::Surface(Uint32 flags, int width, int height, int depth, Uint32 format) : sp(SDL_CreateRGBSurfaceWithFormat(flags, width, height, depth, format), SDL_FreeSurface)
{

}

Surface::Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
	: sp(SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask), SDL_FreeSurface)
{

}

Surface::Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 format) : sp(SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, depth, pitch, format), SDL_FreeSurface)
{

}

std::pair<int, int> Surface::getSize() const
{
	return std::make_pair(sp->w, sp->h);
}

Surface Surface::rotozoom(double angle, double zoom, bool smooth) const
{
	return Surface(rotozoomSurface(sp.get(), angle, zoom, smooth ? SMOOTHING_ON : SMOOTHING_OFF));
}

Surface Surface::rotozoom(double angle, double zoomX, double zoomY, bool smooth) const
{
	return Surface(rotozoomSurfaceXY(sp.get(), angle, zoomX, zoomY, smooth ? SMOOTHING_ON : SMOOTHING_OFF));
}

Surface Surface::zoom(double zoomX, double zoomY, bool smooth) const
{
	return Surface(zoomSurface(sp.get(), zoomX, zoomY, smooth ? SMOOTHING_ON : SMOOTHING_OFF));
}

Surface Surface::shrink(int factorX, int factorY) const
{
	return Surface(shrinkSurface(sp.get(), factorX, factorY));
}

Surface Surface::rotate90(int clockwiseTurns) const
{
	return Surface(rotateSurface90Degrees(sp.get(), clockwiseTurns));
}

std::pair<int, int> Surface::rotozoomSize(double angle, double zoom) const
{
	int w, h;
	rotozoomSurfaceSize(sp->w, sp->h, angle, zoom, &w, &h);
	return std::make_pair(w, h);
}

std::pair<int, int> Surface::rotozoomSize(double angle, double zoomX, double zoomY) const
{
	int w, h;
	rotozoomSurfaceSizeXY(sp->w, sp->h, angle, zoomX, zoomY, &w, &h);
	return std::make_pair(w, h);
}

std::pair<int, int> Surface::zoomSize(double zoomX, double zoomY) const
{
	int w, h;
	zoomSurfaceSize(sp->w, sp->h, zoomX, zoomY, &w, &h);
	return std::make_pair(w, h);
}

SDL_Rect Surface::copy(const Surface& s, const SDL_Rect& src, const SDL_Rect& dst)
{
	SDL_Rect tdst = dst;
	SDL_BlitSurface(s.sp.get(), &src, sp.get(), &tdst);
	return tdst;
}

SDL_Rect Surface::copyTo(const Surface& s, const SDL_Rect& dst)
{
	SDL_Rect tdst = dst;
	SDL_BlitSurface(s.sp.get(), NULL, sp.get(), &tdst);
	return tdst;
}

void Surface::copyFill(const Surface& s, const SDL_Rect& src)
{
	SDL_BlitSurface(s.sp.get(), &src, sp.get(), NULL);
}

void Surface::copyFullFill(const Surface& s)
{
	SDL_BlitSurface(s.sp.get(), NULL, sp.get(), NULL);
}

SDL_Rect Surface::copyScaled(const Surface& s, const SDL_Rect& src, const SDL_Rect& dst)
{
	SDL_Rect tdst = dst;
	SDL_BlitScaled(s.sp.get(), &src, sp.get(), &tdst);
	return tdst;
}

SDL_Rect Surface::copyToScaled(const Surface& s, const SDL_Rect& dst)
{
	SDL_Rect tdst = dst;
	SDL_BlitSurface(s.sp.get(), NULL, sp.get(), &tdst);
	return tdst;
}

void Surface::copyFillScaled(const Surface& s, const SDL_Rect& src)
{
	SDL_BlitSurface(s.sp.get(), &src, sp.get(), NULL);
}

void Surface::copyFullFillScaled(const Surface& s)
{
	SDL_BlitSurface(s.sp.get(), NULL, sp.get(), NULL);
}

void Surface::setColorKey(bool enable, Uint32 key)
{
	SDL_SetColorKey(sp.get(), enable, key);
}

Uint8 Surface::getAlphaMod() const
{
	Uint8 a;
	SDL_GetSurfaceAlphaMod(sp.get(), &a);
	return a;
}

void Surface::setAlphaMod(Uint8 a)
{
	SDL_SetSurfaceAlphaMod(sp.get(), a);
}

std::tuple<Uint8, Uint8, Uint8> Surface::getColorMod() const
{
	Uint8 r, g, b;
	SDL_GetSurfaceColorMod(sp.get(), &r, &g, &b);
	return std::make_tuple(r, g, b);
}

void Surface::setColorMod(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetSurfaceColorMod(sp.get(), r, g, b);
}

SDL_BlendMode Surface::getBlendMode() const
{
	SDL_BlendMode blend;
	SDL_GetSurfaceBlendMode(sp.get(), &blend);
	return blend;
}

void Surface::setBlendMode(SDL_BlendMode blend) const
{
	SDL_SetSurfaceBlendMode(sp.get(), blend);
}

Uint32 Surface::getColorKey() const
{
	Uint32 key;
	SDL_GetColorKey(sp.get(), &key);
	return key;
}

Surface::Surface(SDL_Surface* surf) : sp(surf, SDL_FreeSurface)
{

}
