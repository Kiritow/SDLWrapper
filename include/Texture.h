#pragma once
#include "includes.h"

class Texture
{
public:
	std::shared_ptr<SDL_Texture> sp;
	std::pair<int, int> getSize() const;

	Texture() = default;

	SDL_Color getColor() const;
	void setColor(const SDL_Color& c);
	int getAlpha() const;
	void setAlpha(const int& alpha);
	SDL_BlendMode getBlendMode() const;
	void setBlendMode(const SDL_BlendMode& blend);
private:
	friend class Renderer;
	Texture(SDL_Texture*);
};
