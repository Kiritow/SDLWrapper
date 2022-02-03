#include "Texture.h"

Texture::operator bool() const
{
	return _sp.get();
}

std::pair<int, int> Texture::getSize() const
{
	int w, h;
	SDL_QueryTexture(_sp.get(), NULL, NULL, &w, &h);
	return std::make_pair(w, h);
}

SDL_Color Texture::getColorMod() const
{
	SDL_Color c;
	c.a = -1;
	SDL_GetTextureColorMod(_sp.get(), &c.r, &c.g, &c.b);
	return c;
}

void Texture::setColorMod(const SDL_Color& c)
{
	SDL_SetTextureColorMod(_sp.get(), c.r, c.g, c.b);
}

int Texture::getAlphaMod() const
{
	Uint8 alpha;
	SDL_GetTextureAlphaMod(_sp.get(), &alpha);
	return alpha;
}

void Texture::setAlphaMod(const int& alpha)
{
	SDL_SetTextureAlphaMod(_sp.get(), alpha);
}

SDL_BlendMode Texture::getBlendMode() const
{
	SDL_BlendMode blend;
	SDL_GetTextureBlendMode(_sp.get(), &blend);
	return blend;
}

void Texture::setBlendMode(const SDL_BlendMode& blend)
{
	SDL_SetTextureBlendMode(_sp.get(), blend);
}

Texture::Texture(SDL_Texture* text) : _sp(text, SDL_DestroyTexture)
{
	
}
