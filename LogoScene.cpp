#include "stdafx.h"
#include "LogoScene.h"


LogoScene::LogoScene()
{

}


LogoScene::~LogoScene()
{
}
HRESULT LogoScene::initialize()
{
	_logo = IMAGEMANAGER->addImage("logo", "resource/image/logo/logo.bmp", 800, 600);
	_logoBlack = IMAGEMANAGER->addImage("logo_black", "resource/image/logo/logo_black.bmp", 800, 600);

	_alpha = 255;

	_time = 0;
	_state = LOGO_STATE_START;

	return S_OK;
}
void LogoScene::release()
{

}
void LogoScene::update()
{
	if (_state == LOGO_STATE_START)
	{
		_time += TIMEMANAGER->getElapsedTime();
		_alpha = 255 - ((float)_time / 2) * 254;
		if (_time >= 2)
		{
			_time = 0;
			_state = LOGO_STATE_VIEW;
		}
	}
	else if (_state == LOGO_STATE_VIEW)
	{
		_time += TIMEMANAGER->getElapsedTime();
		if (_time >= 1)
		{
			_time = 0;
			_state = LOGO_STATE_END;
		}
	}
	else if (_state == LOGO_STATE_END)
	{
		_time += TIMEMANAGER->getElapsedTime();
		_alpha = ((float)_time / 2) * 254;
		if (_time >= 2)
		{
			SCENEMANAGER->changeScene("main");
		}
	}
}
void LogoScene::render()
{
	_logo->render(getMemDC(), 0, 0, 0, 0, _option.width(), _option.height());
	_logoBlack->render(getMemDC(), 0, 0, 0, 0, _option.width(), _option.height(), _alpha);
}