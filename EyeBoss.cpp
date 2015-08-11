#include "stdafx.h"
#include "EyeBoss.h"

namespace Terraria
{
	HRESULT EyeBoss::initialize(DroppedItemManager* dm, Player* player, int hp, int atk, int def)
	{
		_player = player;
		_image = IMAGEMANAGER->findImage("boss eye");

		setUnitInfo(hp, 0, atk, def);
		setMaxSpeed(METER_TO_PIXEL * 20);
		setSize(120, 120);
		setTileCollision(false);

		_attackTime = 3000;

		_dm = dm;

		SOUNDMANAGER->play("boss", _option.volume());
		return S_OK;
	}
	void EyeBoss::release()
	{
		TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(M_PI * 2), 160, "boss eye dead 1", 1, 1, 3000, false, true);
		TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(M_PI * 2), 160 * 2, "boss eye dead 1", 1, 1, 3000, false, true);
		TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(M_PI * 2), 160 * 2, "boss eye dead 1", 1, 1, 3000, false, true);
		TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(M_PI * 2), 160 * 2, "boss eye dead 2", 1, 1, 3000, false, true);
		TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(M_PI * 2), 160 * 2, "boss eye dead 2", 1, 1, 3000, false, true);
		TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(M_PI * 2), 160 * 2, "boss eye dead 3", 1, 1, 3000, false, true);
		TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(M_PI * 2), 160 * 2, "boss eye dead 3", 1, 1, 3000, false, true);
		TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(M_PI * 2), 160 * 2, "boss eye dead 3", 1, 1, 3000, false, true);
		TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(M_PI * 2), 160 * 2, "boss eye dead 4", 1, 1, 3000, false, true);
		TEffectManager::getSingleton()->createEffect(getX(), getY(), RANDOM->getFloat(M_PI * 2), 160 * 2, "boss eye dead 4", 1, 1, 3000, false, true);

		_dm->createDroppedItem("ingot cobalt", 10, getX(), _player->getY(), RANDOM->getFloatTo(10, 100), RANDOM->getFloat(M_PI * 2));
		_dm->createDroppedItem("blue baloon", 1, getX(), _player->getY(), RANDOM->getFloatTo(10, 100), RANDOM->getFloat(M_PI * 2));
		
		SOUNDMANAGER->play("monster dead", _option.volume());
	}
	void EyeBoss::update()
	{
		_angleByPlayer = myUtil::getAngle(getX(), getY(), _player->getX(), _player->getY());

		if (_attackTime < 0)
		{
			_attackTime = 3000;

			setAngleR(_angleByPlayer);
			setAccel(-100);
			setSpeed(METER_TO_PIXEL * 5);
		}
		else //if (abs(getX() - _player->getX()) > METER_TO_PIXEL * 10 || abs(getY() - _player->getY()) > METER_TO_PIXEL * 10)
		{
			float accelX = cos(_angleByPlayer) * METER_TO_PIXEL * 5;//(min(10, abs(getX() - _player->getX())) * 10);
			float accelY = -sin(_angleByPlayer) * METER_TO_PIXEL * 5;//(min(10, abs(getY() - _player->getY())) * 10);

			setAccelX(getAccelX() + accelX);
			setAccelY(getAccelY() + accelY);
		}

		activate();
		_attackTime -= TIMEMANAGER->getElapsedTime() * 1000;
	}
	void EyeBoss::render(HDC hdc)
	{
		//_image->setCenter(getX(), getY());
		_image->rotateRender(hdc,_option.getRenderX(getX()), _option.getRenderY(getY()), _angleByPlayer);
	}
	void EyeBoss::hit(UNIT_DIRECT direct, int atk)
	{
		setHp(getHp() - max(0, atk - getDef()));
		SOUNDMANAGER->play("monster hit", _option.volume());
	}

	EyeBoss::EyeBoss()
	{

	}
	EyeBoss::~EyeBoss()
	{

	}
}