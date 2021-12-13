#include "Point.h"

Point::Point() : x(0), y(0)
{

}

Point::Point(int X, int Y) : x(X), y(Y)
{

}

Point::Point(const SDL_Point& p) : x(p.x), y(p.y)
{

}

bool Point::inRect(const Rect& r)
{
	auto sp = (SDL_Point)*this;
	auto sr = (SDL_Rect)r;
	return SDL_PointInRect(&sp, &sr);
}

Point::operator SDL_Point() const
{
	return SDL_Point{ x, y };
}
