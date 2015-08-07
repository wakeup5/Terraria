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
		/*
		viEffect iter = _vEffect.begin();
		for (; iter != _vEffect.end(); iter++)
		{
			SAFE_RELEASE(*iter);
		}
		*/
		for (int i = 0; i < _vEffect.size(); i++)
		{
			SAFE_RELEASE(_vEffect[i]);
		}

		_vEffect.clear();
	}
	void TEffectManager::update()
	{
		/*
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
		*/
		for (int i = 0; i < _vEffect.size(); i++)
		{
			_vEffect[i]->update();

			if (!_vEffect[i]->isLive())
			{
				SAFE_RELEASE(_vEffect[i]);
				_vEffect.erase(_vEffect.begin() + i);
				i--;
			}
		}
	}
	void TEffectManager::render(HDC hdc)
	{
		/*
		viEffect iter = _vEffect.begin();
		for (; iter != _vEffect.end(); iter++)
		{
			(*iter)->render(hdc);
		}
		*/
		for (int i = 0; i < _vEffect.size(); i++)
		{
			_vEffect[i]->render(hdc);
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
				angle + RANDOM->getFloat(M_PI / 4), // angle 
				(speed + (speed * sin(angle - playerAngle + M_PI / 2)) * 2), //speed
				imageName, frameX, frameY, lifeTime, false, isGravity); //option
		}
	}
}