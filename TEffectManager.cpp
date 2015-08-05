#include "stdafx.h"
#include "TEffectManager.h"

namespace Terraria
{
	TEffectManager::TEffectManager()
	{

	}

	TEffectManager::~TEffectManager()
	{

	}

	HRESULT TEffectManager::initialize(int max)
	{
		_max = max;

		return S_OK;
	}
	void TEffectManager::release()
	{
		viEffect iter = _vEffect.begin();
		for (; iter != _vEffect.end(); iter++)
		{
			SAFE_RELEASE(*iter);
		}

		_vEffect.clear();
	}
	void TEffectManager::update()
	{
		viEffect iter = _vEffect.begin();
		for (; iter != _vEffect.end();)
		{
			(*iter)->update();

			if (!(*iter)->isLive())
			{
				SAFE_RELEASE(*iter);
				iter = _vEffect.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
	void TEffectManager::render(HDC hdc)
	{
		viEffect iter = _vEffect.begin();
		for (; iter != _vEffect.end(); iter++)
		{
			(*iter)->render(hdc);
		}
	}

	void TEffectManager::createEffect(
		float x, float y, float angle, float speed, 
		string imageName, int frameX, int frameY, 
		float lifeTime, bool isTileCollision, bool isGravity)
	{
		TEffect* effect = new TEffect;
		effect->initialize(imageName, frameX, frameY, lifeTime, isTileCollision, isGravity);
		effect->setAngleR(angle);
		effect->setSpeed(speed);
		effect->setCenter(x, y);

		_vEffect.push_back(effect);

		if (_vEffect.size() > _max)
		{
			viEffect iter = _vEffect.begin();

			SAFE_RELEASE(*iter);
			_vEffect.erase(iter);
		}
	}

	void TEffectManager::createEffects(
		float x, float y, int amount, float playerAngle, float speed, 
		std::string imageName, int frameX, int frameY, 
		float lifeTime, bool isGravity)
	{
		float angle;
		for (int i = 0; i < amount; i++)
		{
			angle = (((float)i / amount) * M_PI * 2);
			//speed = speed;

			createEffect(
				x, y, //x, y
				angle + RANDOM->getFloatTo(-0.1, 0.1), // angle 
				(speed + (speed * sin(angle - playerAngle + M_PI / 2)) / 1.2) * RANDOM->getFloatTo(0.8, 1.2), //speed
				imageName, frameX, frameY, lifeTime, false, isGravity); //option
		}
	}
}