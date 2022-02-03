#include "Window.h"

Window::Window(const std::string& title, int w, int h, const SDL_WindowFlags& flags, int x, int y) : _sp(SDL_CreateWindow(title.c_str(), x, y, w, h, flags), SDL_DestroyWindow)
{
	if (!_sp.get()) throw SDLErrorViewer();
}

Renderer Window::createRenderer(Uint32 flags, int index)
{
	return Renderer(SDL_CreateRenderer(_sp.get(), index, flags));
}

Uint32 Window::getID() const
{
	return SDL_GetWindowID(_sp.get());
}

void Window::hide()
{
	SDL_HideWindow(_sp.get());
}

void Window::show()
{
	SDL_ShowWindow(_sp.get());
}

void Window::minimize()
{
	SDL_MinimizeWindow(_sp.get());
}

void Window::maximize()
{
	SDL_MaximizeWindow(_sp.get());
}

void Window::raise()
{
	SDL_RaiseWindow(_sp.get());
}

void Window::restore()
{
	SDL_RestoreWindow(_sp.get());
}

void Window::setSize(int w, int h)
{
	SDL_SetWindowSize(_sp.get(), w, h);
}

std::pair<int, int> Window::getSize() const
{
	int w, h;
	SDL_GetWindowSize(_sp.get(), &w, &h);
	return std::make_pair(w, h);
}

