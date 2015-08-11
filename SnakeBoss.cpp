#include "stdafx.h"
#include "SnakeBoss.h"
#include "TileMap.h"
#include "DroppedItemManager.h"

namespace Terraria
{
	//============piece============//
	HRESULT SnakePiece::initialize(SnakeBoss* self, PIECE p)
	{
		if (p == HEAD)
		{
			_image = IMAGEMANAGER->findImage("boss snake head");
		}
		else if (p == BODY)
		{
			_image = IMAGEMANAGER->findImage("boss snake body");
		}
		else if (p == TAIL)
		{
			_image = IMAGEMANAGER->findImage("boss snake tail");
		}

		_self = self;

		setSize(50, 50);
		setUnitInfo(1, 1, 20, 10);
		setTileCollision(false);
		setMaxSpeed(METER_TO_PIXEL * 35);

		return S_OK;
	}
	void SnakePiece::release()
	{

	}
	void SnakePiece::update()
	{

	}
	void SnakePiece::render(HDC hdc)
	{
		_image->rotateRender(hdc, _option.getRenderX(getX()), _option.getRenderY(getY()), getAngleR() - (M_PI / 2));
	}

	void SnakePiece::hit(UNIT_DIRECT direct, int atk)
	{
		_self->setHp(_self->getHp() - max(0, atk));
		//sound
		SOUNDMANAGER->play("snake hit", _option.volume());
	}
	
	SnakePiece::SnakePiece(){}
	SnakePiece::~SnakePiece(){}

	//=============snake================//
	HRESULT SnakeBoss::initialize(DroppedItemManager* dm, TileMap* tileMap, Player* player, float x, float y)
	{
		_tileMap = tileMap;
		_player = player;
		_dm = dm;

		setSize(0, 0);
		setCenter(x, y);
		setMaxSpeed(METER_TO_PIXEL * 60);

		_pieces[0] = new SnakePiece;
		_pieces[0]->initialize(this, HEAD);
		_pieces[0]->setCenter(getX(), getY());

		for (int i = 1; i < LENGTH - 1; i++)
		{
			_pieces[i] = new SnakePiece;
			_pieces[i]->initialize(this, BODY);
			_pieces[i]->setCenter(getX(), getY());
			_pieces[i]->setSpeed(METER_TO_PIXEL * 10);
		}

		_pieces[LENGTH - 1] = new SnakePiece;
		_pieces[LENGTH - 1]->initialize(this, TAIL);
		_pieces[LENGTH - 1]->setCenter(getX(), getY());
		_pieces[LENGTH - 1]->setSpeed(METER_TO_PIXEL * 10);

		setUnitInfo(5000, 0, 20, 10);

		setTileCollision(false);

		SOUNDMANAGER->play("boss", _option.volume());

		return S_OK;
	}

	void SnakeBoss::release()
	{
		for (int i = 0; i < LENGTH; i++)
		{
			_pieces[i]->setHp(0);
		}
		_dm->createDroppedItem("ingot mythril", 10, getX(), _player->getY(), RANDOM->getFloatTo(10, 100), RANDOM->getFloat(M_PI * 2));
		_dm->createDroppedItem("ingot blood", 10, getX(), _player->getY(), RANDOM->getFloatTo(10, 100), RANDOM->getFloat(M_PI * 2));

		_dm->createDroppedItem("gray baloon", 1, getX(), _player->getY(), RANDOM->getFloatTo(10, 100), RANDOM->getFloat(M_PI * 2));
		_dm->createDroppedItem("green baloon", 1, getX(), _player->getY(), RANDOM->getFloatTo(10, 100), RANDOM->getFloat(M_PI * 2));

		SOUNDMANAGER->play("snake dead", _option.volume());
	}

	void SnakeBoss::update()
	{
		//snake update
		float distance, angle;
		float x, y;

		_pieces[0]->setCenter(getX(), getY());
		_pieces[0]->setAngleR(getAngleR());
		_pieces[0]->setSpeed(getSpeed());
		//_pieces[0]->activate();

		for (int i = 1; i < LENGTH; i++)
		{
			distance = myUtil::getDistance(_pieces[i - 1]->getX(), _pieces[i - 1]->getY(), _pieces[i]->getX(), _pieces[i]->getY());
			angle = myUtil::getAngle(_pieces[i - 1]->getX(), _pieces[i - 1]->getY(), _pieces[i]->getX(), _pieces[i]->getY());

			while (angle < 0) angle += M_PI * 2;
			while (angle >(M_PI * 2)) angle -= M_PI * 2;

			if (distance > 45)
			{
				x = cos(angle) * 45;
				y = -sin(angle) * 45;
				_pieces[i]->setCenter(_pieces[i - 1]->getX() + x, _pieces[i - 1]->getY() + y);
				_pieces[i]->setAngleR(angle);
			}
			else
			{
				_pieces[i]->setX(_pieces[i]->getX() - cos(_pieces[i]->getAngleR()) * 9.9);
				_pieces[i]->setY(_pieces[i]->getY() + sin(_pieces[i]->getAngleR()) * 9.9);
			}
			
		}


		//moving
		if (!tileCollision() ||
			getX() < 0 || getX() > MAP_SIZE_X * METER_TO_PIXEL ||
			getY() < 0 || getY() > MAP_SIZE_Y * METER_TO_PIXEL)
		{
			setAccel(0);
			setAccelY(GRAVITY_ACCEL / 2);

			//angle = min(M_PI / 4, abs((myUtil::getDistance(getX(), getY(), _player->getX(), _player->getY()) / (_option.width() / 2)) * (M_PI / 8)));
		}
		else
		{
			angle = min(M_PI, abs((myUtil::getDistance(getX(), getY(), _player->getX(), _player->getY()) / (_option.width() / 2)) * (M_PI)));

			setAccelY(0);
			
			setAccel(METER_TO_PIXEL * 80);
			//setSpeed(METER_TO_PIXEL * 80);
			int direct = 0;
			float destAngle = myUtil::getAngle(getX(), getY(), _player->getX(), _player->getY() - METER_TO_PIXEL * 5);
			float sourAngle = getAngleR();

			while (destAngle < 0) destAngle += M_PI * 2;
			while (destAngle >(M_PI * 2)) destAngle -= M_PI * 2;
			while (sourAngle < 0) sourAngle += M_PI * 2;
			while (sourAngle >(M_PI * 2)) sourAngle -= M_PI * 2;
			while (angle < 0) angle += M_PI * 2;
			while (angle >(M_PI * 2)) angle -= M_PI * 2;

			if (destAngle > sourAngle)
			{
				if (abs(destAngle - sourAngle) < (M_PI / 32)) direct = 0;
				else if (abs(destAngle - sourAngle) > M_PI) direct = 2;
				else direct = 1;
			}
			else
			{
				if (abs(destAngle - sourAngle) < (M_PI / 32)) direct = 0;
				else if (abs(destAngle - sourAngle) > M_PI) direct = 1;
				else direct = 2;
			}

			switch (direct)
			{
			case 1:
				setAngleR(sourAngle + (angle * TIMEMANAGER->getElapsedTime()));
				break;
			case 2:
				setAngleR(sourAngle - (angle * TIMEMANAGER->getElapsedTime()));
				break;
			case 0:
				setAngleR(destAngle);
				break;
			}
		}

		activate();
	}

	void SnakeBoss::render(HDC hdc)
	{
		//null
	}

	void SnakeBoss::addMonsterList(vUnit* units)
	{
		for (int i = LENGTH - 1; i > -1; i--)
		{
			units->push_back(_pieces[i]);
		}
	}

	bool SnakeBoss::tileCollision()
	{
		int x = getX() / METER_TO_PIXEL;
		int y = getY() / METER_TO_PIXEL;

		if (x < 0 || x > MAP_SIZE_X || y < 0 || y > MAP_SIZE_Y) return false;
		
		return _tileMap->getTile(x, y)->isBlock();
	}

	SnakeBoss::SnakeBoss(){}
	SnakeBoss::~SnakeBoss(){}
}