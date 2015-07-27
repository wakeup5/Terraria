#pragma once
#include "TerrariaUnit.h"
#include "Equip.h"

namespace Terraria
{
	class Player : public Unit
	{
	private:
		SpriteImage* _head;
		SpriteImage* _body;
		SpriteImage* _leg;
		SpriteImage* _arm;
		SpriteImage* _hair;

		Equip* _equip;
		Item* _selectItem;
	public:
		HRESULT initialize();
		void release();
		//void update();
		void render(HDC hdc);

		void action();

		void stateMoveLeft();
		void stateMoveRight();
		void stateFreeFall();
		void stateAttack();
		void stateStay();

		inline Equip* getEquip(){ return _equip; }

		inline Item* const getSelectItem(){ return _selectItem; }
		inline void setSelectItem(Item* item) { _selectItem = item; }

		Player();
		~Player();
	};
}
