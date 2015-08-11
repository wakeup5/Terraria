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

	HRESULT Player::initialize(Inventory* inven)
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

		_inven = inven;

		int width = _head->getWidth();
		int height = _head->getHeight();

		ANIMATEMANAGER->addSectionFrameAnimation("player stay left", width, height, 2, 20, 0, 1, 1);
		ANIMATEMANAGER->addSectionFrameAnimation("player stay right", width, height, 2, 20, 0, 0, 0);
		int moveLeftArr[] = { 13, 15, 17, 19, 21, 23, 25, 27 };
		ANIMATEMANAGER->addArrFrameAnimation("player move left", width, height, 2, 20, 25, moveLeftArr, 8, true);
		int moveRightArr[] = { 12, 14, 16, 18, 20, 22, 24, 26 };
		ANIMATEMANAGER->addArrFrameAnimation("player move right", width, height, 2, 20, 25, moveRightArr, 8, true);
		int moveLeftArrRe[] = { 27, 25, 23, 21, 19, 17, 15, 13 };
		ANIMATEMANAGER->addArrFrameAnimation("player move left reverse", width, height, 2, 20, 25, moveLeftArr, 8, true);
		int moveRightArrRe[] = { 26, 24, 22, 20, 18, 16, 14, 12 };
		ANIMATEMANAGER->addArrFrameAnimation("player move right reverse", width, height, 2, 20, 25, moveRightArr, 8, true);
		int actionLeftArr[] = { 3, 5, 7, 9 };
		ANIMATEMANAGER->addArrFrameAnimation("player action left", width, height, 2, 20, 16, actionLeftArr, 4, false);
		int actionRightArr[] = { 2, 4, 6, 8 };
		ANIMATEMANAGER->addArrFrameAnimation("player action right", width, height, 2, 20, 16, actionRightArr, 4, false);
		ANIMATEMANAGER->addSectionFrameAnimation("player jump left", width, height, 2, 20, 0, 11, 11);
		ANIMATEMANAGER->addSectionFrameAnimation("player jump right", width, height, 2, 20, 0, 10, 10);

		//슈팅 공격
		ANIMATEMANAGER->addSectionFrameAnimation("player shoot right 1", width, height, 2, 20, 0, 2, 2);
		ANIMATEMANAGER->addSectionFrameAnimation("player shoot right 2", width, height, 2, 20, 0, 4, 4);
		ANIMATEMANAGER->addSectionFrameAnimation("player shoot right 3", width, height, 2, 20, 0, 6, 6);
		ANIMATEMANAGER->addSectionFrameAnimation("player shoot right 4", width, height, 2, 20, 0, 8, 8);
		ANIMATEMANAGER->addSectionFrameAnimation("player shoot right 5", width, height, 2, 20, 0, 0, 0);

		ANIMATEMANAGER->addSectionFrameAnimation("player shoot left 1", width, height, 2, 20, 0, 3, 3);
		ANIMATEMANAGER->addSectionFrameAnimation("player shoot left 2", width, height, 2, 20, 0, 5, 5);
		ANIMATEMANAGER->addSectionFrameAnimation("player shoot left 3", width, height, 2, 20, 0, 7, 7);
		ANIMATEMANAGER->addSectionFrameAnimation("player shoot left 4", width, height, 2, 20, 0, 9, 9);
		ANIMATEMANAGER->addSectionFrameAnimation("player shoot left 5", width, height, 2, 20, 0, 1, 1);

		//마법 캐스팅
		ANIMATEMANAGER->addSectionFrameAnimation("player magic left", width, height, 2, 20, 0, 11, 11);
		ANIMATEMANAGER->addSectionFrameAnimation("player magic right", width, height, 2, 20, 0, 10, 10);

		int accLeft[] = { 0, 2, 4, 6 };
		ANIMATEMANAGER->addArrFrameAnimation("player acc left", 104, 224, 2, 4, 5, accLeft, 4, true);
		int accRight[] = { 1, 3, 5, 7 };
		ANIMATEMANAGER->addArrFrameAnimation("player acc right", 104, 224, 2, 4, 5, accRight, 4, true);

		_animate = _legAnimate = ANIMATEMANAGER->findAnimation("player stay left");
		_accAni = ANIMATEMANAGER->findAnimation("player acc left");

		ANIMATEMANAGER->findAnimation("player acc left")->start();
		ANIMATEMANAGER->findAnimation("player acc right")->start();

		setState(UnitState{ US(LEFT, LEFT, STAY, JUMP, 0) });

		setUnitInfo(100, 100, 0, 0);
		//SOUNDMANAGER->pause("player run");

		return S_OK;
	}
	void Player::release()
	{

	}
	//void update();
	void Player::render(HDC hdc)
	{
		if (_unbeatableTime > 0 && ((int)_unbeatableTime % 100) > 50) return;

		Image* image = NULL;

		//악세서리
		float accX = _option.getRenderX(getX()) - _accAni->getFrameWidth() / 2;
		float accY = _option.getRenderY(getY()) - (_accAni->getFrameHeight()) / 2 - 20;
		if ((image = _equip->getEquipImage(EQUIP_ACCESSORY)) != NULL) image->aniRender(hdc, accX, accY, _accAni);
		
		//머리와 투구와 헤어
		float x = _option.getRenderX(getX()) - _animate->getFrameWidth() / 2;
		float y = _option.getRenderY(getY()) - (_animate->getFrameHeight()) / 2 - 6;

		_head->aniRender(hdc, x, y, _animate);
		if ((image = _equip->getEquipImage(EQUIP_HELMET)) != NULL)
		{
			image->aniRender(hdc, x, y, _animate);
		}
		else
		{
			_hair->aniRender(hdc, x, y, _animate);
		}

		//바지와 하의
		_leg->aniRender(hdc, x, y, _legAnimate);
		if ((image = _equip->getEquipImage(EQUIP_PANT)) != NULL) image->aniRender(hdc, x, y, _legAnimate);

		//스윙 무기 휘두르기
		if (getAction() == ACTION_SWING)
		{
			swingRender(hdc);
		}
		else if (getAction() == ACTION_SHOOT)
		{
			shootRender(hdc);
		}
		else if (getAction() == ACTION_MAGIC)
		{
			magicRender(hdc);
		}

		//바디와 갑옷
		_body->aniRender(hdc, x, y, _animate);
		if ((image = _equip->getEquipImage(EQUIP_TOP)) != NULL) image->aniRender(hdc, x, y, _animate);
	}

	void Player::swingRender(HDC hdc)
	{
		if (_selectItem != NULL)
		{
			if (_actionTime > 0)
			{
				//_actionTime -= TIMEMANAGER->getElapsedTime();

				float angleR = 0;
				if (getDirect() == LEFT)
				{
					angleR = M_PI + (_actionTime / getAtkSpeed()) * M_PI;
				}
				else
				{
					angleR = M_PI - (_actionTime / getAtkSpeed()) * M_PI;
				}
				Image* image = _selectItem->getImage();
				float itemX, itemY;

				itemX = _option.getRenderX(getX()) + sin(angleR) * 25;
				itemY = _option.getRenderY(getY()) - cos(angleR) * 25;

				image->setCenter(itemX, itemY);
				image->rotateRender(hdc, -(angleR - M_PI / 4));
			}
		}
	}

	void Player::shootRender(HDC hdc)
	{
		//float angleR = -myUtil::getAngle(getX(), getY(), _option.inMouseX(), _option.inMouseY());

		Image* image = _selectItem->getImage();
		float itemX, itemY;

		itemX = (getX() - _option.cameraX() + (_option.width() / 2)) + sin(_shootAngle + M_PI / 2) * 15;
		itemY = (getY() - _option.cameraY() + (_option.height() / 2)) - cos(_shootAngle + M_PI / 2) * 15;

		image->setCenter(itemX, itemY);
		image->rotateRender(hdc, -(_shootAngle));
	}

	void Player::magicRender(HDC hdc)
	{
		Image* image = _selectItem->getImage();
		Image* tempImage = new Image;
		if (FAILED(tempImage->initialize(image->getWidth(), image->getHeight()))) return;
		
		float itemX = _option.getRenderX(getX());
		float itemY = _option.getRenderY(getY()) - METER_TO_PIXEL * 0.5;
		float angle;

		if (getView() == LEFT)
		{
			StretchBlt(tempImage->getMemDC(), tempImage->getWidth() - 1, 0, -tempImage->getWidth(), tempImage->getHeight(), image->getMemDC(), 0, 0, tempImage->getWidth(), tempImage->getHeight(), SRCCOPY);
			itemX -= METER_TO_PIXEL * 1.5;
			angle = M_PI / 4;
		}
		else
		{
			StretchBlt(tempImage->getMemDC(), 0, 0, tempImage->getWidth(), tempImage->getHeight(), image->getMemDC(), 0, 0, tempImage->getWidth(), tempImage->getHeight(), SRCCOPY);
			itemX += METER_TO_PIXEL * 1.5;
			angle = M_PI / 4;
		}
		tempImage->setCenter(itemX, itemY);
		tempImage->render(hdc);

		SAFE_RELEASE(tempImage);
		/*
		image->setCenter(itemX, itemY);
		image->rotateRender(hdc, angle);
		*/		
	}

	void Player::action()
	{
		if (_actionTime > 0) return;

		Unit::action();

		if (_selectItem == NULL)
		{
			setAction(ACTION_SWING);
		}
		else if ((_selectItem->getItemType() == ITEM_WEAPON_BOW && getArrow() != NULL) ||
			(_selectItem->getItemType() == ITEM_WEAPON_GUN && getBullet() != NULL))
		{
			setAction(ACTION_SHOOT);
			_shootAngle = -myUtil::getAngle(getX(), getY(), _option.inMouseX(), _option.inMouseY());
			if (getX() > _option.inMouseX())
			{
				setView(LEFT);
			}
			else
			{
				setView(RIGHT);
			}
		}
		else if (_selectItem->getItemType() == ITEM_WEAPON_MAGIC && getMp() > _selectItem->getAbillity().mana)
		{
			setAction(ACTION_MAGIC);
		}
		else
		{
			setAction(ACTION_SWING);
		}

		animate();
		_animate->start();

		_actionTime = getAtkSpeed();
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
		if (getPosition() != FLOOR)
		{
			if (_equip->getItem(EQUIP_ACCESSORY) != NULL && 
				_equip->getItem(EQUIP_ACCESSORY)->getAbillity().doubleJump &&
  				!_isDoubleJump)
			{
				setPosition(FLOOR);
				Unit::jump();
				animate();
				_isDoubleJump = true;
				_fly = true;

				TEffectManager::getSingleton()->createEffects(getX(), getY(),10, M_PI / 2, 25, 
					"effect jump", 1, 5, 500, false);
			}
		}
		else
		{
			Unit::jump();
			animate();
			if (_equip->getItem(EQUIP_ACCESSORY) != NULL &&
				_equip->getItem(EQUIP_ACCESSORY)->getAbillity().doubleJump)
			{
				_fly = false;
			}
			else
			{
				_fly = true;
			}
		}

		//SOUNDMANAGER->play("player jump", _option.volume());
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

		_isDoubleJump = false;
		_flyTime = 5000;
		_fly = false;
	}

	void Player::flyDown()
	{
		if (_equip->getItem(EQUIP_ACCESSORY) == NULL ||
			!_equip->getItem(EQUIP_ACCESSORY)->getAbillity().fly)
		{
			//flyUp();
			return;
		}

		if (_flyTime > 0 && _fly)
		{
			if (getSpeedY() > (JUMP_SPEED)* 0.5)
			{
				setAccelY(JUMP_SPEED * 2);
			}
			else
			{
				setAccelY(0);
				setSpeedY((JUMP_SPEED) * 0.5);
			}

			static bool isEffect = false;
			if ((int)_flyTime % 20 < 5 && !isEffect)
			{
				TEffectManager::getSingleton()->createEffects(getX(), getY() + METER_TO_PIXEL, 10, getAngleR(), 25,
					"effect jump", 1, 5, 500, false);
				isEffect = true;
			}
			else
			{
				isEffect = false;
			}
			
			_flyTime -= TIMEMANAGER->getElapsedTime() * 1000;
		}
		else
		{
			flyUp();
		}
	}
	void Player::flyUp()
	{
		setAccelY(GRAVITY_ACCEL);
	}

	void Player::renew()
	{
		Unit::renew();
		if (!_animate->isPlay()) _animate->start();

		if (getAction() == ACTION_SWING)
		{
			_animate->frameUpdate(4 / getAtkSpeed());// 1.0f / MAX_GAME_FPS);
		}
		else
		{ 
			_animate->frameUpdate(1.0f / MAX_GAME_FPS);
		}
		_accAni->frameUpdate(1.0f / MAX_GAME_FPS);

		if (_animate != _legAnimate)
		{
			if (!_legAnimate->isPlay()) _legAnimate->start();
			_legAnimate->frameUpdate(1.0f / MAX_GAME_FPS);
		}

		if (_actionTime < 0 || !_animate->isPlay())
		{
			if (getAction() == ACTION_SWING || getAction() == ACTION_MAGIC)
			{
				setAction(ACTION_STAY);
			}
			else if (getAction() == ACTION_SHOOT)
			{
				if (getMovement() == MOVE)
				{
					setView(getDirect());
				}
				else
				{
					setDirect(getView());
				}
				setAction(ACTION_STAY);
			}
			animate();
		}

		//printf("%f\n", _actionTime);

		if (getMovement() == MOVE &&
			getPosition() == FLOOR && 
			!SOUNDMANAGER->isPlay("player run"))
		{
			SOUNDMANAGER->play("player run", _option.volume());
		}

		if (_actionTime > 0) _actionTime -= TIMEMANAGER->getElapsedTime() * 1000;
		if (_unbeatableTime > 0) _unbeatableTime -= TIMEMANAGER->getElapsedTime() * 1000;

		//recovery hp
		if (getHp() < getMaxHp()) setHp(getHp() + 10 * TIMEMANAGER->getElapsedTime());
		else if (getHp() > getMaxHp()) setHp(getMaxHp());
		//recovery mp
		if (getMp() < getMaxMp()) setMp(getMp() + (getMaxMp()) * TIMEMANAGER->getElapsedTime());
		else if (getMp() > getMaxMp()) setMp(getMaxMp());

		//fast run
		if (_equip->getItem(EQUIP_ACCESSORY) != NULL &&
			_equip->getItem(EQUIP_ACCESSORY)->getAbillity().fastRun)
		{
			setMoveSpeed(PLAYER_MOVE_SPEED * 1.5);
		}
		else
		{
			setMoveSpeed(PLAYER_MOVE_SPEED);
		}

		static bool isEffectRun = false;
		if (abs(getSpeedX()) > PLAYER_MOVE_SPEED * 1.2 && getPosition() == FLOOR)
		{
			if (((int)TIMEMANAGER->getWorldTimeMs()) % 20 < 5 && !isEffectRun)
			{
				TEffectManager::getSingleton()->createEffects(getX(), getY() + METER_TO_PIXEL, 3, getAngleR(), 25,
					"effect jump", 1, 5, 500, false);
				isEffectRun = true;
			}
			else
			{
				isEffectRun = false;
			}
		}
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

		//leg reverse
		if (getMovement() == MOVE && getView() != getDirect())
		{
			if (getView() == LEFT)
			{
				_legAnimate = ANIMATEMANAGER->findAnimation("player move left reverse");
			}
			else
			{
				_legAnimate = ANIMATEMANAGER->findAnimation("player move right reverse");
			}
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
			float angle = myUtil::getAngle(getX(), getY(), _option.inMouseX(), _option.inMouseY());
			angle = myUtil::degFromRad(angle);

			while (angle > 360) angle -= 360;
			while (angle < 0) angle += 360;

			if ((angle >= 90) && (angle < 140))
			{
				_animate = ANIMATEMANAGER->findAnimation("player shoot left 2");
			}
			else if ((angle >= 140) && (angle < 190))
			{
				_animate = ANIMATEMANAGER->findAnimation("player shoot left 3");
			}
			else if ((angle >= 190) && (angle < 270))
			{
				_animate = ANIMATEMANAGER->findAnimation("player shoot left 4");
			}
			else if ((angle >= 40) && (angle < 90))
			{
				_animate = ANIMATEMANAGER->findAnimation("player shoot right 2");
			}
			else if ((angle >= 270) && (angle < 350))
			{
				_animate = ANIMATEMANAGER->findAnimation("player shoot right 4");
			}
			else
			{
				_animate = ANIMATEMANAGER->findAnimation("player shoot right 3");
			}

			/*
			if (getView() == LEFT)
			{
				_animate = ANIMATEMANAGER->findAnimation("player action left");
			}
			else
			{
				_animate = ANIMATEMANAGER->findAnimation("player action right");
			}
			*/
		}

		//action casting magic
		if (getAction() == ACTION_MAGIC)
		{
			if (getView() == LEFT)
			{
				_animate = ANIMATEMANAGER->findAnimation("player magic left");
			}
			else
			{
				_animate = ANIMATEMANAGER->findAnimation("player magic right");
			}
		}

		//accesory
		if (getView() == LEFT)
		{
			_accAni = ANIMATEMANAGER->findAnimation("player acc left");
		}
		else
		{
			_accAni = ANIMATEMANAGER->findAnimation("player acc right");
		}

	}

	void Player::setFloor(float floorY)
	{
		Unit::setFloor(floorY);
		if (abs(getSpeedY()) < FLOAT_EPSILON)
		{

		}
	}

	void Player::hit(UNIT_DIRECT direct, int atk)
	{
		Unit::hit(direct, atk);
		_unbeatableTime = 1000;

		switch (RANDOM->getInt(3))
		{
		case 0:
			SOUNDMANAGER->play("hit 1", _option.volume());
			break;
		case 1:
			SOUNDMANAGER->play("hit 2", _option.volume());
			break;
		case 2: default:
			SOUNDMANAGER->play("hit 3", _option.volume());
			break;
		}
	}

	float Player::getAtkSpeed()
	{ 
		if (_selectItem != NULL && _selectItem->getAbillity().atkSpeed > 0)
			return _selectItem->getAbillity().atkSpeed;
		else
			return 333;
	}

	float Player::getHp()
	{
		return Unit::getHp();
	}
	float Player::getMp()
	{
		return Unit::getMp();
	}
	int Player::getAtk()
	{
		float atk = (_selectItem == NULL) ? 0 : _selectItem->getAbillity().attack;
		return max(0, Unit::getAtk() + _equip->getTotalAbillity().attack + atk);
	}
	int Player::getDef()
	{
		return Unit::getDef() + _equip->getTotalAbillity().defense;
	}
	int Player::getMaxHp()
	{
		return Unit::getMaxHp() + _equip->getTotalAbillity().HP;
	}
	int Player::getMaxMp()
	{
		return Unit::getMaxMp() + _equip->getTotalAbillity().MP;
	}

	Item* Player::getArrow()
	{
		Item* item;
		for (int i = 0; i < INVENTORY_LENGTH; i++)
		{
			item = _inven->getItemInfo(i);
			if (item != NULL &&
				item->getItemType() == ITEM_AMMO_ARROW)
			{
				return item;
			}
		}

		return NULL;
	}
	Item* Player::getBullet()
	{
		Item* item;
		for (int i = 0; i < INVENTORY_LENGTH; i++)
		{
			item = _inven->getItemInfo(i);
			if (item != NULL &&
				item->getItemType() == ITEM_AMMO_BULLET)
			{
				return item;
			}
		}

		return NULL;
	}
}
