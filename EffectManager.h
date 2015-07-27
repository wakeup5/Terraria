#pragma once
#include "SingletonBase.h"

typedef std::vector<SpriteImage*> VSpriteImage;
typedef std::vector<SpriteImage*>::iterator VISpriteImage;

class EffectManager : public SingletonBase < EffectManager >
{
private:
	VSpriteImage _vEffect;
	VISpriteImage _viEffect;
public:
	EffectManager();
	~EffectManager();

	HRESULT initialize();
	void release();
	void update();
	void render(HDC hdc);

	void addEffect(SpriteImage* spriteEffect);
};

