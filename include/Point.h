#pragma once
#include "includes.h"
#include "Rect.h"

class Point
{
public:
	int x, y;

	Point();
	Point(int X, int Y);
	Point(const SDL_Point& p);

	bool inRect(const Rect& r);

	operator SDL_Point() const;
};
