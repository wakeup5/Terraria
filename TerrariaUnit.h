#pragma once
#include "TerrariaObject.h"
#include "Physical.h"



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

	/*
#define UNIT_STATE_DIRECT 0
#define UNIT_STATE_VIEW 2
#define UNIT_STATE_MOVEMENT 4
#define UNIT_STATE_POSITION 8
#define UNIT_STATE_ACTION 12
	*/
	static const unsigned short DIRECT = 0U;
	static const unsigned short VIEW = 2U;
	static const unsigned short MOVEMENT = 4U;
	static const unsigned short POSITION = 8U;
	static const unsigned short ACTION = 12U;

	union UnitState
	{
		USHORT total;
		struct {
			UCHAR direct : 2;
			UCHAR view : 2;
			UCHAR movement : 4;
			UCHAR position : 4;
			UCHAR action : 4;
		};
	};

#define US(direct, view, movement, position, action) ((direct << DIRECT) + (view << VIEW) + (movement << MOVEMENT) + (position << POSITION) + (action << ACTION))

	enum UNIT_DIRECT
	{
		LEFT = (UCHAR)1,
		RIGHT = (UCHAR)2
	};
	enum _UNIT_VIEW_DIRECT
	{
		VIEW_LEFT = (UCHAR)1,
		VIEW_RIGHT = (UCHAR)2
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
		ACTION_STAY = (UCHAR)0,
		ACTION_SWING = (UCHAR)1,
		ACTION_SHOOT = (UCHAR)2,
		ACTION_MAGIC = (UCHAR)3,
		ACTION_NONE = (UCHAR)4
	};

	/*
	enum UNIT_STATE
	{
		UNIT_STATE_STAY_LEFT				= (LEFT << DIRECT)	+ (LEFT << VIEW)	+ (STAY << MOVEMENT) + (FLOOR << POSITION),
		UNIT_STATE_STAY_RIGHT				= (RIGHT << DIRECT)	+ (STAY << MOVEMENT) + (FLOOR << POSITION),
		UNIT_STATE_MOVE_LEFT				= (LEFT << DIRECT) + (LEFT << VIEW) + (MOVE << MOVEMENT) + (FLOOR << POSITION),
		UNIT_STATE_MOVE_RIGHT				= (RIGHT << DIRECT)	+ (MOVE << MOVEMENT) + (FLOOR << POSITION),
		UNIT_STATE_JUMP_LEFT				= (LEFT << DIRECT) + (LEFT << VIEW) + (STAY << MOVEMENT) + (JUMP << POSITION),
		UNIT_STATE_JUMP_RIGHT				= (RIGHT << DIRECT)	+ (STAY << MOVEMENT) + (JUMP << POSITION),
		UNIT_STATE_JUMP_MOVE_LEFT			= (LEFT << DIRECT) + (LEFT << VIEW) + (MOVE << MOVEMENT) + (JUMP << POSITION),
		UNIT_STATE_JUMP_MOVE_RIGHT			= (RIGHT << DIRECT)	+ (MOVE << MOVEMENT) + (JUMP << POSITION),
		UNIT_STATE_SWING_LEFT				= (LEFT << DIRECT) + (LEFT << VIEW) + (STAY << MOVEMENT) + (FLOOR << POSITION) + (ACTION_SWING << ACTION),
		UNIT_STATE_SWING_RIGHT				= (RIGHT << DIRECT)	+ (STAY << MOVEMENT) + (FLOOR << POSITION)	+ (ACTION_SWING << ACTION),
		UNIT_STATE_SWING_MOVE_LEFT			= (LEFT << DIRECT) + (LEFT << VIEW) + (MOVE << MOVEMENT) + (FLOOR << POSITION) + (ACTION_SWING << ACTION),
		UNIT_STATE_SWING_MOVE_RIGHT			= (RIGHT << DIRECT)	+ (MOVE << MOVEMENT) + (FLOOR << POSITION)	+ (ACTION_SWING << ACTION),
		UNIT_STATE_SWING_JUMP_LEFT			= (LEFT << DIRECT) + (LEFT << VIEW) + (STAY << MOVEMENT) + (JUMP << POSITION) + (ACTION_SWING << ACTION),
		UNIT_STATE_SWING_JUMP_RIGHT			= (RIGHT << DIRECT)	+ (STAY << MOVEMENT) + (JUMP << POSITION)	+ (ACTION_SWING << ACTION),
		UNIT_STATE_SWING_JUMP_MOVE_LEFT		= (LEFT << DIRECT) + (LEFT << VIEW) + (MOVE << MOVEMENT) + (JUMP << POSITION) + (ACTION_SWING << ACTION),
		UNIT_STATE_SWING_JUMP_MOVE_RIGHT	= (RIGHT << DIRECT)	+ (MOVE << MOVEMENT) + (JUMP << POSITION)	+ (ACTION_SWING << ACTION),
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
	*/

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

		int _mhp;
		float _hp;
		int _mmp;
		float _mp;
		int _attack;
		int _defense;

		bool _isCollisionTile;
	public:
		Unit();
		virtual ~Unit();

		virtual HRESULT initialize();
		virtual void release();
		virtual void update();
		virtual void render(HDC hdc);

		//void order(UNIT_ORDER order){ _order = order; }
		//void addOrder(UNIT_ORDER order){ _order += order; }

		inline void setMoveAccel(float moveAccel){ _moveAccel = moveAccel; }
		inline void setMoveSpeed(float moveSpeed){ _moveSpeed = moveSpeed; }
		inline void setJumpSpeed(float jumpSpeed){ _jumpSpeed = jumpSpeed; }
		inline void setAttackTime(float attackTime){ _attackTime = attackTime; }

		inline float getMoveAccel(){ return _moveAccel; }
		inline float getMoveSpeed(){ return _moveSpeed; }
		inline float getJumpSpeed(){ return _jumpSpeed; }
		inline float getAttackTime(){ return _attackTime; }

		inline UINT getState(){ return _state.total; }
		inline void setState(UnitState state){ _state = state; }

		inline UnitState getUnitState(){ return _state; }

		inline void setDirect(UCHAR direct){ _state.direct = direct; }
		inline void setView(UCHAR view){ _state.view = view; }
		inline void setMovement(UCHAR movement){ _state.movement = movement; }
		inline void setPosition(UCHAR position){ _state.position = position; }
		inline void setAction(UCHAR action){ _state.action = action; }

		inline UCHAR getDirect(){ return _state.direct; }
		inline UCHAR getView(){ return _state.view; }
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
		virtual void hit(UNIT_DIRECT direct, int atk = 0);

		inline void setUnitInfo(int hp, int mp, int atk, int def){ _hp = _mhp = hp; _mp = _mmp = mp; _attack = atk; _defense = def; }
		inline virtual void setHp(float hp){ _hp = hp; }
		inline virtual void setMp(float mp){ _mp = mp; }
		inline virtual void setAtk(int atk){ _attack = atk; }
		inline virtual void setDef(int def){ _defense = def; }
		inline virtual float getHp(){ return _hp; }
		inline virtual float getMp(){ return _mp; }
		inline virtual int getAtk(){ return _attack; }
		inline virtual int getDef(){ return _defense; }
		inline virtual int getMaxHp(){ return _mhp; }
		inline virtual int getMaxMp(){ return _mmp; }

		inline void setTileCollision(bool collision){ _isCollisionTile = collision; }
		inline bool isTileCollision(){ return _isCollisionTile; }

	private:
		void unitStateupdate();

	protected:
		virtual void renew();
	};
}