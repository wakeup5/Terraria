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
		
		if ((_head = IMAGEMANAGER->addImage("player head", IMAGE("player/head"), 80, 1120, TRUE, TRANS_COLOR)) == NULL) return E_FAIL;
		if ((_body = IMAGEMANAGER->addImage("player body", IMAGE("player/body"), 80, 1120, TRUE, TRANS_COLOR)) == NULL) return E_FAIL;
		if ((_leg = IMAGEMANAGER->addImage("player leg", IMAGE("player/leg"), 80, 1120, TRUE, TRANS_COLOR)) == NULL) return E_FAIL;
		if ((_hair = IMAGEMANAGER->addImage("player hair", IMAGE("player/hair"), 80, 1120, TRUE, TRANS_COLOR)) == NULL) return E_FAIL;

		setSize(PLAYER_WIDTH, PLAYER_HEIGHT);
		setCenter(100, 100);
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
		ANIMATEMANAGER->addArrFrameAnimation("player action left", 80, 1120, 2, 20, 12, actionLeftArr, 4, false);
		int actionRightArr[] = { 2, 4, 6, 8 };
		ANIMATEMANAGER->addArrFrameAnimation("player action right", 80, 1120, 2, 20, 12, actionRightArr, 4, false);
		ANIMATEMANAGER->addSectionFrameAnimation("player jump left", 80, 1120, 2, 20, 0, 11, 11);
		ANIMATEMANAGER->addSectionFrameAnimation("player jump right", 80, 1120, 2, 20, 0, 10, 10);

		_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player stay left");

		setState(UNIT_STATE_STAY_RIGHT);
		return S_OK;
	}
	void Player::release()
	{

	}
	//void update();
	void Player::render(HDC hdc)
	{
		Image* image = NULL;
		
		float x = getX() - _option.cameraX() + (_option.width() / 2) - _animate->getFrameWidth() / 2;
		float y = getY() - _option.cameraY() + (_option.height() / 2) - (_animate->getFrameHeight()) / 2 - 6;

		_head->aniRender(hdc, x, y, _animate);
		if ((image = _equip->getEquipImage(EQUIP_HELMET)) != NULL)
		{
			image->aniRender(hdc, x, y, _animate);
		}
		else
		{
			_hair->aniRender(hdc, x, y, _animate);
		}
		_body->aniRender(hdc, x, y, _animate);
		if ((image = _equip->getEquipImage(EQUIP_TOP)) != NULL) image->aniRender(hdc, x, y, _animate);
		_leg->aniRender(hdc, x, y, _legAnimate);
		if ((image = _equip->getEquipImage(EQUIP_PANT)) != NULL) image->aniRender(hdc, x, y, _legAnimate);
		
		if ((image = _equip->getEquipImage(EQUIP_ACCESSORY)) != NULL) image->aniRender(hdc, x, y, _animate);
	}

	void Player::action()
	{
		Unit::action();
		if (_selectItem != NULL && _selectItem->getItemType() == ITEM_WEAPON_BOW)
		{
			setAction(ACTION_SHOOT);
		}
		else
		{
			setAction(ACTION_SWING);
		}
		animate();
		_animate->start();
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

		if (getUnitState().action != 0 && !_animate->isPlay())
		{
			setAction(0);
			animate();
		}

		//animate();
	}

	void Player::animate()
	{
		switch (getState())
		{
		case UNIT_STATE_STAY_LEFT:
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player stay left");
			break;
		case UNIT_STATE_STAY_RIGHT:
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player stay right");
			break;
		case UNIT_STATE_MOVE_LEFT:
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player move left");
			break;
		case UNIT_STATE_MOVE_RIGHT:
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player move right");
			break;
		case UNIT_STATE_JUMP_LEFT:
		case UNIT_STATE_JUMP_MOVE_LEFT:
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player jump left");
			break;
		case UNIT_STATE_JUMP_RIGHT:
		case UNIT_STATE_JUMP_MOVE_RIGHT:
			_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player jump right");
			break;
		case UNIT_STATE_SWING_LEFT:
			_animate = ANIMATEMANAGER->findAnimation("player action left");
			_legAnimate = ANIMATEMANAGER->findAnimation("player stay left");
			break;
		case UNIT_STATE_SWING_RIGHT:
			_animate = ANIMATEMANAGER->findAnimation("player action right");
			_legAnimate = ANIMATEMANAGER->findAnimation("player stay right");
			break;
		case UNIT_STATE_SWING_MOVE_LEFT:
			_animate = ANIMATEMANAGER->findAnimation("player action left");
			_legAnimate = ANIMATEMANAGER->findAnimation("player move left");
			break;
		case UNIT_STATE_SWING_MOVE_RIGHT:
			_animate = ANIMATEMANAGER->findAnimation("player action right");
			_legAnimate = ANIMATEMANAGER->findAnimation("player move right");
			break;
		case UNIT_STATE_SWING_JUMP_LEFT:
		case UNIT_STATE_SWING_JUMP_MOVE_LEFT:
			_animate = ANIMATEMANAGER->findAnimation("player action left");
			_legAnimate = ANIMATEMANAGER->findAnimation("player jump left");
			break;
		case UNIT_STATE_SWING_JUMP_RIGHT:
		case UNIT_STATE_SWING_JUMP_MOVE_RIGHT:
			_animate = ANIMATEMANAGER->findAnimation("player action right");
			_legAnimate = ANIMATEMANAGER->findAnimation("player jump right");
			break;
		case UNIT_STATE_SHOOT_LEFT:
			break;
		case UNIT_STATE_SHOOT_RIGHT:
			break;
		case UNIT_STATE_SHOOT_MOVE_LEFT:
			break;
		case UNIT_STATE_SHOOT_MOVE_RIGHT:
			break;
		case UNIT_STATE_SHOOT_JUMP_LEFT:
			break;
		case UNIT_STATE_SHOOT_JUMP_RIGHT:
			break;
		case UNIT_STATE_SHOOT_JUMP_MOVE_LEFT:
			break;
		case UNIT_STATE_SHOOT_JUMP_MOVE_RIGHT:
			break;
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
