#include "Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0)
{

}

Rect::Rect(int X, int Y, int W, int H) : x(X), y(Y), w(W), h(H)
{

}

Rect::Rect(const SDL_Rect& r) : Rect(r.x, r.y, r.w, r.h)
{

}

bool Rect::intersect(const Rect& r, Rect& result) const
{
	SDL_Rect a = *this, b = r, c;
	bool ret = SDL_IntersectRect(&a, &b, &c);
	result = c;
	return ret;
}

bool Rect::hasIntersect(const Rect& r) const
{
	SDL_Rect a = *this, b = r;
	return SDL_HasIntersection(&a, &b);
}

bool Rect::operator==(const Rect& r) const
{
	SDL_Rect a = *this, b = r;
	return SDL_RectEquals(&a, &b);
}

bool Rect::empty() const
{
	SDL_Rect a = *this;
	return SDL_RectEmpty(&a);
}

Rect::operator SDL_Rect() const
{
	return SDL_Rect{ x, y, w, h };
}


