#pragma once
#include "TerrariaUnit.h"
#include "Equip.h"
#include "Animate.h"

namespace Terraria
{
	class Player : public Unit
	{
	private:
		Image* _head;
		Image* _body;
		Image* _leg;
		Image* _arm;
		Image* _hair;

		Equip* _equip;
		Item* _selectItem;

		Animate* _animate;
		Animate* _legAnimate;
	public:
		HRESULT initialize();
		void release();
		//void update();
		void render(HDC hdc);

		void renew();

		void animate();

		void action();
		void move(UNIT_DIRECT direct);
		void stay();
		void jump();
		void freeFall();
		void floor();

		void setFloor(float floorY);

		inline Equip* getEquip(){ return _equip; }

		inline Item* const getSelectItem(){ return _selectItem; }
		inline void setSelectItem(Item* item) { _selectItem = item; }

		Player();
		~Player();
	};
}
