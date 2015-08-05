#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

HRESULT SoundManager::initialize(void)
{
	//사운드 시스템 생성
	System_Create(&_system);

	//채널수
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//사운드와 채널 동적할당
	//_sound = new Sound*[TOTALSOUNDBUFFER];
	//_channel = new Channel*[TOTALSOUNDBUFFER];

	//멤셋~~
	//memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	//memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));

	_soundMap.clear();
	_channelMap.clear();

	return S_OK;
}

void SoundManager::release(void)
{
	//사운드 삭제한당~
	/*
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}
			if (_sound != NULL)
			{
				if (_sound != NULL) _sound[i]->release();
			}
		}
	}

	//메모리 지운다
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);
	*/

	for (SoundMapIter i = _soundMap.begin(); i != _soundMap.end();)
	{
		i->second->release();
		i = _soundMap.erase(i);
	}

	for (ChannelMapIter i = _channelMap.begin(); i != _channelMap.end();)
	{
		i->second->stop();
		i = _channelMap.erase(i);
	}

	//시스템 닫는다
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}

	_soundMap.clear();
	_channelMap.clear();
}

//사운드 추가한다
void SoundManager::addSound(string keyName, string soundName,
	bool background, bool loop)
{
	//뺑뻉이냐?
	if (loop)
	{
		//브금이냐?
		if (background)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound);
		}
	}
	else //뺑뺑이가 아니면..
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound);
	}

	//맵에 사운드를 키값과 함께 넣어준다
	_soundMap.insert(make_pair(keyName, _sound));
}

//사운드 플레이~~
void SoundManager::play(string keyName, float volume)
{
	SoundMapIter iter = _soundMap.find(keyName);
	ChannelMapIter cIter = _channelMap.find(keyName);

	if (iter != _soundMap.end())
	{
		//if (cIter == _channelMap.end())
		{
			_system->playSound(FMOD_CHANNEL_FREE, iter->second, false, &_channel);

			_channelMap.insert(make_pair(keyName, _channel));
		}
		//else
		//{
		//	_channel = cIter->second;
		//}

		_channel->setVolume(volume);
	}

	/*
	for (iter; iter != _soundMap.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count],
				false, _channel);
			_channel[count]->setVolume(volume);
			break;
		}
	}
	*/
}

//현재 재생중인 사운드를 일시정지 시킴
void SoundManager::pause(string keyName)
{
	ChannelMapIter iter = _channelMap.find(keyName);

	if (iter != _channelMap.end())
	{
		iter->second->setPaused(true);
	}
	/*
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
	*/
}

//일시정지된 사운드를 다시 재생한당..
void SoundManager::resume(string keyName)
{
	ChannelMapIter iter = _channelMap.find(keyName);

	if (iter != _channelMap.end())
	{
		iter->second->setPaused(false);
	}
	/*
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
	*/
}

void SoundManager::stop(string keyName)
{
	ChannelMapIter iter = _channelMap.find(keyName);

	if (iter != _channelMap.end())
	{
		iter->second->stop();
		_channelMap.erase(iter);
	}
	/*
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
	*/
}

void SoundManager::update(void)
{
	//사운드 시스템을 계속 업데이트한다..
	_system->update();

	bool isPlay;
	for (ChannelMapIter i = _channelMap.begin(); i != _channelMap.end();)
	{
		isPlay = false;
		i->second->isPlaying(&isPlay);

		if (!isPlay)
		{
			i = _channelMap.erase(i);
		}
		else
		{
			i++;
		}
	}
}

bool SoundManager::isPlay(string keyName)
{
	bool result = false;
	ChannelMapIter iter = _channelMap.find(keyName);

	if (iter != _channelMap.end())
	{
		return true;
		//iter->second->isPlaying(&result);
	}

	return false;
}
bool SoundManager::isPause(string keyName)
{
	bool result = false;
	ChannelMapIter iter = _channelMap.find(keyName);

	if (iter != _channelMap.end())
	{
		iter->second->getPaused(&result);
	}

	return result;
}