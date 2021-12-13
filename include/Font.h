#pragma once
#include "includes.h"
#include "Surface.h"
#include "Renderer.h"

class Font
{
public:
	std::shared_ptr<TTF_Font> _sp;
	operator bool();

	Font() = default;
	Font(const std::string& filename, int ptsize);
	Font(const void* data, int size, int ptsize);

	std::pair<int, int> sizeUTF8(const std::string& text);

	// UTF8
	Surface blendUTF8(const std::string& text, const SDL_Color& fg);
	Surface solidUTF8(const std::string& text, const SDL_Color& fg);
	Surface shadedUTF8(const std::string& text, const SDL_Color& fg, const SDL_Color& bg);
	
	Texture blendUTF8(Renderer& rnd, const std::string& text, const SDL_Color& fg);
	Texture solidUTF8(Renderer& rnd, const std::string& text, const SDL_Color& fg);
	Texture shadedUTF8(Renderer& rnd, const std::string& text, const SDL_Color& fg, const SDL_Color& bg);

	// GBK
	Surface blendGBK(const std::string& text, const SDL_Color& fg);
	Surface solidGBK(const std::string& text, const SDL_Color& fg);
	Surface shadedGBK(const std::string& text, const SDL_Color& fg, const SDL_Color& bg);

	Texture blendGBK(Renderer& rnd, const std::string& text, const SDL_Color& fg);
	Texture solidGBK(Renderer& rnd, const std::string& text, const SDL_Color& fg);
	Texture shadedGBK(Renderer& rnd, const std::string& text, const SDL_Color& fg, const SDL_Color& bg);
};
