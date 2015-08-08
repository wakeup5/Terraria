#pragma once
#include "TerrariaUnit.h"
#include "Inventory.h"
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

		Inventory* _inven;

		Animate* _animate;
		Animate* _legAnimate;
		Animate* _accAni;

		float _actionTime;

		float _unbeatableTime;

		float _shootAngle;

		float _isDoubleJump;
		float _flyTime;
		bool _fly;
	public:
		HRESULT initialize(Inventory* inven);
		void release();
		//void update();
		void render(HDC hdc);
		void swingRender(HDC hdc);
		void shootRender(HDC hdc);

		void renew();

		void animate();

		void action();
		void move(UNIT_DIRECT direct);
		void stay();
		void jump();
		void freeFall();
		void floor();
		void hit(UNIT_DIRECT direct, int atk = 0);

		void flyDown();
		void flyUp();

		void setFloor(float floorY);

		inline Equip* getEquip(){ return _equip; }

		inline Item* const getSelectItem(){ return _selectItem; }
		inline void setSelectItem(Item* item) { _selectItem = item; }

		inline void setUnbeatableTime(float ms){ _unbeatableTime = ms; }
		inline bool isUnbeatable(){ return _unbeatableTime > 0; }

		float getAtkSpeed();

		inline virtual float getHp();
		inline virtual float getMp();
		inline virtual int getAtk();
		inline virtual int getDef();
		inline virtual int getMaxHp();
		inline virtual int getMaxMp();

		inline Item* getArrow();
		inline Item* getBullet();

		inline void setActionTime(float ms){ _actionTime = ms; }
		inline float isAction(){ return _actionTime > 0; }

		Player();
		~Player();
	};
}
