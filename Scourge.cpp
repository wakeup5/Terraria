#include "stdafx.h"
#include "Scourge.h"


Scourge::Scourge()
{
}


Scourge::~Scourge()
{
}

HRESULT Scourge::initialize(float x, float y, float angleD, float speed)
{
	Image* image = IMAGEMANAGER->addImage("scourge", "resource/starcraft/scourge.bmp", 544, 150, TRUE, RGB(0, 255, 0));
	if (!image) return E_FAIL;

	Unit::initialize(image->createSprite(16, 5), x, y, 20, 20, angleD, speed);

	_unitName = "scourge";

	Image* hpBar = IMAGEMANAGER->addImage("hp bar", "resource/starcraft/hp_bar.bmp", 50, 5);
	Image* hpBarB = IMAGEMANAGER->addImage("hp bar back", "resource/starcraft/hp_bar_back.bmp", 50, 5);
	Image* mpBar = IMAGEMANAGER->addImage("mp bar", "resource/starcraft/mp_bar.bmp", 50, 5);
	Image* mpBarB = IMAGEMANAGER->addImage("mp bar back", "resource/starcraft/mp_bar_back.bmp", 50, 5);

	_hpBar->initialize(hpBar, hpBarB, 0, 20);
	_mpBar->initialize(mpBar, mpBarB, 0, 27);

	_walkTime = 10000;

	return S_OK;
}
void Scourge::release(void)
{
	SAFE_RELEASE(_image);
}
void Scourge::move()
{

}
void Scourge::frame(void)
{
	if (getSpeed() == 0)
	{
		_image->setFrameY(0);
	}
	else
	{
		if (_image->getFrameY() == 0) _image->setFrameY(1);
	}
}
void Scourge::draw(HDC hdc)
{
	
}