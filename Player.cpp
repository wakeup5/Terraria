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
		
		if (IMAGEMANAGER->addImage("player head", IMAGE("player/head"), 80, 1120, TRUE, TRANS_COLOR) == NULL) return E_FAIL;
		_head = IMAGEMANAGER->findImage("player head")->createSprite(2, 20);

		if (IMAGEMANAGER->addImage("player body", IMAGE("player/body"), 80, 1120, TRUE, TRANS_COLOR) == NULL) return E_FAIL;
		_body = IMAGEMANAGER->findImage("player body")->createSprite(2, 20);

		if (IMAGEMANAGER->addImage("player leg", IMAGE("player/leg"), 80, 1120, TRUE, TRANS_COLOR) == NULL) return E_FAIL;
		_leg = IMAGEMANAGER->findImage("player leg")->createSprite(2, 20);

		if (IMAGEMANAGER->addImage("player hair", IMAGE("player/hair"), 80, 1120, TRUE, TRANS_COLOR) == NULL) return E_FAIL;
		_hair = IMAGEMANAGER->findImage("player hair")->createSprite(2, 20);

		setSize(PLAYER_WIDTH, PLAYER_HEIGHT);
		setCenter(_option.width() / 2, 0);
		setMaxSpeed(MAX_SPEED);
		setMaxAccel(MAX_ACCEL);
		setMoveSpeed(PLAYER_MOVE_SPEED);
		setMoveAccel(PLAYER_MOVE_ACCEL);

		_equip = new Equip;
		_equip->initialize();

		return S_OK;
	}
	void Player::release()
	{
		SAFE_RELEASE(_head);
		SAFE_RELEASE(_hair);
		SAFE_RELEASE(_body);
		SAFE_RELEASE(_leg);
	}
	//void update();
	void Player::render(HDC hdc)
	{
		float x = getX() - _option.cameraX() + (_option.width() / 2) - (_head->getFrameWidth() / 2);
		float y = getY() - _option.cameraY() + (_option.height() / 2) - (_head->getFrameHeight() / 2) - 6;

		_head->render(hdc, x, y);
		_hair->render(hdc, x, y);
		_body->render(hdc, x, y);
		_leg->render(hdc, x, y);
		for (int i = 0; i < EQUIP_NONE; i++)
		{
			SpriteImage* image = _equip->getSpriteImage((EQUIPMENT_TYPE)i);
			if (image != NULL) image->render(hdc, x, y);
		}
	}

	void Player::action()
	{
		_head->setCenter(getX(), getY() - 6);
		_hair->setCenter(getX(), getY() - 6);
		_body->setCenter(getX(), getY() - 6);
		_leg->setCenter(getX(), getY() - 6);

		
		if (abs(getSpeedX()) > 1)
		{
			if (sign(getSpeedX()) < 0)
			{
				_head->setFrameX(1);
				_hair->setFrameX(1);
				_body->setFrameX(1);
				_leg->setFrameX(1);
			}
			else
			{
				_head->setFrameX(0);
				_hair->setFrameX(0);
				_body->setFrameX(0);
				_leg->setFrameX(0);
			}
		}
		
		_equip->setCenter(getX(), getY() - 6);
		for (int i = 0; i < EQUIP_NONE; i++) _equip->setImageFrameX((EQUIPMENT_TYPE)i, _head->getFrameX());
	}

	void Player::stateMoveLeft()
	{
		float frameTime = getSpeed() + 0.02;
		_head->nextFrameY(frameTime);
		_hair->nextFrameY(frameTime);
		_body->nextFrameY(frameTime);
		_leg->nextFrameY(frameTime);

		for (int i = 0; i < EQUIP_NONE; i++)
		{
			if (_equip->getSpriteImage((EQUIPMENT_TYPE)i) == NULL) continue;
			_equip->getSpriteImage((EQUIPMENT_TYPE)i)->nextFrameY(frameTime);
		}

		if (_head->getFrameY() > 13 || _head->getFrameY() < 6)
		{
			_head->setFrameY(6);
			_hair->setFrameY(6);
			_body->setFrameY(6);
			_leg->setFrameY(6);

			for (int i = 0; i < EQUIP_NONE; i++) _equip->setImageFrameY((EQUIPMENT_TYPE)i, 6);
		}
	}
	void Player::stateMoveRight()
	{
		float frameTime = getSpeed() + 0.02;
		_head->nextFrameY(frameTime);
		_hair->nextFrameY(frameTime);
		_body->nextFrameY(frameTime);
		_leg->nextFrameY(frameTime);

		for (int i = 0; i < EQUIP_NONE; i++)
		{
			if (_equip->getSpriteImage((EQUIPMENT_TYPE)i) == NULL) continue;
			_equip->getSpriteImage((EQUIPMENT_TYPE)i)->nextFrameY(frameTime);
		}

		if (_head->getFrameY() > 13 || _head->getFrameY() < 6)
		{
			_head->setFrameY(6);
			_hair->setFrameY(6);
			_body->setFrameY(6);
			_leg->setFrameY(6);

			for (int i = 0; i < EQUIP_NONE; i++) _equip->setImageFrameY((EQUIPMENT_TYPE)i, 6);
		}
	}
	void Player::stateFreeFall()
	{
		_head->setFrameY(5);
		_hair->setFrameY(5);
		_body->setFrameY(5);
		_leg->setFrameY(5);

		for (int i = 0; i < EQUIP_NONE; i++) _equip->setImageFrameY((EQUIPMENT_TYPE)i, 5);
	}
	void Player::stateAttack()
	{
		float frameTime = getSpeed() + 0.02;
		_leg->nextFrameY(frameTime);

		if (getState() == UNIT_STATE_FREEFALL)
		{
			_leg->setFrameY(5);
		}
		else if (abs(getSpeedX()) > 1)
		{
			if(_leg->getFrameY() > 13 || _leg->getFrameY() < 6)
			{
				_leg->setFrameY(6);
			}
		}
		else
		{
			_leg->setFrameY(0);
		}

		if (_equip->getSpriteImage(EQUIP_PANT) != NULL)
		{
			_equip->getSpriteImage(EQUIP_PANT)->nextFrameY(frameTime);

			if (getState() == UNIT_STATE_FREEFALL)
			{
				_equip->getSpriteImage(EQUIP_PANT)->setFrameY(5);
			}
			else if (abs(getSpeedX()) > 1)
			{
				if (_equip->getSpriteImage(EQUIP_PANT)->getFrameY() > 13 || _equip->getSpriteImage(EQUIP_PANT)->getFrameY() < 6)
				{
					_equip->getSpriteImage(EQUIP_PANT)->setFrameY(6);
				}
			}
			else
			{
				_equip->getSpriteImage(EQUIP_PANT)->setFrameY(0);
			}
		}

		_head->nextFrameY(0.5 / 4);
		_hair->nextFrameY(0.5 / 4);
		_body->nextFrameY(0.5 / 4);

		for (int i = 0; i < EQUIP_NONE; i++)
		{
			if (i == EQUIP_PANT) continue;
			if (_equip->getSpriteImage((EQUIPMENT_TYPE)i) == NULL) continue;
			_equip->getSpriteImage((EQUIPMENT_TYPE)i)->nextFrameY(0.5 / 4);
		}

		if (_head->getFrameY() > 4 || _head->getFrameY() < 1)
		{
			_head->setFrameY(1);
			_hair->setFrameY(1);
			_body->setFrameY(1);

			for (int i = 0; i < EQUIP_NONE; i++)
			{
				if (i == EQUIP_PANT) continue;
				_equip->setImageFrameY((EQUIPMENT_TYPE)i, 1);
			}
		}

	}
	void Player::stateStay()
	{
		_head->setFrameY(0);
		_hair->setFrameY(0);
		_body->setFrameY(0);
		_leg->setFrameY(0);

		for (int i = 0; i < EQUIP_NONE; i++)
		{
			_equip->setImageFrameY((EQUIPMENT_TYPE)i, 0);
		}
	}
}
