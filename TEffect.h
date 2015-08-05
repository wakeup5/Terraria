#pragma once
#include "Physical.h"
namespace Terraria
{
	class TEffect : public Physical
	{
	private:
		bool _isTileCollision;
		float _lifeTime;
		float _time;

		SpriteImage* _image;
	public:
		virtual HRESULT initialize(){ return E_FAIL; }
		virtual HRESULT initialize(std::string imageName, int frameX, int frameY, float lifeTIme, bool isTileCollision, bool isGravity);
		virtual void release();
		virtual void update();
		virtual void render(HDC hdc);

		bool isTileCollision(){ return _isTileCollision; }

		bool isLive(){ return _lifeTime > _time; }
	
		TEffect();
		virtual ~TEffect();
	};
}