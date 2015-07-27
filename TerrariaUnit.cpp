#include "stdafx.h"
#include "TerrariaUnit.h"

using namespace myUtil;

namespace Terraria
{
	Unit::Unit()
	{
	}

	Unit::~Unit()
	{
	}

	HRESULT Unit::initialize()
	{
		_order = (UNIT_INPUT_ORDER)0;

		setMoveAccel(0);
		setMoveSpeed(0);
		setJumpSpeed(-500);

		setCenter(0, 0);
		setSize(0, 0);
		setMaxSpeed(getMoveSpeed());
		setMaxAccel(getMoveAccel());
		setSpeed(0);
		setAccel(0);
		setAngleD(90);

		_isAttack = false;

		return S_OK;
	}

	void Unit::release()
	{

	}

	void Unit::update()
	{

		if (existBit(_order, ORDER_MOVE_LEFT))
		{
			setAccelX(-getMoveAccel());
		}
		else if (existBit(_order, ORDER_MOVE_RIGHT))
		{
			setAccelX(getMoveAccel());
		}
		else 
		{
			if (abs(getSpeedX()) < 10)
			{
				setAccelX(0);
				setSpeedX(0);
			}
			else
			{
				setAccelX(getMoveAccel() * -sign(getSpeedX()));
			}
		}

		if (existBit(_order, ORDER_JUMP) && getState() != UNIT_STATE_FREEFALL)
		{
			setSpeedY(getJumpSpeed());
			setState(UNIT_STATE_FREEFALL);
		}
		else if (existBit(_order, ORDER_ATTACK) && !_isAttack)
		{
			_isAttack = true;
			_attackFrameTime = 0;
		}

		if (_isAttack)
		{
			_attackFrameTime += TIMEMANAGER->getElapsedTime();
			if (_attackFrameTime > 0.5) _isAttack = false;
			stateAttack();
		}

		//이동속도가 최고속도를 넘었을때
		if (abs(getSpeedX()) > getMoveSpeed())
		{
			setSpeedX(getMoveSpeed() * sign(getSpeedX()));
		}

		if (_isAttack)
		{
			stateAttack();
		}
		else if (_state == UNIT_STATE_FREEFALL)
		{
			stateFreeFall();
		}
		else if (abs(getSpeedX()) < FLOAT_EPSILON)
		{
			stateStay();
		}
		else
		{
			if (sign(getSpeedX()) < 0)
			{
				stateMoveLeft();
			}
			else
			{
				stateMoveRight();
			}
		}

		activate();
		action();
	}

	void Unit::render(HDC hdc)
	{

	}

	void Unit::action()
	{
		
	}

	void Unit::setFloor(float floorY)
	{
		if (getRect().bottom + 1 > floorY)
		{
			setState(UNIT_STATE_STAY);
			setSpeedY(0);
			setAccelY(0);
			setY(floorY - (getHeight() / 2) + 1);
		}
		else
		{
			setState(UNIT_STATE_FREEFALL);
			setAccelY(GRAVITY_ACCEL);
		}
	}

	void Unit::stateMoveLeft()
	{
		//setAccelX(-getMoveAccel());
	}
	void Unit::stateMoveRight()
	{
		//setAccelX(getMoveAccel());
	}
	void Unit::stateFreeFall()
	{

	}
	void Unit::stateAttack()
	{

	}
	void Unit::stateStay()
	{

	}
}