#pragma once
#include "TerrariaUnit.h"

namespace Terraria
{
	class Zombie : public Unit
	{
	private:
		Image* _image;
		Animate* _animate;

		float _prevX;
	public:
		HRESULT initialize();
		void release();
		void update();
		void render(HDC hdc);

		virtual void stay();
		virtual void move(UNIT_DIRECT direct);
		virtual void jump();
		virtual void freeFall();
		virtual void floor();
		virtual void action();

		virtual void renew();

		Zombie();
		virtual ~Zombie();
	};
}