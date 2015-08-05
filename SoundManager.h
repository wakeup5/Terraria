#pragma once
#include "SingletonBase.h"

#include <string>
#include <map>

//fmod.hpp �߰����ش�
#include "inc/fmod.hpp"

//lib��ũ���ش�
#pragma comment (lib, "lib/fmodex_vc.lib")

//������ ä�� ���� (����~~)
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 10

//�� ���� ���� : ���۰� �۾Ƽ� ������
//������ �ذ��ϱ� ���� ������ ���� ä���� ����� �ش�
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

