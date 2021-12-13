#pragma once
#include "includes.h"

class Rect
{
public:
	int x, y, w, h;

	Rect();
	Rect(int X, int Y, int W, int H);
	Rect(const SDL_Rect& r);

	bool intersect(const Rect& r, Rect& result) const;
	bool hasIntersect(const Rect& r) const;

	bool operator == (const Rect& r) const;
	bool empty() const;

	operator SDL_Rect() const;
};
