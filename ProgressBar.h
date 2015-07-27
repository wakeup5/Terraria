#pragma once
#include "GameNode.h"
class ProgressBar
{
private:
	Image* _bar = NULL;
	Image* _back = NULL;

	float _max;
	float _current;
	float _x, _y;
	float _dx, _dy;
public:
	ProgressBar();
	~ProgressBar();

	HRESULT initialize(Image* bar, Image* back, float dx, float dy);
	void release();
	void update();
	void render(HDC);

	void setInfo(float max, float current);
	void setCenter(float x, float y);
};

