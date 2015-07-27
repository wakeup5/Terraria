#pragma once
#include <cmath>
#include "TerrariaObject.h"

namespace Terraria
{
	class Physical : public Object
	{
	private:
		float _angleD;
		float _angleR;
		
		float _speed;
		float _maxSpeed;

		float _speedX;
		float _maxSpeedX;
		float _speedY;
		float _maxSpeedY;

		float _accel;
		float _maxAccel;

		float _accelX;
		float _maxAccelX;
		float _accelY;
		float _maxAccelY;

	public:
		inline float getAngleD() { return _angleD; }
		inline float getAngleR() { return _angleR; }
		inline float getAngle(bool isRadian) { return (isRadian) ? _angleR : _angleD; }
		inline float getSpeed() { return _speed; }
		inline float getMaxSpeed(){ return _maxSpeed; }
		inline float getSpeedX(){ return _speedX; }
		inline float getMaxSpeedX(){ return _maxSpeedX; }
		inline float getSpeedY(){ return _speedY; }
		inline float getMacSpeedY(){ return _maxSpeedY; }
		inline float getAccel(){ return _accel; }
		inline float getMaxAccel(){ return _maxAccel; }
		inline float getAccelX(){ return _accelX; }
		inline float getMaxAccelX(){ return _maxAccelX; }
		inline float getAccelY(){ return _accelY; }
		inline float getMaxAccelY(){ return _maxAccelY; }

		void setAngleD(float angleD);
		void setAngleR(float angleR);
		void setSpeed(float speed);
		void setMaxSpeed(float maxSpeed);
		void setSpeedX(float speedX);
		void setSpeedY(float speedY);
		void setAccel(float accel);
		void setMaxAccel(float maxAccel);
		void setAccelX(float accelX);
		void setAccelY(float accelY);

		virtual void activate(double elapsedTime = 0.0f);

	private:
		float radianToDegree(float radian);
		float degreeToRadian(float degree);

	public:
		Physical();
		virtual ~Physical();

	};
}

