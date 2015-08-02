#include "stdafx.h"
#include "Player.h"

using namespace myUtil;

namespace Terraria
{
	Player::Player()
	{

	}
	Player::~Player()
	{

	}

	HRESULT Player::initialize()
	{
		Unit::initialize();
		
		if ((_head = IMAGEMANAGER->findImage("player head")) == NULL) return E_FAIL;
		if ((_body = IMAGEMANAGER->findImage("player body")) == NULL) return E_FAIL;
		if ((_leg = IMAGEMANAGER->findImage("player leg")) == NULL) return E_FAIL;
		if ((_hair = IMAGEMANAGER->findImage("player hair")) == NULL) return E_FAIL;

		setSize(PLAYER_WIDTH, PLAYER_HEIGHT);
		//setCenter(100, 100);
		setMaxSpeed(MAX_SPEED);
		setMaxAccel(MAX_ACCEL);
		setMoveSpeed(PLAYER_MOVE_SPEED);
		setMoveAccel(PLAYER_MOVE_ACCEL);

		_equip = new Equip;
		_equip->initialize();

		ANIMATEMANAGER->addSectionFrameAnimation("player stay left", 80, 1120, 2, 20, 0, 1, 1);
		ANIMATEMANAGER->addSectionFrameAnimation("player stay right", 80, 1120, 2, 20, 0, 0, 0);
		int moveLeftArr[] = { 13, 15, 17, 19, 21, 23, 25, 27 };
		ANIMATEMANAGER->addArrFrameAnimation("player move left", 80, 1120, 2, 20, 25, moveLeftArr, 8, true);
		int moveRightArr[] = { 12, 14, 16, 18, 20, 22, 24, 26 };
		ANIMATEMANAGER->addArrFrameAnimation("player move right", 80, 1120, 2, 20, 25, moveRightArr, 8, true);
		int actionLeftArr[] = { 3, 5, 7, 9 };
		ANIMATEMANAGER->addArrFrameAnimation("player action left", 80, 1120, 2, 20, 16, actionLeftArr, 4, false);
		int actionRightArr[] = { 2, 4, 6, 8 };
		ANIMATEMANAGER->addArrFrameAnimation("player action right", 80, 1120, 2, 20, 16, actionRightArr, 4, false);
		ANIMATEMANAGER->addSectionFrameAnimation("player jump left", 80, 1120, 2, 20, 0, 11, 11);
		ANIMATEMANAGER->addSectionFrameAnimation("player jump right", 80, 1120, 2, 20, 0, 10, 10);

		_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player stay left");

		setState(UnitState{ US(LEFT, LEFT, STAY, JUMP, 0) });

		//SOUNDMANAGER->pause("player run");

		return S_OK;
	}
	void Player::release()
	{

	}
	//void update();
	void Player::render(HDC hdc)
	{
		Image* image = NULL;
		
		float x = _option.getRenderX(getX()) - _animate->getFrameWidth() / 2;
		float y = _option.getRenderY(getY()) - (_animate->getFrameHeight()) / 2 - 6;

		//머리와 투구와 헤어
		_head->aniRender(hdc, x, y, _animate);
		if ((image = _equip->getEquipImage(EQUIP_HELMET)) != NULL)
		{
			image->aniRender(hdc, x, y, _animate);
		}
		else
		{
			_hair->aniRender(hdc, x, y, _animate);
		}

		//스윙 무기 휘두르기
		if (getAction() == ACTION_SWING)
		{
			swingRender(hdc);
		}

		//바디와 갑옷
		_body->aniRender(hdc, x, y, _animate);
		if ((image = _equip->getEquipImage(EQUIP_TOP)) != NULL) image->aniRender(hdc, x, y, _animate);

		//바지와 하의
		_leg->aniRender(hdc, x, y, _legAnimate);
		if ((image = _equip->getEquipImage(EQUIP_PANT)) != NULL) image->aniRender(hdc, x, y, _legAnimate);
		
		//악세서리
		if ((image = _equip->getEquipImage(EQUIP_ACCESSORY)) != NULL) image->aniRender(hdc, x, y, _animate);
	}

	void Player::swingRender(HDC hdc)
	{
		if (_selectItem != NULL)
		{
			if (_actionTime > 0)
			{
				_actionTime -= TIMEMANAGER->getElapsedTime();

				float angleR = 0;
				if (getDirect() == LEFT)
				{
					angleR = M_PI + (_actionTime / (TIMEMANAGER->getElapsedTime() * 12)) * M_PI;
				}
				else
				{
					angleR = M_PI - (_actionTime / (TIMEMANAGER->getElapsedTime() * 12)) * M_PI;
				}
				Image* image = _selectItem->getImage();
				float itemX, itemY;

				itemX = (getX() - _option.cameraX() + (_option.width() / 2)) + sin(angleR) * 25;
				itemY = (getY() - _option.cameraY() + (_option.height() / 2)) - cos(angleR) * 25;

				image->setCenter(itemX, itemY);
				image->rotateRender(hdc, -(angleR - M_PI / 4));
			}
		}
	}

	void Player::action()
	{
		Unit::action();
		if (_selectItem != NULL && _selectItem->getItemType() == ITEM_WEAPON_BOW)
		{
			setAction(ACTION_SHOOT);
			if (getX() > _option.inMouseX())
			{
				setView(LEFT);
			}
			else
			{
				setView(RIGHT);
			}
		}
		else
		{
			setAction(ACTION_SWING);
		}
		animate();
		_animate->start();

		_actionTime = TIMEMANAGER->getElapsedTime() * 12;
	}
	void Player::move(UNIT_DIRECT direct)
	{
		Unit::move(direct);
		animate();
	}
	void Player::stay()
	{
		Unit::stay();
		animate();
	}
	void Player::jump()
	{
		Unit::jump();
		animate();
	}
	void Player::freeFall()
	{
		Unit::freeFall();
		animate();
	}
	void Player::floor()
	{
		Unit::floor();
		animate();
	}

	void Player::renew()
	{
		Unit::renew();
		if (!_animate->isPlay()) _animate->start();
		_animate->frameUpdate(1.0f / MAX_GAME_FPS);

		if (_animate != _legAnimate)
		{
			if (!_legAnimate->isPlay()) _legAnimate->start();
			_legAnimate->frameUpdate(1.0f / MAX_GAME_FPS);
		}

		if (!_animate->isPlay())
		{
			if (getAction() == ACTION_SWING)
			{
				setAction(0);
			}
			else if (getAction() == ACTION_SHOOT)
			{
				if (getMovement() == MOVE)
				{
					setView(getDirect());
				}
				setAction(0);
			}
			animate();
		}

		if (getMovement() == MOVE && getPosition() == FLOOR)
		{
			//SOUNDMANAGER->resume("player run");
			SOUNDMANAGER->play("player run", _option.volume());
		}
		else
		{
			//SOUNDMANAGER->pause("player run");
			SOUNDMANAGER->stop("player run");
		}
		//animate();
	}

	void Player::animate()
	{
		//leg or no action animation
		if (getView() == LEFT && getMovement() == STAY && getPosition() == FLOOR)
		{
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player stay left");
		}
		if (getView() == RIGHT && getMovement() == STAY && getPosition() == FLOOR)
		{
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player stay right");
		}
		if (getView() == LEFT && getMovement() == MOVE && getPosition() == FLOOR)
		{
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player move left");
		}
		if (getView() == RIGHT && getMovement() == MOVE && getPosition() == FLOOR)
		{
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player move right");
		}
		if (getView() == LEFT && getPosition() == JUMP)
		{
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player jump left");
		}
		if (getView() == RIGHT && getPosition() == JUMP)
		{
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player jump right");
		}

		//swing
		if (getAction() == ACTION_SWING)
		{
			if (getView() == LEFT)
			{
				_animate = ANIMATEMANAGER->findAnimation("player action left");
			}
			else
			{
				_animate = ANIMATEMANAGER->findAnimation("player action right");
			}
		}

		//shoot
		if (getAction() == ACTION_SHOOT)
		{
			if (getView() == LEFT)
			{
				_animate = ANIMATEMANAGER->findAnimation("player action left");
			}
			else
			{
				_animate = ANIMATEMANAGER->findAnimation("player action right");
			}
		}
	}

	void Player::setFloor(float floorY)
	{
		Unit::setFloor(floorY);
		if (abs(getSpeedY()) < FLOAT_EPSILON)
		{

		}
	}
}
