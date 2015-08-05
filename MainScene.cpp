#include "stdafx.h"
#include "MainScene.h"


MainScene::MainScene()
{
}


MainScene::~MainScene()
{

}

HRESULT MainScene::initialize()
{
	Image* _singlePlayerImage = IMAGEMANAGER->addImage("singlePlayerButton", "resource/image/main/single player.bmp", 615, 46, TRUE, TRANS_COLOR);
	Image* _settingImage = IMAGEMANAGER->addImage("settingButton", "resource/image/main/setting.bmp", 378, 46, TRUE, TRANS_COLOR);
	Image* _exitImage = IMAGEMANAGER->addImage("exitButton", "resource/image/main/exit.bmp", 180, 32, TRUE, TRANS_COLOR);

	_logo = IMAGEMANAGER->addImage("mainLogo", "resource/image/main/logo.bmp", 486, 142, TRUE, TRANS_COLOR);

	_singlePlayer = new Button;
	_singlePlayer->initialize(_singlePlayerImage, _option.width() / 2.0f, 250);
	_singlePlayer->onCLickUp([](){
		SCENEMANAGER->changeScene("loading");
	});
	_setting = new Button;
	_setting->initialize(_settingImage, _option.width() / 2.0f, 310);
	_setting->onCLickUp([](){
		static bool isBig = false;

		if (isBig ? isBig = false : isBig = true) _option.setScreenSize(1024, 768);
		else _option.setScreenSize(800, 600);
	});
	_exit = new Button;
	_exit->initialize(_exitImage, _option.width() / 2, 370);
	_exit->onCLickUp([](){
		PostMessage(_hWnd, WM_DESTROY, 0, 0);
	});

	_black = IMAGEMANAGER->addImage("logo_black", "resource/image/logo/logo_black.bmp", 800, 600);

	_startAlpha = false;
	_alpha = 255;
	return S_OK;
}
void MainScene::release()
{
	SAFE_RELEASE(_singlePlayer);
	SAFE_RELEASE(_setting);
	SAFE_RELEASE(_exit);
}
void MainScene::update()
{
	_singlePlayer->setCenter(_option.width() / 2.0f, 250);
	_setting->setCenter(_option.width() / 2.0f, 310);
	_exit->setCenter(_option.width() / 2.0f, 370);

	startBlackAlpha();

	_option.setCamera(_offsetX += 3, 0);

	_logo->setCenter(_option.width() / 2, 120);

	_exit->update();
	_setting->update();
	_singlePlayer->update();
}
void MainScene::render()
{
	Terraria::Background::getSingleton()->render(getMemDC());

	_logo->sizeRotateRender(getMemDC(), 0.8 - (sin(TIMEMANAGER->getWorldTime() / 2) * 0.15), (sin(TIMEMANAGER->getWorldTime()  / 3) * 0.2));

	_singlePlayer->render();
	_setting->render();
	_exit->render();

	if (!_startAlpha) _black->sizeRender(getMemDC(), 0, 0, _option.width(), _option.height(), _alpha);
}

void MainScene::startBlackAlpha()
{
	if (!_startAlpha)
	{
		_time += TIMEMANAGER->getElapsedTime();
		_alpha = 255 - (_time / 2) * 254;
		if (_time > 2)
		{
			_startAlpha = true;
		}
	}
}