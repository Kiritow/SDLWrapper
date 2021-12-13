#include "Event.h"

int WaitEvent(Event& e)
{
	return SDL_WaitEvent(&e);
}

int WaitEvent(Event& e, int ms)
{
	return SDL_WaitEventTimeout(&e, ms);
}

int PollEvent(Event& e)
{
	return SDL_PollEvent(&e);
}

bool IsQuitRequested()
{
	return SDL_QuitRequested();
}

