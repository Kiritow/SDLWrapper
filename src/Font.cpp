#include "Font.h"
#include "Util.h"

Font::operator bool()
{
	return _sp.get();
}

Font::Font(const std::string& filename, int ptsize) : _sp(TTF_OpenFont(filename.c_str(), ptsize), TTF_CloseFont)
{
	if (!_sp.get()) throw SDLErrorViewer();
}

Font::Font(const void* data, int size, int ptsize) : _sp(TTF_OpenFontRW(SDL_RWFromConstMem(data, size), 1, ptsize), TTF_CloseFont)
{
	if (!_sp.get()) throw SDLErrorViewer();
}

std::pair<int, int> Font::sizeUTF8(const std::string& text)
{
	int w, h;
	TTF_SizeUTF8(_sp.get(), text.c_str(), &w, &h);
	return std::make_pair(w, h);
}

Surface Font::blendUTF8(const std::string& text, const SDL_Color& fg)
{
	return Surface(TTF_RenderUTF8_Blended(_sp.get(), text.c_str(), fg));
}

Surface Font::solidUTF8(const std::string& text, const SDL_Color& fg)
{
	return Surface(TTF_RenderUTF8_Solid(_sp.get(), text.c_str(), fg));
}

Surface Font::shadedUTF8(const std::string& text, const SDL_Color& fg, const SDL_Color& bg)
{
	return Surface(TTF_RenderUTF8_Shaded(_sp.get(), text.c_str(), fg, bg));
}

Texture Font::blendUTF8(Renderer& rnd, const std::string& text, const SDL_Color& fg)
{
	return rnd.render(blendUTF8(text, fg));
}

Texture Font::solidUTF8(Renderer& rnd, const std::string& text, const SDL_Color& fg)
{
	return rnd.render(solidUTF8(text, fg));
}

Texture Font::shadedUTF8(Renderer& rnd, const std::string& text, const SDL_Color& fg, const SDL_Color& bg)
{
	return rnd.render(shadedUTF8(text, fg, bg));
}

Surface Font::blendGBK(const std::string& text, const SDL_Color& fg)
{
	std::string str = GBKToUTF8(text);
	return Surface(TTF_RenderUTF8_Blended(_sp.get(), str.c_str(), fg));
}

Surface Font::solidGBK(const std::string& text, const SDL_Color& fg)
{
	std::string str = GBKToUTF8(text);
	return Surface(TTF_RenderUTF8_Solid(_sp.get(), str.c_str(), fg));
}

Surface Font::shadedGBK(const std::string& text, const SDL_Color& fg, const SDL_Color& bg)
{
	std::string str = GBKToUTF8(text);
	return Surface(TTF_RenderUTF8_Shaded(_sp.get(), str.c_str(), fg, bg));
}

Texture Font::blendGBK(Renderer& rnd, const std::string& text, const SDL_Color& fg)
{
	return rnd.render(blendGBK(text, fg));
}

Texture Font::solidGBK(Renderer& rnd, const std::string& text, const SDL_Color& fg)
{
	return rnd.render(solidGBK(text, fg));
}

Texture Font::shadedGBK(Renderer& rnd, const std::string& text, const SDL_Color& fg, const SDL_Color& bg)
{
	return rnd.render(shadedGBK(text, fg, bg));
}

