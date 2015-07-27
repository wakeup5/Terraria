#pragma once
#include "TerrariaObject.h"
#include "Physical.h"

namespace Terraria
{
	enum UNIT_STATE
	{
		UNIT_STATE_STAY = 0x00000000,
		UNIT_STATE_MOVE,
		UNIT_STATE_MOVE_LEFT,
		UNIT_STATE_MOVE_RIGHT,
		UNIT_STATE_FREEFALL,
		UNIT_STATE_FLY,
		UNIT_STATE_ATTACK
	};

	typedef enum UNIT_INPUT_ORDER
	{
		ORDER_MOVE_LEFT = 0x00000001,
		ORDER_MOVE_RIGHT = 0x00000002,
		ORDER_JUMP = 0x00000004,
		ORDER_UNDER_JUMP = 0x00000010,
		ORDER_ATTACK = 0x00000020,
		ORDER_PICK = 0x00000040,
		ORDER_BUILD = 0x00000100,
		ORDER_NONE = 0x00000000
	} UNIT_ORDER;

	class Unit : public Physical
	{
	private:
		UINT _order;
		UNIT_STATE _state;

		float _moveAccel;
		float _moveSpeed;
		float _jumpSpeed;
		float _attackTime;

		bool _isAttack;
		float _attackFrameTime;
	public:
		Unit();
		virtual ~Unit();

		virtual HRESULT initialize();
		virtual void release();
		virtual void update();
		virtual void render(HDC hdc);

		void order(UNIT_ORDER order){ _order = order; }
		void addOrder(UNIT_ORDER order){ _order += order; }

		inline void setMoveAccel(float moveAccel){ _moveAccel = moveAccel; }
		inline void setMoveSpeed(float moveSpeed){ _moveSpeed = moveSpeed; }
		inline void setJumpSpeed(float jumpSpeed){ _jumpSpeed = jumpSpeed; }
		inline void setAttackTime(float attackTime){ _attackTime = attackTime; }

		inline float getMoveAccel(){ return _moveAccel; }
		inline float getMoveSpeed(){ return _moveSpeed; }
		inline float getJumpSpeed(){ return _jumpSpeed; }
		inline float getAttackTime(){ return _attackTime; }

		inline UINT getState(){ return _state; }
		inline void setState(UNIT_STATE state){ _state = state; }

		void setFloor(float floorY);
	protected:
		virtual void stateMoveLeft();
		virtual void stateMoveRight();
		virtual void stateFreeFall();
		virtual void stateAttack();
		virtual void stateStay();

	private:
		virtual void action();
	};
}