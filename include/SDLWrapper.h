#pragma once

#include "Color.h"
#include "ErrorViewer.h"
#include "Event.h"
#include "Font.h"
#include "Music.h"
#include "Point.h"
#include "RWOP.h"
#include "Rect.h"
#include "Renderer.h"
#include "Surface.h"
#include "Texture.h"
#include "Window.h"

void InitSDLWrapper(Uint32 sdl = SDL_INIT_EVERYTHING, int img = IMG_INIT_PNG, int mixer = MIX_INIT_MP3);
void ShutdownSDLWrapper();
