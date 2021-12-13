#pragma once
#include "includes.h"
#include "Surface.h"
#include "Texture.h"
#include <vector>
#include <stack>

class Renderer
{
public:
	std::shared_ptr<SDL_Renderer> _sp;
	std::stack<SDL_Color> _storedColors;

	Renderer() = default;

	Texture load(const std::string& filename);
	Texture load(const void* data, int size);
	Texture render(const Surface& surf);

	void clear();
	void present();

	void copy(const Texture& t, const SDL_Rect& src, const SDL_Rect& dst);
	void copyTo(const Texture& t, const SDL_Point& lu);
	void copyTo(const Texture& t, const SDL_Rect& dst);
	void copyFill(const Texture& t, const SDL_Rect& src);
	void copyFullFill(const Texture& t);

	void drawLine(int x1, int y1, int x2, int y2);
	void drawAALine(int x1, int y1, int x2, int y2);
	void drawThickLine(int x1, int y1, int x2, int y2, Uint8 width);
	void drawPoint(int x, int y);
	void drawRect(const SDL_Rect& r);
	void drawRoundedRect(const SDL_Rect& r, int rad);
	void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
	void drawAATriangle(int x1, int y1, int x2, int y2, int x3, int y3);
	void drawPolygon(const Sint16* vx, const Sint16* vy, int n);
	void drawPolygon(const SDL_Point* v, int n);
	void drawPolygon(const std::vector<SDL_Point>& vec);
	void drawAAPolygon(const Sint16* vx, const Sint16* vy, int n);
	void drawAAPolygon(const SDL_Point* v, int n);
	void drawAAPolygon(const std::vector<SDL_Point>& vec);
	void drawCircle(int x, int y, int rad);
	void drawAACircle(int x, int y, int rad);
	void drawArc(int x, int y, int rad, int start, int end);
	void drawPie(int x, int y, int rad, int start, int end);
	void drawEllipse(int x, int y, int rx, int ry);
	void drawAAEllipse(int x, int y, int rx, int ry);

	void fillRect(const SDL_Rect& r);
	void fillRoundedRect(const SDL_Rect& r, int rad);
	void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
	void fillPolygon(const Sint16* vx, const Sint16* vy, int n);
	void fillPolygon(const SDL_Point* v, int n);
	void fillPolygon(const std::vector<SDL_Point>& vec);
	void fillCircle(int x, int y, int rad);
	void fillEllipse(int x, int y, int rx, int ry);
	void fillPie(int x, int y, int rad, int start, int end);
	
	void fillPolygonSurface(const Sint16* vx, const Sint16* vy, int n, const Surface& s, int dx, int dy);
	void fillPolygonSurface(const SDL_Point* v, int n, const Surface& s, int dx, int dy);
	void fillPolygonSurface(const std::vector<SDL_Point>& vec, const Surface& s, int dx, int dy);
	void fillPolygonSurface(const std::vector<SDL_Point>& vec, const Surface& s, const SDL_Point& lup);

	SDL_Color getColor() const;
	void setColor(const SDL_Color& c);
	SDL_Color pushColor(const SDL_Color& c);
	SDL_Color popColor();

	SDL_BlendMode getBlendMode() const;
	void setBlendMode(const SDL_BlendMode& blend);

	void setTarget(Texture& t);
	void setTarget();

private: 
	friend class Window;
	Renderer(SDL_Renderer* rnd);
};
