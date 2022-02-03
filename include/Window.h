#pragma once
#include "includes.h"
#include "Renderer.h"

class Window
{
public:
	std::shared_ptr<SDL_Window> _sp;

	Window() = default;
	Window(const std::string& title, int w, int h,
		const SDL_WindowFlags& flags = SDL_WINDOW_HIDDEN,
		int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED);
	
	Renderer createRenderer(Uint32 flags = SDL_RENDERER_ACCELERATED, int index = -1);

	Uint32 getID() const;

	void hide();
	void show();
	void minimize();
	void maximize();
	void raise();
	void restore();
	
	void setSize(int w, int h);
	std::pair<int, int> getSize() const;
};
