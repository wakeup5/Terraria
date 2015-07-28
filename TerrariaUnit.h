#pragma once
#include "TerrariaObject.h"
#include "Physical.h"

#define UNIT_STATE_DIRECT 0
#define UNIT_STATE_MOVEMENT 4
#define UNIT_STATE_POSITION 8
#define UNIT_STATE_ACTION 12

namespace Terraria
{
	/*
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
	*/
	union UnitState
	{
		USHORT total;
		struct {
			UCHAR direct : 4;
			UCHAR movement : 4;
			UCHAR position : 4;
			UCHAR action : 4;
		};
	};

	enum UNIT_DIRECT
	{
		LEFT = (UCHAR)1,
		RIGHT = (UCHAR)2
	};
	enum UNIT_MOVEMENT
	{
		STAY = (UCHAR)1,
		MOVE = (UCHAR)2
	};
	enum UNIT_POSITION
	{
		FLOOR = (UCHAR)1,
		JUMP = (UCHAR)2
	};
	enum UNIT_ACTION
	{
		ACTION_SWING = (UCHAR)1,
		ACTION_SHOOT = (UCHAR)2,
	};

	enum UNIT_STATE
	{
		UNIT_STATE_STAY_LEFT				= (LEFT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION),
		UNIT_STATE_STAY_RIGHT				= (RIGHT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION),
		UNIT_STATE_MOVE_LEFT				= (LEFT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION),
		UNIT_STATE_MOVE_RIGHT				= (RIGHT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION),
		UNIT_STATE_JUMP_LEFT				= (LEFT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION),
		UNIT_STATE_JUMP_RIGHT				= (RIGHT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION),
		UNIT_STATE_JUMP_MOVE_LEFT			= (LEFT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION),
		UNIT_STATE_JUMP_MOVE_RIGHT			= (RIGHT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION),
		UNIT_STATE_SWING_LEFT				= (LEFT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION) + (ACTION_SWING << UNIT_STATE_ACTION),
		UNIT_STATE_SWING_RIGHT				= (RIGHT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION) + (ACTION_SWING << UNIT_STATE_ACTION),
		UNIT_STATE_SWING_MOVE_LEFT			= (LEFT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION) + (ACTION_SWING << UNIT_STATE_ACTION),
		UNIT_STATE_SWING_MOVE_RIGHT			= (RIGHT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION) + (ACTION_SWING << UNIT_STATE_ACTION),
		UNIT_STATE_SWING_JUMP_LEFT			= (LEFT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION) + (ACTION_SWING << UNIT_STATE_ACTION),
		UNIT_STATE_SWING_JUMP_RIGHT			= (RIGHT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION) + (ACTION_SWING << UNIT_STATE_ACTION),
		UNIT_STATE_SWING_JUMP_MOVE_LEFT		= (LEFT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION) + (ACTION_SWING << UNIT_STATE_ACTION),
		UNIT_STATE_SWING_JUMP_MOVE_RIGHT	= (RIGHT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION) + (ACTION_SWING << UNIT_STATE_ACTION),
		UNIT_STATE_SHOOT_LEFT				= (LEFT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION) + (ACTION_SHOOT << UNIT_STATE_ACTION),
		UNIT_STATE_SHOOT_RIGHT				= (RIGHT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION) + (ACTION_SHOOT << UNIT_STATE_ACTION),
		UNIT_STATE_SHOOT_MOVE_LEFT			= (LEFT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION) + (ACTION_SHOOT << UNIT_STATE_ACTION),
		UNIT_STATE_SHOOT_MOVE_RIGHT			= (RIGHT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (FLOOR << UNIT_STATE_POSITION) + (ACTION_SHOOT << UNIT_STATE_ACTION),
		UNIT_STATE_SHOOT_JUMP_LEFT			= (LEFT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION) + (ACTION_SHOOT << UNIT_STATE_ACTION),
		UNIT_STATE_SHOOT_JUMP_RIGHT			= (RIGHT << UNIT_STATE_DIRECT)	+ (STAY << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION) + (ACTION_SHOOT << UNIT_STATE_ACTION),
		UNIT_STATE_SHOOT_JUMP_MOVE_LEFT		= (LEFT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION) + (ACTION_SHOOT << UNIT_STATE_ACTION),
		UNIT_STATE_SHOOT_JUMP_MOVE_RIGHT	= (RIGHT << UNIT_STATE_DIRECT)	+ (MOVE << UNIT_STATE_MOVEMENT) + (JUMP << UNIT_STATE_POSITION) + (ACTION_SHOOT << UNIT_STATE_ACTION),
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
		UnitState _state;

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

		inline UINT getState(){ return _state.total; }
		inline void setState(UNIT_STATE state){ _state.total = state; }

		inline UnitState getUnitState(){ return _state; }

		inline void setDirect(UCHAR direct){ _state.direct = direct; }
		inline void setMovement(UCHAR movement){ _state.movement = movement; }
		inline void setPosition(UCHAR position){ _state.position = position; }
		inline void setAction(UCHAR action){ _state.action = action; }

		inline UCHAR getDirect(){ return _state.direct; }
		inline UCHAR getMovement(){ return _state.movement; }
		inline UCHAR getPosition(){ return _state.position; }
		inline UCHAR getAction(){ return _state.action; }

		virtual void setFloor(float floorY);

		virtual void stay();
		virtual void move(UNIT_DIRECT direct);
		virtual void jump();
		virtual void freeFall();
		virtual void floor();
		virtual void action();
	private:
		void unitStateupdate();

	protected:
		virtual void renew();
	};
}