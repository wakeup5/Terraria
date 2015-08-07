#include "stdafx.h"
#include "Zombie.h"

namespace Terraria
{
	Zombie::Zombie()
	{

	}

	Zombie::~Zombie()
	{

	}

	HRESULT Zombie::initialize()
	{
		Unit::initialize();
		switch (RANDOM->getInt(4))
		{
		case 0:
			_image = IMAGEMANAGER->findImage("monster zombie1");
			break;
		case 1:
			_image = IMAGEMANAGER->findImage("monster zombie2");
			break;
		case 2:
			_image = IMAGEMANAGER->findImage("monster zombie3");
			break;
		case 3: default:
			_image = IMAGEMANAGER->findImage("monster zombie4");
			break;
		}

		int leftMoveArr[3] = { 0, 2, 4 };
		ANIMATEMANAGER->addArrFrameAnimation("zombie move left", _image->getWidth(), _image->getHeight(), 2, 3, 10, leftMoveArr, 3, true);
		int rightMoveArr[3] = { 1, 3, 5 };
		ANIMATEMANAGER->addArrFrameAnimation("zombie move right", _image->getWidth(), _image->getHeight(), 2, 3, 10, rightMoveArr, 3, true);

		ANIMATEMANAGER->addSectionFrameAnimation("zombie jump left", _image->getWidth(), _image->getHeight(), 2, 3, 10, 4, 4, false, true);
		ANIMATEMANAGER->addSectionFrameAnimation("zombie jump right", _image->getWidth(), _image->getHeight(), 2, 3, 10, 5, 5, false, true);

		_animate = ANIMATEMANAGER->findAnimation("zombie move left");

		ANIMATEMANAGER->findAnimation("zombie move left")->start();
		ANIMATEMANAGER->findAnimation("zombie move right")->start();
		ANIMATEMANAGER->findAnimation("zombie jump left")->start();
		ANIMATEMANAGER->findAnimation("zombie jump right")->start();

		setState(UnitState{ US(RIGHT, RIGHT, MOVE, FLOOR, 0) });

		setSize(PLAYER_WIDTH, PLAYER_HEIGHT);
		//setCenter(100, 100);
		setMaxSpeed(MAX_SPEED / 2);
		setMaxAccel(MAX_ACCEL);
		setMoveSpeed(PLAYER_MOVE_SPEED / 2);
		setMoveAccel(PLAYER_MOVE_ACCEL / 2);

		setUnitInfo(100, 0, 5, 3);

		return S_OK;
	}
	void Zombie::release()
	{
		TEffectManager::getSingleton()->createEffects(
			getX(), getY(), //x, y
			16, M_PI / 2, METER_TO_PIXEL * 10, // angle 
			"blood", 1, 5, 2500, true); //option
	}

	void Zombie::update()
	{
		Unit::update();
	}

	void Zombie::renew()
	{
		Unit::renew();
		//_animate->frameUpdate(TIMEMANAGER->getElapsedTime());

		if (abs(_prevX - getX()) < 0.1 && getPosition() == FLOOR) jump();

		_prevX = getX();
	}

	void Zombie::render(HDC hdc)
	{
		float x = _option.getRenderX(getX()) - _animate->getFrameWidth() / 2;
		float y = _option.getRenderY(getY()) - (_animate->getFrameHeight()) / 2 - 6;

		_image->aniRender(hdc, x, y, _animate);
	}

	void Zombie::stay()
	{
		Unit::stay();
	}
	void Zombie::move(UNIT_DIRECT direct)
	{
		Unit::move(direct);
		
		if (direct == LEFT)
		{
			_animate = ANIMATEMANAGER->findAnimation("zombie move left");
		}
		else
		{
			_animate = ANIMATEMANAGER->findAnimation("zombie move right");
		}
	}
	void Zombie::jump()
	{
		Unit::jump();

		if (getDirect() == LEFT)
		{
			_animate = ANIMATEMANAGER->findAnimation("zombie move left");
		}
		else
		{
			_animate = ANIMATEMANAGER->findAnimation("zombie move right");
		}
	}
	void Zombie::freeFall()
	{
		Unit::freeFall();

		if (getDirect() == LEFT)
		{
			_animate = ANIMATEMANAGER->findAnimation("zombie move left");
		}
		else
		{
			_animate = ANIMATEMANAGER->findAnimation("zombie move right");
		}
	}
	void Zombie::floor()
	{
		Unit::floor();
	}
	void Zombie::action()
	{
		Unit::action();
	}

	void Zombie::hit(UNIT_DIRECT direct, int atk)
	{
		Unit::hit(direct, atk);
	}
}