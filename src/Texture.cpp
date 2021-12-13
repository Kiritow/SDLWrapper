#include "Texture.h"

std::pair<int, int> Texture::getSize() const
{
	int w, h;
	SDL_QueryTexture(sp.get(), NULL, NULL, &w, &h);
	return std::make_pair(w, h);
}

SDL_Color Texture::getColor() const
{
	SDL_Color c;
	c.a = -1;
	SDL_GetTextureColorMod(sp.get(), &c.r, &c.g, &c.b);
	return c;
}

void Texture::setColor(const SDL_Color& c)
{
	SDL_SetTextureColorMod(sp.get(), c.r, c.g, c.b);
}

int Texture::getAlpha() const
{
	Uint8 alpha;
	SDL_GetTextureAlphaMod(sp.get(), &alpha);
	return alpha;
}

void Texture::setAlpha(const int& alpha)
{
	SDL_SetTextureAlphaMod(sp.get(), alpha);
}

SDL_BlendMode Texture::getBlendMode() const
{
	SDL_BlendMode blend;
	SDL_GetTextureBlendMode(sp.get(), &blend);
	return blend;
}

void Texture::setBlendMode(const SDL_BlendMode& blend)
{
	SDL_SetTextureBlendMode(sp.get(), blend);
}

Texture::Texture(SDL_Texture* text) : sp(text, SDL_DestroyTexture)
{
	
}
