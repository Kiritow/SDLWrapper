#include "Music.h"

Music::Music(const std::string& filename) : sp(Mix_LoadMUS(filename.c_str()), Mix_FreeMusic)
{

}

Music::Music(const void* data, int size) : sp(Mix_LoadMUS_RW(SDL_RWFromConstMem(data, size), 1), Mix_FreeMusic)
{

}

Sound::Sound(const std::string& filename) : sp(Mix_LoadWAV(filename.c_str()), Mix_FreeChunk)
{

}

Sound::Sound(const void* data, int size) : sp(Mix_LoadWAV_RW(SDL_RWFromConstMem(data, size), 1), Mix_FreeChunk)
{

}

void Sound::setVolume(int volume)
{
	Mix_VolumeChunk(sp.get(), volume);
}

std::thread MusicPlayer::_tdChecker;
std::mutex MusicPlayer::_lock;
std::condition_variable MusicPlayer::_cond;
std::function<void()> MusicPlayer::_cbms;
std::function<void(int)> MusicPlayer::_cbch;
std::queue<std::pair<int, int>> MusicPlayer::_events;

void MusicPlayer::play(const Music& m, int loop)
{
	if (Mix_PlayMusic(m.sp.get(), loop) < 0)
	{
		throw SDLErrorViewer();
	}
}

void MusicPlayer::play(const Sound& s, int chan, int loop)
{
	Mix_PlayChannel(chan, s.sp.get(), loop);
}

void MusicPlayer::fadeIn(const Music& m, int ms, int loop)
{
	Mix_FadeInMusic(m.sp.get(), loop, ms);
}

void MusicPlayer::fadeIn(const Sound& s, int chan, int ms, int loop)
{
	Mix_FadeInChannel(chan, s.sp.get(), loop, chan);
}

void MusicPlayer::fadeInPos(const Music& m, int ms, double position, int loop)
{
	Mix_FadeInMusicPos(m.sp.get(), loop, ms, position);
}

void MusicPlayer::stop()
{
	Mix_HaltMusic();
}

void MusicPlayer::stop(int chan)
{
	Mix_HaltChannel(chan);
}

void MusicPlayer::fadeOut(int ms)
{
	Mix_FadeOutMusic(ms);
}

void MusicPlayer::fadeOut(int chan, int ms)
{
	Mix_FadeOutChannel(chan, ms);
}

void MusicPlayer::pause()
{
	Mix_PauseMusic();
}

void MusicPlayer::pause(int chan)
{
	Mix_Pause(chan);
}

void MusicPlayer::setMusicPosition(double position)
{
	Mix_SetMusicPosition(position);
}

std::tuple<int, Uint16, int> MusicPlayer::querySpec()
{
	int freq;
	Uint16 format;
	int chans;
	if (Mix_QuerySpec(&freq, &format, &chans) == 0)
	{
		throw SDLErrorViewer();
	}
	return std::make_tuple(freq, format, chans);
}

std::tuple<int, Uint16, int, int> MusicPlayer::querySpecEx()
{
	int freq;
	Uint16 format;
	int chans;
	int ret = Mix_QuerySpec(&freq, &format, &chans);
	return std::make_tuple(freq, format, chans, ret);
}

void MusicPlayer::setPosition(int chan, int angle, int distance)
{
	Mix_SetPosition(chan, angle, distance);
}

void MusicPlayer::hookMusic(MusicMixerCallback callback, void* ud)
{
	Mix_HookMusic(callback, ud);
}

void MusicPlayer::hookMusicFinished(MusicFinishedCallback callback)
{
	Mix_HookMusicFinished(callback);
}

void MusicPlayer::hookChannelFinished(ChannelFinishedCallback callback)
{
	Mix_ChannelFinished(callback);
}

void MP_MusicFinishCallgate()
{
	std::unique_lock<std::mutex> ulk(MusicPlayer::_lock);
	MusicPlayer::_events.emplace(1, 0);
	MusicPlayer::_cond.notify_all();
}

void MP_ChannelFinishCallgate(int chan)
{
	std::unique_lock<std::mutex> ulk(MusicPlayer::_lock);
	MusicPlayer::_events.emplace(2, chan);
	MusicPlayer::_cond.notify_all();
}

void MP_CallbackWorker()
{
	int eid, edata;
	std::unique_lock<std::mutex> ulk(MusicPlayer::_lock);
	while (true)
	{
		MusicPlayer::_cond.wait(ulk, []() { return !MusicPlayer::_events.empty(); });
		std::tie(eid, edata) = MusicPlayer::_events.front();
		MusicPlayer::_events.pop();
		if (!eid)
		{
			break;
		}
		else if (eid == 1 && MusicPlayer::_cbms)
		{
			MusicPlayer::_cbms();
		}
		else if (eid == 2 && MusicPlayer::_cbch)
		{
			MusicPlayer::_cbch(edata);
		}
	}
}

void MusicPlayer::onMusicFinished(const std::function<void()>& fn)
{
	std::unique_lock<std::mutex> ulk(MusicPlayer::_lock);
	_cbms = fn;
	hookMusicFinished(MP_MusicFinishCallgate);

	if (!_tdChecker.joinable())
	{
		_tdChecker = std::thread(MP_CallbackWorker);
	}
}

void MusicPlayer::onChannelFinished(const std::function<void(int)>& fn)
{
	std::unique_lock<std::mutex> ulk(MusicPlayer::_lock);
	_cbch = fn;
	hookChannelFinished(MP_ChannelFinishCallgate);

	if (!_tdChecker.joinable())
	{
		_tdChecker = std::thread(MP_CallbackWorker);
	}
}

void MusicPlayer::quitPlayer()
{
	SDL_Log("QuitPlayer called.");
	if (_tdChecker.joinable())
	{
		{
			std::unique_lock<std::mutex> ulk(MusicPlayer::_lock);
			MusicPlayer::_events.emplace(0, 0);
			MusicPlayer::_cond.notify_all();
		}
		_tdChecker.join();
	}
}
