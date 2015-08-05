#pragma once
#include "SingletonBase.h"

#include <string>
#include <map>

//fmod.hpp 추가해준다
#include "inc/fmod.hpp"

//lib링크해준다
#pragma comment (lib, "lib/fmodex_vc.lib")

//여분의 채널 갯수 (버퍼~~)
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 10

//총 사운드 갯수 : 버퍼가 작아서 씹히는
//문제를 해결하기 위해 여분의 사운드 채널을 만들어 준다
#define TOTALSOUNDBUFFER EXTRACHANNELBUFFER + SOUNDBUFFER

using namespace FMOD;

class SoundManager : public SingletonBase < SoundManager >
{
private:
	typedef map<string, Sound*> SoundMap;
	typedef map<string, Sound*>::iterator SoundMapIter;
	typedef map<string, Channel*> ChannelMap;
	typedef map<string, Channel*>::iterator ChannelMapIter;

private:
	System* _system;
	Sound* _sound;
	Channel* _channel;

	SoundMap _soundMap;
	ChannelMap _channelMap;

public:
	HRESULT initialize();
	void release();
	void update();

	void addSound(string keyName, string soundName,
		bool background, bool loop);
	void play(string keyName, float volume);
	void pause(string keyName);
	void resume(string keyName);
	void stop(string keyName);

	bool isPlay(string keyName);
	bool isPause(string keyName);

public:
	SoundManager();
	~SoundManager();
};

