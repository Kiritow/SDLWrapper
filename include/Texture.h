#pragma once
#include "includes.h"

class Texture
{
public:
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _sp;
	operator bool() const;

	std::pair<int, int> getSize() const;
	SDL_Color getColorMod() const;
	void setColorMod(const SDL_Color& c);
	int getAlphaMod() const;
	void setAlphaMod(const int& alpha);
	SDL_BlendMode getBlendMode() const;
	void setBlendMode(const SDL_BlendMode& blend);
private:
	friend class Renderer;
	Texture(SDL_Texture*);
};
