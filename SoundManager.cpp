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
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	//멤셋~~
	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));

	return S_OK;
}

void SoundManager::release(void)
{
	//사운드 삭제한당~
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

	//시스템 닫는다
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}

	_mTotalSounds.clear();
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
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0,
				&_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(),
				FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else //뺑뺑이가 아니면..
	{
		_system->createSound(soundName.c_str(),
			FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	//맵에 사운드를 키값과 함께 넣어준다
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

//사운드 플레이~~
void SoundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count],
				false, _channel);
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

//현재 재생중인 사운드를 일시정지 시킴
void SoundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

//일시정지된 사운드를 다시 재생한당..
void SoundManager::resume(string keyName)
{
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
}

void SoundManager::stop(string keyName)
{
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
}

void SoundManager::update(void)
{
	//사운드 시스템을 계속 업데이트한다..
	_system->update();
}