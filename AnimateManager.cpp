#include "stdafx.h"
#include "AnimateManager.h"


AnimateManager::AnimateManager()
{
}


AnimateManager::~AnimateManager()
{
}


HRESULT AnimateManager::init(void)
{
	return S_OK;
}

void AnimateManager::release(void)
{
	deleteAll();
}

void AnimateManager::update(void)
{
	iterAnimation iter = _mTotalAnimations.begin();

	for (iter; iter != _mTotalAnimations.end(); ++iter)
	{
		if (!iter->second->isPlay()) continue;
		iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	}
}

void AnimateManager::render(void)
{
}

//처음부터 그냥 애니메이션..
void AnimateManager::addDefFrameAnimation(string aniKeyName,
	int width, int height, int maxFrameX, int maxFrameY, int fps, BOOL reverse,
	BOOL loop)
{
	
	Animate* ani = new Animate;

	ani->init(width, height,
		 width / maxFrameX, height / maxFrameY);
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimations.insert(make_pair(aniKeyName, ani));
}

void AnimateManager::addDefFrameAnimation(string aniKeyName,
	int width, int height, int maxFrameX, int maxFrameY, int fps, BOOL reverse,
	BOOL loop, void* cbFunction)
{
	
	Animate* ani = new Animate;

	ani->init(width, height,
		 width / maxFrameX, height / maxFrameY);
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNC)cbFunction);
	ani->setFPS(fps);

	_mTotalAnimations.insert(make_pair(aniKeyName, ani));
}

void AnimateManager::addDefFrameAnimation(string aniKeyName,
	int width, int height, int maxFrameX, int maxFrameY, int fps, BOOL reverse,
	BOOL loop, void* cbFunction, void* obj)
{
	
	Animate* ani = new Animate;

	ani->init(width, height,
		 width / maxFrameX, height / maxFrameY);
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNC_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_mTotalAnimations.insert(make_pair(aniKeyName, ani));
}

//수동으로 선택한 애니메이션
void AnimateManager::addArrFrameAnimation(string aniKeyName,
	int width, int height, int maxFrameX, int maxFrameY, int fps, int* playArr,
	int arrLen, BOOL loop)
{
	
	Animate* ani = new Animate;

	ani->init(width, height,
		 width / maxFrameX, height / maxFrameY);
	ani->setPlayFrame(playArr, arrLen, loop);
	ani->setFPS(fps);

	_mTotalAnimations.insert(make_pair(aniKeyName, ani));
}

void AnimateManager::addArrFrameAnimation(string aniKeyName,
	int width, int height, int maxFrameX, int maxFrameY, int fps, int* playArr,
	int arrLen, BOOL loop, void* cbFunction)
{
	
	Animate* ani = new Animate;

	ani->init(width, height,
		 width / maxFrameX, height / maxFrameY);
	ani->setPlayFrame(playArr, arrLen, loop, (CALLBACK_FUNC)cbFunction);
	ani->setFPS(fps);

	_mTotalAnimations.insert(make_pair(aniKeyName, ani));
}

void AnimateManager::addArrFrameAnimation(string aniKeyName,
	int width, int height, int maxFrameX, int maxFrameY, int fps, int* playArr,
	int arrLen, BOOL loop, void* cbFunction, void* obj)
{
	
	Animate* ani = new Animate;

	ani->init(width, height,
		 width / maxFrameX, height / maxFrameY);
	ani->setPlayFrame(playArr, arrLen, loop, (CALLBACK_FUNC_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_mTotalAnimations.insert(make_pair(aniKeyName, ani));
}

//구간반복 애니메이션
void AnimateManager::addSectionFrameAnimation(string aniKeyName, int width, int height, int maxFrameX, int maxFrameY, int fps, int start, int end, BOOL reverse, BOOL loop)
{
	Animate* ani = new Animate;

	ani->init(width, height, width / maxFrameX, height / maxFrameY);
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimations.insert(make_pair(aniKeyName, ani));
}

void AnimateManager::addSectionFrameAnimation(string aniKeyName,
	int width, int height, int maxFrameX, int maxFrameY, int fps, int start,
	int end, BOOL reverse, BOOL loop, void* cbFunction)
{
	
	Animate* ani = new Animate;

	ani->init(width, height,
		 width / maxFrameX, height / maxFrameY);
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNC)cbFunction);
	ani->setFPS(fps);

	_mTotalAnimations.insert(make_pair(aniKeyName, ani));
}

void AnimateManager::addSectionFrameAnimation(string aniKeyName,
	int width, int height, int maxFrameX, int maxFrameY, int fps, int start,
	int end, BOOL reverse, BOOL loop, void* cbFunction, void* obj)
{
	
	Animate* ani = new Animate;

	ani->init(width, height,
		 width / maxFrameX, height / maxFrameY);
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNC_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_mTotalAnimations.insert(make_pair(aniKeyName, ani));
}

void AnimateManager::start(string keyName)
{
	iterAnimation iter = _mTotalAnimations.find(keyName);
	if (iter != _mTotalAnimations.end())
	{
		iter->second->start();
	}
}

void AnimateManager::stop(string keyName)
{
	iterAnimation iter = _mTotalAnimations.find(keyName);
	if (iter != _mTotalAnimations.end())
	{
		iter->second->stop();
	}
}

void AnimateManager::pause(string keyName)
{
	iterAnimation iter = _mTotalAnimations.find(keyName);
	if (iter != _mTotalAnimations.end())
	{
		iter->second->pause();
	}
}

void AnimateManager::resume(string keyName)
{
	iterAnimation iter = _mTotalAnimations.find(keyName);
	if (iter != _mTotalAnimations.end())
	{
		iter->second->resume();
	}
}

//애니메이션 찾는다
Animate* AnimateManager::findAnimation(string keyName)
{
	iterAnimation iter = _mTotalAnimations.find(keyName);
	if (iter != _mTotalAnimations.end())
	{
		return iter->second;
	}
	return NULL;
}

void AnimateManager::deleteAll(void)
{
	iterAnimation iter = _mTotalAnimations.begin();

	for (; iter != _mTotalAnimations.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mTotalAnimations.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mTotalAnimations.clear();
}

