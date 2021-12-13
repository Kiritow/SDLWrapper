#pragma once
#include "includes.h"

using Event = SDL_Event;

int WaitEvent(Event& e);
int WaitEvent(Event& e, int ms);
int PollEvent(Event& e);
bool IsQuitRequested();
