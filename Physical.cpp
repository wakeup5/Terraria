#include "stdafx.h"
#include "Physical.h"

namespace Terraria
{
	Terraria::Physical::Physical()
	{
		_angleD = 90;
		_angleR = M_PI / 2;
		_speed = _maxSpeed = _speedX = _maxSpeedX = _speedY = _maxSpeedY = 0.0f;
		_accel = _maxAccel = _accelX = _maxAccelX = _accelY = _maxAccelY = 0.0f;
	}

	Physical::~Physical()
	{

	}

	void Physical::setAngleD(float angleD)
	{
		_angleD = angleD;
		while (_angleD < 0) _angleD += 360;
		while (_angleD > 360) _angleD -= 360;

		_angleR = degreeToRadian(_angleD);

		_speedX = _speed * cos(_angleR);
		_speedY = -_speed * sin(_angleR);
	}
	void Physical::setAngleR(float angleR)
	{
		_angleR = angleR;
		while (_angleR < 0) _angleR += 2 * M_PI;
		while (_angleR >= 2 * M_PI) _angleR -= 2 * M_PI;

		_angleD = radianToDegree(_angleR);

		_speedX = _speed * cos(_angleR);
		_speedY = -_speed * sin(_angleR);
	}
	void Physical::setSpeed(float speed)
	{
		_speed = speed;

		if (_speed < -_maxSpeed) _speed = -_maxSpeed;
		if (_speed > _maxSpeed) _speed = _maxSpeed;

		_speedX = _speed * cos(_angleR);
		_speedY = -_speed * sin(_angleR);
		
	}
	void Physical::setMaxSpeed(float maxSpeed)
	{
		_maxSpeed = maxSpeed;

		_maxSpeedX = _maxSpeed * cos(_maxSpeed);
		_maxSpeedY = -_maxSpeed * sin(_maxSpeed);
	}
	void Physical::setSpeedX(float speedX)
	{
		_speedX = speedX;

		if (_speedX < -_maxSpeed) _speedX = -_maxSpeed;
		if (_speedX > _maxSpeed) _speedX = _maxSpeed;

		_angleR = atan2(-_speedY, _speedX);
		while (_angleR < 0) _angleR += 2 * M_PI;
		while (_angleR >= 2 * M_PI) _angleR -= 2 * M_PI;
		_angleD = radianToDegree(_angleR);

		_speed = (sqrt(pow(_speedX, 2) + pow(_speedY, 2))) * myUtil::sign(_speedX) * myUtil::sign(_speedY);
	}
	void Physical::setSpeedY(float speedY)
	{
		_speedY = speedY;

		if (_speedY < -_maxSpeed) _speed = -_maxSpeed;
		if (_speedY > _maxSpeed) _speed = _maxSpeed;

		_angleR = atan2(-_speedY, _speedX);
		while (_angleR < 0) _angleR += 2 * M_PI;
		while (_angleR >= 2 * M_PI) _angleR -= 2 * M_PI;
		_angleD = radianToDegree(_angleR);

		_speed = (sqrt(pow(_speedX, 2) + pow(_speedY, 2))) * myUtil::sign(_speedY) * myUtil::sign(_speedX);
	}
	void Physical::setAccel(float accel)
	{
		_accel = accel;

		_accelX = _accel * cos(_angleR);
		_accelY = -_accel * sin(_angleR);

		//setSpeed(_speed + (_accel));
	}
	void Physical::setMaxAccel(float maxAccel)
	{
		_maxAccel = maxAccel;
	}
	void Physical::setAccelX(float accelX)
	{
		_accelX = accelX;

		_accel = (sqrt(pow(_accelX, 2) + pow(_accelY, 2)));

		//_angleR = atan2(_speedY - _accelY, _speedX + _accelX);
		//_angleD = radianToDegree(_angleR);

		//if (abs(_accel) > _maxAccel) setAccel(_maxAccel * (_accel / abs(_accel)));
	}
	void Physical::setAccelY(float accelY)
	{
		_accelY = accelY;

		_accel = (sqrt(pow(_accelX, 2) + pow(_accelY, 2)));

		//_angleR = atan2(_speedY - _accelY, _speedX + _accelX);
		//_angleD = radianToDegree(_angleR);

		//if (abs(_accel) > _maxAccel) setAccel(_maxAccel * (_accel / abs(_accel)));
	}

	void Physical::activate(double elapsedTime)
	{
		if (elapsedTime < FLOAT_EPSILON) elapsedTime = TIMEMANAGER->getElapsedTime();

		_speedX += _accelX * elapsedTime;
		_speedY += _accelY * elapsedTime;
		
		_angleR = atan2(-_speedY, _speedX);
		_angleD = radianToDegree(_angleR);

		setSpeed(sqrt(pow(_speedX, 2) + pow(_speedY, 2)));

		setX(getX() + _speedX * elapsedTime);
		setY(getY() + _speedY * elapsedTime);

		updateRect();
	}

	float Physical::radianToDegree(float radian)
	{
		return radian * 180 / M_PI;
	}
	float Physical::degreeToRadian(float degree)
	{
		return degree * M_PI / 180;
	}
}