#include "SDLWrapper.h"

void InitSDLWrapper(Uint32 sdl, int img, int mixer)
{
	if (SDL_Init(sdl)) throw SDLErrorViewer();
	if (img != IMG_Init(img)) throw SDLErrorViewer();
	if (mixer != Mix_Init(mixer)) throw SDLErrorViewer();
	if (TTF_Init()) throw SDLErrorViewer();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) throw SDLErrorViewer();
	if (Mix_AllocateChannels(16) != 16) throw SDLErrorViewer();
}

void ShutdownSDLWrapper()
{
	MusicPlayer::quitPlayer();
	int times;
	std::tie(std::ignore, std::ignore, std::ignore, times) = MusicPlayer::querySpecEx();
	while (times-- > 0) Mix_CloseAudio();

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
