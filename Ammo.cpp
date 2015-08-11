#include "stdafx.h"
#include "Ammo.h"

namespace Terraria
{
	//========================= arrow =========================//
	HRESULT Arrow::initialize()
	{
		_image = new Image(*IMAGEMANAGER->findImage("arrow image"));
		setMaxSpeed(METER_TO_PIXEL * 50);
		setAccelY(GRAVITY_ACCEL / 2);
		return S_OK;
	}
	void Arrow::release()
	{
		//SAFE_RELEASE(_image);
	}
	void Arrow::update()
	{
		activate();
		_image->setCenter(_option.getRenderX(getX()), _option.getRenderY(getY()));
	}
	void Arrow::render(HDC hdc)
	{
		_image->rotateRender(hdc, getAngleR() - M_PI / 2);
	}
	//======================== bullet ==========================//
	HRESULT Bullet::initialize()
	{
		_image = new Image(*IMAGEMANAGER->findImage("bullet image"));
		setMaxSpeed(METER_TO_PIXEL * 100);
		return S_OK;
	}
	void Bullet::release()
	{
		
	}
	void Bullet::update()
	{
		activate();
		_image->setCenter(_option.getRenderX(getX()), _option.getRenderY(getY()));
	}
	void Bullet::render(HDC hdc)
	{
		_image->rotateRender(hdc, getAngleR() - M_PI / 2);
	}

	//========================== Ammo ============================//
	HRESULT Ammo::initialize(int max)
	{
		_lAmmo.clear();
		_max = max;

		return S_OK;
	}
	void Ammo::release()
	{
		liAmmo iter = _lAmmo.begin();
		for (; iter != _lAmmo.end();)
		{
			SAFE_RELEASE(*iter);
			iter = _lAmmo.erase(iter);
		}
		_lAmmo.clear();
	}
	void Ammo::update()
	{
		liAmmo iter = _lAmmo.begin();
		for (; iter != _lAmmo.end(); iter++)
		{
			(*iter)->update();
		}
	}
	void Ammo::render(HDC hdc)
	{
		liAmmo iter = _lAmmo.begin();
		for (; iter != _lAmmo.end(); iter++)
		{
			(*iter)->render(hdc);
		}
	}

	void Ammo::fireArrow(float x, float y, float angle, float speed)
	{
		Arrow* arrow = new Arrow;
		arrow->initialize();
		arrow->setCenter(x, y);
		arrow->setSize(METER_TO_PIXEL, METER_TO_PIXEL);
		arrow->setAngleR(angle);
		arrow->setSpeed(speed);

		arrow->update();

		_lAmmo.push_back(arrow);
		if (_lAmmo.size() > _max) removeFirst();
	}
	void Ammo::fireBullet(float x, float y, float angle, float speed)
	{
		Bullet* bullet = new Bullet;
		bullet->initialize();
		bullet->setCenter(x, y);
		bullet->setSize(METER_TO_PIXEL, METER_TO_PIXEL);
		bullet->setAngleR(angle);
		bullet->setSpeed(speed);

		bullet->update();

		_lAmmo.push_back(bullet);
		if (_lAmmo.size() > _max) removeFirst();
	}

	void Ammo::removeFirst()
	{
		SAFE_DELETE(*_lAmmo.begin());
		_lAmmo.pop_front();
	}
}