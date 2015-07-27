#pragma once
class GameObject
{
protected:
	float _centerX;
	float _centerY;

	int _width;
	int _height;

	float _angleD;
	float _angleR;

	float _speed;
	float _speedX;
	float _speedY;

	float _accel;
	float _accelX;
	float _accelY;

	RECT _rect;

public:
	GameObject();
	~GameObject();

	void initialize(float centerX, float centerY, int width = 0, int height = 0, float angleD = 0.0f, float speed = 0.0f);

	void setPosition(POINT p) { _centerX = p.x, _centerY = p.y; updateRect(); }
	void setPosition(float x, float y) { _centerX = x, _centerY = y; updateRect(); }
	POINT getPosition(){ return POINT{ _centerX, _centerY }; }

	void setCenter(POINT p){ setPosition(p); }
	void setCenter(float x, float y){ setPosition(x, y); }
	POINT getCenter(){ return POINT{ _centerX, _centerY }; }

	void setX(float x){ _centerX = x; updateRect(); }
	float getY(){ return _centerY; }
	void setY(float y){ _centerY = y; updateRect(); }
	float getX(){ return _centerX; }

	void setWidth(int width){ _width = width; updateRect(); }
	int getWidth(){ return _width; }
	void setHeight(int height){ _height = height; updateRect(); }
	int getHeight(){ return _height; }
	
	void setSize(int width, int height){ _width = width; _height = height; updateRect(); }
	void updateRect(){ _rect = makeRectCenter(_centerX, _centerY, _width, _height); }
	RECT getRect(){ return _rect; }
	RECT getUpdateRect() { updateRect(); return _rect; }

	void setAngleD(float angleD);
	float getAngleD();
	void setAngleR(float angleR);
	float getAngleR();

	void setSpeedX(float speedX);
	float getSpeedX();
	void setSpeedY(float speedY);
	float getSpeedY();
	void setSpeed(float speed);
	float getSpeed();

	void setAccelX(float accelX);
	float getAccelX();
	void setAccelY(float accelY);
	float getAccelY();
	void setAccel(float accel);
	float getAccel();

	virtual void activate();
	virtual void activate(float gravity);
};

