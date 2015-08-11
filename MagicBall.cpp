#include "stdafx.h"
#include "MagicBall.h"
#include "MonsterManager.h"

namespace Terraria
{
	//=================== water ===================//
	HRESULT MBall::initialize(float lifeTime, float effectTime)
	{
		_effectTime = effectTime;
		_time = 0;
		_lifeTime = lifeTime;
		setMaxSpeed(METER_TO_PIXEL * 100);
		setSize(5, 5);

		_effectName = "magic effect bagic";

		return S_OK;
	}
	void MBall::release()
	{
		_unit.clear();
	}
	void MBall::update()
	{
		activate();

		if (_time > _effectTime)
		{
			_time = 0;
			TEffectManager::getSingleton()->createEffect(getX(), getY(), 0, 0,
				_effectName, 1, 9, 1000, false, false);
		}
		else
		{
			_time += TIMEMANAGER->getElapsedTime() * 1000;
 		}

		if (_lifeTime > 0)
		{
			_lifeTime -= TIMEMANAGER->getElapsedTime() * 1000;
		}

	}
	void MBall::render(HDC hdc)
	{

	}

	bool MBall::isPass(Unit* unit)
	{
		sUnit::iterator iter = _unit.find(unit);
		if (iter == _unit.end())
		{
			_unit.insert(unit);
			return false;
		}
		
		return true;
	}

	MBall::MBall()
	{

	}
	MBall::~MBall()
	{

	}

	//=====================water====================//
	HRESULT Water::initialize(float lifeTime, float effectTime)
	{
		MBall::initialize(lifeTime, effectTime);
		setSize(40, 40);
		_effectName = "magic effect graind";
		_clearTime = 0;
		return S_OK;
	}
	void Water::update()
	{
		activate();

		if (_time > _effectTime)
		{
			_time = 0;
			TEffectManager::getSingleton()->createEffect(getX(), getY(), 0, 0,
				_effectName, 1, 4, 120, false, false);
		}
		else
		{
			_time += TIMEMANAGER->getElapsedTime() * 1000;
		}

		if (_lifeTime > 0)
		{
			_lifeTime -= TIMEMANAGER->getElapsedTime() * 1000;
		}

		if (_clearTime < 0)
		{
			_clearTime = 500;
			_unit.clear();
		}
		else
		{
			_clearTime -= TIMEMANAGER->getElapsedTime() * 1000;
		}
	}

	Water::Water(){}
	Water::~Water(){}

	//=====================greenball==================//
	HRESULT GreenBall::initialize(float lifeTime, float effectTime)
	{
		MBall::initialize(lifeTime, effectTime);
		setSize(30, 30);
		_effectName = "magic effect greenball";

		return S_OK;
	}
	void GreenBall::update()
	{
		activate();

		if (_time > _effectTime)
		{
			_time = 0;
			TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(2 * M_PI), METER_TO_PIXEL * 2,
				_effectName, 1, 5, 1000, false, false);
		}
		else
		{
			_time += TIMEMANAGER->getElapsedTime() * 1000;
		}

		if (_lifeTime > 0)
		{
			_lifeTime -= TIMEMANAGER->getElapsedTime() * 1000;
		}
	}
	//====================magic bullet=======================//
	HRESULT MagicBullet::initialize(float lifeTime, float effectTime, float x, float y)
	{
		MBall::initialize(lifeTime, effectTime);
		setSize(30, 30);
		_effectName = "magic effect bullet";

		_x = x;
		_y = y;

		_clearTime = 0;

		return S_OK;
	}
	void MagicBullet::update()
	{
		activate();

		if (_time > _effectTime)
		{
			_time = 0;
			TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(M_PI * 2), 50,
				_effectName, 1, 1, 500, false, false);
			TEffectManager::getSingleton()->createEffect(getX(), getY(), 0, 0,
				"magic effect bagic", 1, 9, 200, false, false);
		}
		else
		{
			_time += TIMEMANAGER->getElapsedTime() * 1000;
		}

		if (_lifeTime > 0)
		{
			_lifeTime -= TIMEMANAGER->getElapsedTime() * 1000;
		}

		if (_clearTime < 0)
		{
			_clearTime = 250;
			_unit.clear();
		}
		else
		{
			_clearTime -= TIMEMANAGER->getElapsedTime() * 1000;
		}

		DIRECT direct = D;
		float destAngle = myUtil::getAngle(getX(), getY(), _x, _y);

		while (destAngle < 0) destAngle += M_PI * 2;
		while (destAngle > (M_PI * 2)) destAngle -= M_PI * 2;

		float sourAngle = getAngleR();

		while (sourAngle < 0) sourAngle += M_PI * 2;
		while (sourAngle >(M_PI * 2)) sourAngle -= M_PI * 2;

		float angle = max(0, (myUtil::getDistance(getX(), getY(), _x, _y) / (_option.width() / 2)) * (M_PI * 4));
		
		while (angle < 0) angle += M_PI * 2;
		while (angle >(M_PI * 2)) angle -= M_PI * 2;

		if (destAngle > sourAngle)
		{
			if (abs(destAngle - sourAngle) < (M_PI / 32)) direct = D;
			else if (abs(destAngle - sourAngle) > M_PI) direct = R;
			else direct = L;
		}
		else
		{
			if (abs(destAngle - sourAngle) < (M_PI / 32)) direct = D;
			else if (abs(destAngle - sourAngle) > M_PI) direct = L;
			else direct = R;
		}

		switch (direct)
		{
		case L:
			setAngleR(sourAngle + (angle * TIMEMANAGER->getElapsedTime()));
			break;
		case R:
			setAngleR(sourAngle - (angle * TIMEMANAGER->getElapsedTime()));
			break;
		case D:
			setAngleR(destAngle);
			break;
		}

		printf("%f, %d\n", destAngle, direct);

	}

	//=================== magicball ==================//
	HRESULT MagicBall::initialize(int max)
	{
		_lMagic.clear();
		_max = max;

		return S_OK;
	}
	void MagicBall::release()
	{
		lMagic::iterator iter = _lMagic.begin();
		for (; iter != _lMagic.end(); iter++)
		{
			SAFE_RELEASE(*iter);
		}

		_lMagic.clear();
	}
	void MagicBall::update()
	{
		lMagic::iterator iter = _lMagic.begin();
		for (; iter != _lMagic.end();)
		{
			if ((*iter)->isLive())
			{
				(*iter)->update();
				iter++;
			}
			else
			{
				iter = _lMagic.erase(iter);
			}
		}
	}
	void MagicBall::render(HDC hdc)
	{
		lMagic::iterator iter = _lMagic.begin();
		for (; iter != _lMagic.end(); iter++)
		{
			(*iter)->render(hdc);
		}
	}
	void MagicBall::shoot(float x, float y, float angle, float accel, float speed)
	{
		MBall* water = new MBall;
		water->initialize(5000, (10000 / accel));
		water->setAngleR(angle);
		water->setAccel(accel);
		water->setSpeed(speed);
		water->setCenter(x, y);

		_lMagic.push_back(water);
	}

	void MagicBall::shootWater(float x, float y, float angle, float accel, float speed)
	{
		MBall* water = new Water;
		water->initialize(5000, (10000 / accel));
		water->setAngleR(angle);
		//water->setAccel(accel);
		water->setSpeed(METER_TO_PIXEL * 10);
		water->setCenter(x, y);

		_lMagic.push_back(water);
	}

	void MagicBall::shootGreenball(float startX, float startY, float endX, float endY, float accel, float speed)
	{
		float x = RANDOM->getIntTo(startX - METER_TO_PIXEL * 3, startX + METER_TO_PIXEL * 3);
		float y = RANDOM->getIntTo(startY - METER_TO_PIXEL * 3, startY + METER_TO_PIXEL * 3);

		MBall* water = new GreenBall;
		water->initialize(5000, 10);
		water->setAngleR(myUtil::getAngle(x, y, endX, endY));
		water->setAccel(accel);
		water->setSpeed(speed);
		water->setCenter(x, y);

		_lMagic.push_back(water);
	}

	void MagicBall::shootFire(float startX, float startY, float endX, float endY, float accel, float speed)
	{
		float angle = myUtil::getAngle(startX, startY, endX, endY);
		MagicBullet* water = new MagicBullet;
		water->initialize(5000, 0, endX, endY);
		water->setAngleR(RANDOM->getFloatTo(angle - (M_PI / 4), angle + (M_PI / 4)));
		//water->setAngleR(RANDOM->getFloat(M_PI * 2));
		water->setAccel(accel);
		water->setSpeed(speed);
		water->setCenter(startX, startY);

		_lMagic.push_back(water);
	}

	bool MagicBall::collisionMonster(MonsterManager* mm, int damage)
	{
		vUnit* mons = mm->getMonsters();
		RECT r;

		lMagic::iterator liMagic = _lMagic.begin();
		viUnit iter;
		
		for (; liMagic != _lMagic.end(); liMagic++)
		{
			iter = mons->begin();

			for (; iter != mons->end(); iter++)
			{
				if (IntersectRect(&r, &(*liMagic)->getRect(), &(*iter)->getRect()) && !(*liMagic)->isPass(*iter))
				{
					(*iter)->hit(((*liMagic)->getSpeedX() < 0) ? LEFT : RIGHT, damage);
					TEffectManager::getSingleton()->createEffects(
						(*iter)->getX(), (*iter)->getY(), //x, y
						8, (*liMagic)->getAngleR(), METER_TO_PIXEL * 10, // angle 
						"blood", 1, 5, 1000, true); //option
					//return true;
				}
			}
		}

		return false;
	}

	MagicBall::MagicBall()
	{

	}

	MagicBall::~MagicBall()
	{

	}
}