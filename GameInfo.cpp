#include "stdafx.h"
#include "GameInfo.h"

GameInfo::GameInfo()
{
	_screenStartX = WIN_START_X;
	_screenStartY = WIN_START_Y;
}
GameInfo::~GameInfo()
{

}

void GameInfo::setScreenSize(int width, int height)
{
	setSize(width, height);

	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hWnd, NULL, _screenStartX, _screenStartY, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);

	GameNode::setBackBuffer(width, height);
}

void GameInfo::setCamera(float x, float maxX, float y, float maxY)
{
	if (x < _option.width() / 2) x = _option.width() / 2;
	if (x > maxX - _option.width() / 2) x = maxX - _option.width() / 2;
	if (y < _option.height() / 2) y = _option.height() / 2;
	if (y > maxY - _option.height() / 2) y = maxY - _option.height() / 2;

	setCamera(x, y);
}

void GameInfo::setInMousePoint(POINT p)
{
	_innerMousePoint.x = _cameraX - _screenWidth / 2 + p.x;
	_innerMousePoint.y = _cameraY - _screenHeight / 2 + p.y;
}