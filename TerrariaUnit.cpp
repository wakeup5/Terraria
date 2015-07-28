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
		activate();
		renew();
		unitStateupdate();

		return;
		if (getRect().left < 0)
		{
			setSpeedX(0);
			setAccelX(0);
			setX(0 + getWidth() / 2);
		}

		if (getRect().right >= getWidth())
		{
			setSpeedX(0);
			setAccelX(0);
			setX(getWidth() - getWidth() / 2);
		}

		if (getRect().top < 0)
		{
			setSpeedY(0);
			setAccelY(0);
			setY(0 + getHeight() / 2);
		}

		if (getRect().bottom >= getHeight())
		{
			setSpeedY(0);
			setAccelY(0);
			setY(getHeight() - getHeight() / 2);
		}
	}

	void Unit::render(HDC hdc)
	{

	}

	void Unit::unitStateupdate()
	{
		if (_state.movement == MOVE)
		{
			if (_state.direct == LEFT)
			{
				setAccelX(-getMoveAccel());
			}
			else if (_state.direct == RIGHT)
			{
				setAccelX(getMoveAccel());
			}

			if (abs(getSpeedX()) > getMoveSpeed())
			{
				setAccelX(0);
				setSpeedX(getMoveSpeed() * sign(getSpeedX()));
			}
		}
		else if (_state.movement == STAY)
		{
			if (abs(getSpeedX()) > 20)
			{
				setAccelX(getMoveAccel() * -sign(getSpeedX()));
			}
			else
			{
				setSpeedX(0);
				setAccelX(0);
			}
		}
		printf("%d, %d, %d, %d = %d(%x)\n", _state.direct, _state.movement, _state.position, _state.action, getState(), getState());
	}

	void Unit::renew()
	{
		if (_state.position != FLOOR)
		{
			setAccelY(GRAVITY_ACCEL);
		}
	}

	void Unit::setFloor(float floorY)
	{
		//setPosition(JUMP);
		if (getRect().bottom + 1 > floorY)
		{
			//setPosition(FLOOR);
			setSpeedY(0);
			setAccelY(0);
			setY(floorY - (getHeight() / 2) + 1);
		}
	}

	void Unit::jump()
	{
		if (_state.position == FLOOR)
		{
			setPosition(JUMP);
			setSpeedY(JUMP_SPEED);
			freeFall();
		}
	}

	void Unit::freeFall()
	{
		setPosition(JUMP);
	}

	void Unit::floor()
	{
		setPosition(FLOOR);
		setSpeedY(0);
		setAccelY(0);
	}

	void Unit::action()
	{

	}

	void Unit::stay()
	{
		setMovement(STAY);
	}
	void Unit::move(UNIT_DIRECT direct)
	{
		setMovement(MOVE);
		setDirect(direct);
	}

}