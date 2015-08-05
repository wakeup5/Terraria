#pragma once
#include "SingletonBase.h"
#include "Animate.h"

class AnimateManager : public SingletonBase < AnimateManager >
{
private:
	typedef map<string, Animate*> arrAnimation;
	typedef map<string, Animate*>::iterator iterAnimation;

private:
	arrAnimation _mTotalAnimations;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	/////////////////////////////////////

	void addDefFrameAnimation(string aniKeyName,
		int width, int height,  int maxFrameX, int maxFrameY, int fps = (1.0f / 60.0f), BOOL reverse = FALSE,
		BOOL loop = FALSE);

	void addDefFrameAnimation(string aniKeyName,
		int width, int height,  int maxFrameX, int maxFrameY, int fps, BOOL reverse,
		BOOL loop, void* cbFunction);

	void addDefFrameAnimation(string aniKeyName,
		int width, int height,  int maxFrameX, int maxFrameY, int fps, BOOL reverse,
		BOOL loop, void* cbFunction, void* obj);

	/////////////////////////////////////

	void addArrFrameAnimation(string aniKeyName,
		int width, int height,  int maxFrameX, int maxFrameY, int fps = (1.0f / 60.0f), int* playArr = NULL,
		int arrLen = 0, BOOL loop = FALSE);

	void addArrFrameAnimation(string aniKeyName,
		int width, int height,  int maxFrameX, int maxFrameY, int fps, int* playArr,
		int arrLen, BOOL loop, void* cbFunction);

	void addArrFrameAnimation(string aniKeyName,
		int width, int height,  int maxFrameX, int maxFrameY, int fps, int* playArr,
		int arrLen, BOOL loop, void* cbFunction, void* obj);

	/////////////////////////////////////

	void addSectionFrameAnimation(string aniKeyName,
		int width, int height,  int maxFrameX, int maxFrameY, int fps = (1.0f / 60.0f), int start = 0,
		int end = 0, BOOL reverse = FALSE, BOOL loop = FALSE);

	void addSectionFrameAnimation(string aniKeyName,
		int width, int height,  int maxFrameX, int maxFrameY, int fps, int start,
		int end, BOOL reverse, BOOL loop, void* cbFunction);

	void addSectionFrameAnimation(string aniKeyName,
		int width, int height,  int maxFrameX, int maxFrameY, int fps, int start,
		int end, BOOL reverse, BOOL loop, void* cbFunction, void* obj);

	/////////////////////////////////////

	void start(string keyName);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	//애니메이션 찾는다
	Animate* findAnimation(string keyName);

	void deleteAll(void);

public:
	AnimateManager();
	~AnimateManager();
};

