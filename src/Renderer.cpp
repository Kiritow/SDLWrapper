#include "Renderer.h"
#include "Color.h"
#include <SDL2/SDL2_gfxPrimitives.h>

Texture Renderer::load(const std::string& filename)
{
	return Texture(IMG_LoadTexture(_sp.get(), filename.c_str()));
}

Texture Renderer::load(const void* data, int size)
{
	return Texture(IMG_LoadTexture_RW(_sp.get(), SDL_RWFromConstMem(data, size), 1));
}

Texture Renderer::render(const Surface& surf)
{
	return Texture(SDL_CreateTextureFromSurface(_sp.get(), surf.sp.get()));
}

void Renderer::clear()
{
	SDL_RenderClear(_sp.get());
}

void Renderer::present()
{
	SDL_RenderPresent(_sp.get());
}

void Renderer::copy(const Texture& t, const SDL_Rect& src, const SDL_Rect& dst)
{
	SDL_RenderCopy(_sp.get(), t.sp.get(), &src, &dst);
}

void Renderer::copyTo(const Texture& t, const SDL_Point& lu)
{
	SDL_Rect dst{ lu.x, lu.y, 0, 0 };
	std::tie(dst.w, dst.h) = t.getSize();
	SDL_RenderCopy(_sp.get(), t.sp.get(), NULL, &dst);
}

void Renderer::copyTo(const Texture& t, const SDL_Rect& dst)
{
	SDL_RenderCopy(_sp.get(), t.sp.get(), NULL, &dst);
}

void Renderer::copyFill(const Texture& t, const SDL_Rect& src)
{
	SDL_RenderCopy(_sp.get(), t.sp.get(), &src, NULL);
}

void Renderer::copyFullFill(const Texture& t)
{
	SDL_RenderCopy(_sp.get(), t.sp.get(), NULL, NULL);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(_sp.get(), x1, y1, x2, y2);
}

void Renderer::drawAALine(int x1, int y1, int x2, int y2)
{
	aalineRGBA(_sp.get(), x1, y1, x2, y2, 0, 0, 0, 0);
}

void Renderer::drawThickLine(int x1, int y1, int x2, int y2, Uint8 width)
{
	thickLineRGBA(_sp.get(), x1, y1, x2, y2, width, 0, 0, 0, 0);
}

void Renderer::drawPoint(int x, int y)
{
	SDL_RenderDrawPoint(_sp.get(), x, y);
}

void Renderer::drawRect(const SDL_Rect& r)
{
	SDL_RenderDrawRect(_sp.get(), &r);
}

void Renderer::drawRoundedRect(const SDL_Rect& r, int radius)
{
	roundedRectangleRGBA(_sp.get(), r.x, r.y, r.x + r.w, r.y + r.h, radius, 0, 0, 0, 0);
}

void Renderer::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	trigonRGBA(_sp.get(), x1, y1, x2, y2, x3, y3, 0, 0, 0, 0);
}

void Renderer::drawAATriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	aatrigonRGBA(_sp.get(), x1, y1, x2, y2, x3, y3, 0, 0, 0, 0);
}

void Renderer::drawPolygon(const Sint16* vx, const Sint16* vy, int n)
{
	polygonRGBA(_sp.get(), vx, vy, n, 0, 0, 0, 0);
}

void Renderer::drawPolygon(const SDL_Point* v, int n)
{
	std::vector<Sint16> vx(n);
	std::vector<Sint16> vy(n);
	for (int i = 0; i < n; i++)
	{
		vx[i] = v[i].x;
		vy[i] = v[i].y;
	}
	drawPolygon(vx.data(), vy.data(), n);
}

void Renderer::drawPolygon(const std::vector<SDL_Point>& vec)
{
	drawPolygon(vec.data(), vec.size());
}

void Renderer::drawAAPolygon(const Sint16* vx, const Sint16* vy, int n)
{
	aapolygonRGBA(_sp.get(), vx, vy, n, 0, 0, 0, 0);
}

void Renderer::drawAAPolygon(const SDL_Point* v, int n)
{
	std::vector<Sint16> vx(n);
	std::vector<Sint16> vy(n);
	for (int i = 0; i < n; i++)
	{
		vx[i] = v[i].x;
		vy[i] = v[i].y;
	}
	drawAAPolygon(vx.data(), vy.data(), n);
}

void Renderer::drawAAPolygon(const std::vector<SDL_Point>& vec)
{
	drawAAPolygon(vec.data(), vec.size());
}

void Renderer::drawCircle(int x, int y, int radius)
{
	circleRGBA(_sp.get(), x, y, radius, 0, 0, 0, 0);
}

void Renderer::drawAACircle(int x, int y, int radius)
{
	aacircleRGBA(_sp.get(), x, y, radius, 0, 0, 0, 0);
}

void Renderer::drawArc(int x, int y, int radius, int start, int end)
{
	arcRGBA(_sp.get(), x, y, radius, start, end, 0, 0, 0, 0);
}

void Renderer::drawPie(int x, int y, int radius, int start, int end)
{
	pieRGBA(_sp.get(), x, y, radius, start, end, 0, 0, 0, 0);
}

void Renderer::drawEllipse(int x, int y, int rx, int ry)
{
	ellipseRGBA(_sp.get(), x, y, rx, ry, 0, 0, 0, 0);
}

void Renderer::drawAAEllipse(int x, int y, int rx, int ry)
{
	aaellipseRGBA(_sp.get(), x, y, rx, ry, 0, 0, 0, 0);
}

void Renderer::fillRect(const SDL_Rect& r)
{
	SDL_RenderFillRect(_sp.get(), &r);
}

void Renderer::fillRoundedRect(const SDL_Rect& r, int radius)
{
	roundedBoxRGBA(_sp.get(), r.x, r.y, r.x + r.w, r.y + r.h, radius, 0, 0, 0, 0);
}

void Renderer::fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	filledTrigonRGBA(_sp.get(), x1, y1, x2, y2, x3, y3, 0, 0, 0, 0);
}

void Renderer::fillPolygon(const Sint16* vx, const Sint16* vy, int n)
{
	filledPolygonRGBA(_sp.get(), vx, vy, n, 0, 0, 0, 0);
}

void Renderer::fillPolygon(const SDL_Point* v, int n)
{
	std::vector<Sint16> vx(n);
	std::vector<Sint16> vy(n);
	for (int i = 0; i < n; i++)
	{
		vx[i] = v[i].x;
		vy[i] = v[i].y;
	}
	fillPolygon(vx.data(), vy.data(), n);
}

void Renderer::fillPolygon(const std::vector<SDL_Point>& vec)
{
	fillPolygon(vec.data(), vec.size());
}

void Renderer::fillCircle(int x, int y, int radius)
{
	filledCircleRGBA(_sp.get(), x, y, radius, 0, 0, 0, 0);
}

void Renderer::fillEllipse(int x, int y, int rx, int ry)
{
	filledEllipseRGBA(_sp.get(), x, y, rx, ry, 0, 0, 0, 0);
}

void Renderer::fillPie(int x, int y, int radius, int start, int end)
{
	filledPieRGBA(_sp.get(), x, y, radius, start, end, 0, 0, 0, 0);
}

void Renderer::fillPolygonSurface(const Sint16* vx, const Sint16* vy, int n, const Surface& s, int dx, int dy)
{
	texturedPolygon(_sp.get(), vx, vy, n, s.sp.get(), dx, dy);
}

void Renderer::fillPolygonSurface(const SDL_Point* v, int n, const Surface& s, int dx, int dy)
{
	std::vector<Sint16> vx(n);
	std::vector<Sint16> vy(n);
	for (int i = 0; i < n; i++)
	{
		vx[i] = v[i].x;
		vy[i] = v[i].y;
	}
	fillPolygonSurface(vx.data(), vy.data(), n, s, dx, dy);
}

void Renderer::fillPolygonSurface(const std::vector<SDL_Point>& vec, const Surface& s, int dx, int dy)
{
	fillPolygonSurface(vec.data(), vec.size(), s, dx, dy);
}

void Renderer::fillPolygonSurface(const std::vector<SDL_Point>& vec, const Surface& s, const SDL_Point& lup)
{
	int w, h;
	std::tie(w, h) = s.getSize();
	fillPolygonSurface(vec, s, w - lup.x, lup.y);
}

SDL_Color Renderer::getColor() const
{
	SDL_Color c;
	SDL_GetRenderDrawColor(_sp.get(), &c.r, &c.g, &c.b, &c.a);
	return c;
}

void Renderer::setColor(const SDL_Color& c)
{
	SDL_SetRenderDrawColor(_sp.get(), c.r, c.g, c.b, c.a);
}

SDL_Color Renderer::pushColor(const SDL_Color& c)
{
	auto old = getColor();
	setColor(c);
	_storedColors.push(old);
	return old;
}

SDL_Color Renderer::popColor(int n)
{
	for (int i = 1; i < n; i++) _storedColors.pop();
	auto c = _storedColors.top();
	_storedColors.pop();
	setColor(c);
	return c;
}

SDL_BlendMode Renderer::getBlendMode() const
{
	SDL_BlendMode blend;
	SDL_GetRenderDrawBlendMode(_sp.get(), &blend);
	return blend;
}

void Renderer::setBlendMode(const SDL_BlendMode& blend)
{
	SDL_SetRenderDrawBlendMode(_sp.get(), blend);
}

void Renderer::setTarget(Texture& t)
{
	SDL_SetRenderTarget(_sp.get(), t.sp.get());
}

void Renderer::setTarget()
{
	SDL_SetRenderTarget(_sp.get(), NULL);
}

Renderer::Renderer(SDL_Renderer* rnd) : _sp(rnd, SDL_DestroyRenderer)
{
	
}
