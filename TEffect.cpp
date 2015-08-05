#include "stdafx.h"
#include "TEffect.h"

namespace Terraria
{
	TEffect::TEffect()
	{

	}

	TEffect::~TEffect()
	{

	}

	HRESULT TEffect::initialize(string imageName, int frameX, int frameY, float lifeTime, bool isTileCollision, bool isGravity)
	{
		Image* temp = IMAGEMANAGER->findImage(imageName);
		if (temp == NULL) return E_FAIL;

		_image = temp->createSprite(frameX, frameY);

		_lifeTime = lifeTime;
		_time = 0;
		_isTileCollision = isTileCollision;

		setMaxSpeed(METER_TO_PIXEL * 100);

		if (isGravity) setAccelY(GRAVITY_ACCEL / 2);

		return S_OK;
	}
	void TEffect::release()
	{
		SAFE_RELEASE(_image);
	}
	void TEffect::update()
	{
		_time += TIMEMANAGER->getElapsedTime() * 1000;
		
		_image->setCenter(_option.getRenderX(getX()), _option.getRenderY(getY()));
		_image->setFrameY((_time / _lifeTime) * _image->getMaxFrameY());

		activate();
	}
	void TEffect::render(HDC hdc)
	{
		_image->render(hdc, 127);
	}
}