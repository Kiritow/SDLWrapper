#include "SDLWrapper.h"
#include <cstdio>

void InitSDLWrapper(Uint32 sdl, int img, int mixer)
{
	SDL_version compiled, linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("SDL compiled with %d.%d.%d, linked with %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch, linked.major, linked.minor, linked.patch);
	if (SDL_Init(sdl)) throw SDLErrorViewer();

	SDL_IMAGE_VERSION(&compiled);
	linked = *IMG_Linked_Version();
	printf("SDL_image compiled with %d.%d.%d, linked with %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch, linked.major, linked.minor, linked.patch);
	if (img != IMG_Init(img)) throw SDLErrorViewer();

	SDL_TTF_VERSION(&compiled);
	linked = *TTF_Linked_Version();
	printf("SDL_ttf compiled with %d.%d.%d, linked with %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch, linked.major, linked.minor, linked.patch);
	if (TTF_Init()) throw SDLErrorViewer();

	MIX_VERSION(&compiled);
	linked = *Mix_Linked_Version();
	printf("SDL_mixer compiled with %d.%d.%d, linked with %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch, linked.major, linked.minor, linked.patch);
	if (mixer != Mix_Init(mixer)) throw SDLErrorViewer();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) throw SDLErrorViewer();
	if (Mix_AllocateChannels(16) != 16) throw SDLErrorViewer();
}

void ShutdownSDLWrapper()
{
	MusicPlayer::quitPlayer();
	int times;
	std::tie(std::ignore, std::ignore, std::ignore, times) = MusicPlayer::querySpecEx();
	while (times-- > 0) Mix_CloseAudio();

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
