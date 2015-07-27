#include "stdafx.h"
#include "ProgressBar.h"


ProgressBar::ProgressBar()
{
}


ProgressBar::~ProgressBar()
{
}

HRESULT ProgressBar::initialize(Image* bar, Image* back, float dx, float dy)
{
	_bar = bar;
	_back = back;
	_dx = dx;
	_dy = dy;

	return S_OK;
}
void ProgressBar::release()
{

}
void ProgressBar::update()
{
	if (_back) _back->setCenter(_x + _dx, _y + _dy);
	if (_bar) _bar->setCenter(_x + _dx, _y + _dy);
}
void ProgressBar::render(HDC hdc)
{
	float max = _max;
	float current = _current;
	if (max <= 0) max = 1.0f;
	if (current <= 0) current = 1.0f;

	if (_back) _back->render(hdc, _x + _dx - _bar->getWidth() / 2, _y + _dy - _bar->getHeight() / 2);
	if (_bar) _bar->render(hdc, _x + _dx - _bar->getWidth() / 2, _y + _dy - _bar->getHeight() / 2, 0, 0, (float)_bar->getWidth() * (current / max), _bar->getHeight());
}

void ProgressBar::setInfo(float max, float current)
{
	_max = max;
	_current = current;
}
void ProgressBar::setCenter(float x, float y)
{
	_x = x;
	_y = y;
}