#pragma once
#include "Unit.h"
class Scourge :
	public Unit
{
public:
	Scourge();
	~Scourge();

	virtual HRESULT initialize(float x, float y, float angleD, float speed);
	virtual void release(void);

	virtual void move();
	virtual void draw(HDC);
	virtual void frame();
};

