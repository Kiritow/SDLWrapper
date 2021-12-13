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
	SDL_Color c = getColor();
	aalineRGBA(_sp.get(), x1, y1, x2, y2, c.r, c.g, c.b, c.a);
}

void Renderer::drawThickLine(int x1, int y1, int x2, int y2, Uint8 width)
{
	SDL_Color c = getColor();
	thickLineRGBA(_sp.get(), x1, y1, x2, y2, width, c.r, c.g, c.b, c.a);
}

void Renderer::drawPoint(int x, int y)
{
	SDL_RenderDrawPoint(_sp.get(), x, y);
}

void Renderer::drawRect(const SDL_Rect& r)
{
	SDL_RenderDrawRect(_sp.get(), &r);
}

void Renderer::drawRoundedRect(const SDL_Rect& r, int rad)
{
	SDL_Color c = getColor();
	roundedRectangleRGBA(_sp.get(), r.x, r.y, r.x + r.w, r.y + r.h, rad, c.r, c.g, c.b, c.a);
}

void Renderer::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	SDL_Color c = getColor();
	trigonRGBA(_sp.get(), x1, y1, x2, y2, x3, y3, c.r, c.g, c.b, c.a);
}

void Renderer::drawAATriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	SDL_Color c = getColor();
	aatrigonRGBA(_sp.get(), x1, y1, x2, y2, x3, y3, c.r, c.g, c.b, c.a);
}

void Renderer::drawPolygon(const Sint16* vx, const Sint16* vy, int n)
{
	SDL_Color c = getColor();
	polygonRGBA(_sp.get(), vx, vy, n, c.r, c.g, c.b, c.a);
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
	SDL_Color c = getColor();
	aapolygonRGBA(_sp.get(), vx, vy, n, c.r, c.g, c.b, c.a);
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

void Renderer::drawCircle(int x, int y, int rad)
{
	SDL_Color c = getColor();
	circleRGBA(_sp.get(), x, y, rad, c.r, c.g, c.b, c.a);
}

void Renderer::drawAACircle(int x, int y, int rad)
{
	SDL_Color c = getColor();
	aacircleRGBA(_sp.get(), x, y, rad, c.r, c.g, c.b, c.a);
}

void Renderer::drawArc(int x, int y, int rad, int start, int end)
{
	SDL_Color c = getColor();
	arcRGBA(_sp.get(), x, y, rad, start, end, c.r, c.g, c.b, c.a);
}

void Renderer::drawPie(int x, int y, int rad, int start, int end)
{
	SDL_Color c = getColor();
	pieRGBA(_sp.get(), x, y, rad, start, end, c.r, c.g, c.b, c.a);
}

void Renderer::drawEllipse(int x, int y, int rx, int ry)
{
	SDL_Color c = getColor();
	ellipseRGBA(_sp.get(), x, y, rx, ry, c.r, c.g, c.b, c.a);
}

void Renderer::drawAAEllipse(int x, int y, int rx, int ry)
{
	SDL_Color c = getColor();
	aaellipseRGBA(_sp.get(), x, y, rx, ry, c.r, c.g, c.b, c.a);
}

void Renderer::fillRect(const SDL_Rect& r)
{
	SDL_RenderFillRect(_sp.get(), &r);
}

void Renderer::fillRoundedRect(const SDL_Rect& r, int rad)
{
	SDL_Color c = getColor();
	roundedBoxRGBA(_sp.get(), r.x, r.y, r.x + r.w, r.y + r.h, rad, c.r, c.g, c.b, c.a);
}

void Renderer::fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	SDL_Color c = getColor();
	filledTrigonRGBA(_sp.get(), x1, y1, x2, y2, x3, y3, c.r, c.g, c.b, c.a);
}

void Renderer::fillPolygon(const Sint16* vx, const Sint16* vy, int n)
{
	SDL_Color c = getColor();
	filledPolygonRGBA(_sp.get(), vx, vy, n, c.r, c.g, c.b, c.a);
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

void Renderer::fillCircle(int x, int y, int rad)
{
	SDL_Color c = getColor();
	filledCircleRGBA(_sp.get(), x, y, rad, c.r, c.g, c.b, c.a);
}

void Renderer::fillEllipse(int x, int y, int rx, int ry)
{
	SDL_Color c = getColor();
	filledEllipseRGBA(_sp.get(), x, y, rx, ry, c.r, c.g, c.b, c.a);
}

void Renderer::fillPie(int x, int y, int rad, int start, int end)
{
	SDL_Color c = getColor();
	filledPieRGBA(_sp.get(), x, y, rad, start, end, c.r, c.g, c.b, c.a);
}

void Renderer::fillPolygonSurface(const Sint16* vx, const Sint16* vy, int n, const Surface& s, int dx, int dy)
{
	SDL_Color c = getColor();
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

SDL_Color Renderer::popColor()
{
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
