#pragma once
#include "includes.h"
#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>

class Music
{
public:
	std::shared_ptr<Mix_Music> _sp;

	Music(const std::string& filename);
	Music(const void* data, int size);
};

class Sound
{
public:
	std::shared_ptr<Mix_Chunk> _sp;

	Sound(const std::string& filename);
	Sound(const void* data, int size);

	void setVolume(int volume);
};

class MusicPlayer
{
public:
	// Player Control
	static void play(const Music& m, int loop = 1);
	static void play(const Sound& s, int chan, int loop = 0);
	static void fadeIn(const Music& m, int ms, int loop = 1);
	static void fadeIn(const Sound& s, int chan, int ms, int loop = 0);
	static void fadeInPos(const Music& m, int ms, double position, int loop = 1);
	static void stop();
	static void stop(int chan);
	static void fadeOut(int ms);
	static void fadeOut(int chan, int ms);
	static void pause();
	static void pause(int chan);
	static void setMusicPosition(double position);

	// General
	static std::tuple<int, Uint16, int> querySpec();
	static std::tuple<int, Uint16, int, int> querySpecEx();

	// Effects
	static void setPosition(int chan, int angle, int distance);

	// Callbacks
	using MusicMixerCallback = void (*)(void* ud, Uint8* stream, int len);
	using MusicFinishedCallback = void(*)();
	using ChannelFinishedCallback = void(*)(int);
	static void hookMusic(MusicMixerCallback callback, void* ud);  // Direct callback
	static void hookMusicFinished(MusicFinishedCallback callback);  // Direct callback
	static void hookChannelFinished(ChannelFinishedCallback callback);  // Direct callback
	static void onMusicFinished(const std::function<void()>& fn);  // Delegate callback, recommended.
	static void onChannelFinished(const std::function<void(int)>& fn);  // Delegate callback, recommended.

	// Reserved
	static void quitPlayer();
private:
	friend void MP_MusicFinishCallgate();
	friend void MP_ChannelFinishCallgate(int);
	friend void MP_CallbackWorker();

	static std::thread _tdChecker;
	static std::mutex _lock;
	static std::condition_variable _cond;
	static std::function<void()> _cbms;
	static std::function<void(int)> _cbch;
	static std::queue<std::pair<int, int>> _events;
};
