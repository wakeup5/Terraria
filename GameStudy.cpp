#include "stdafx.h"
#include "GameStudy.h"

#include "TestScene.h"
#include "LogoScene.h"
#include "MainScene.h"
#include "MainGameScene.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);

	imageLoad();

	SCENEMANAGER->addScene("test", new TestScene());

	SCENEMANAGER->addScene("logo", new LogoScene());
	SCENEMANAGER->addScene("main", new MainScene());
	SCENEMANAGER->addScene("mainGame", new MainGameScene());
	SCENEMANAGER->changeScene("mainGame");

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
	SCENEMANAGER->release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

	EFFECTMANAGER->update();
	SCENEMANAGER->update();
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->findImage("backMap")->render(getMemDC(), 0, 0, _option.width(), _option.height(), 0, 0, 10, 10);
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	GameNode::render();
}

void GameStudy::imageLoad()
{
	IMAGEMANAGER->addImage("backMap", "backMap.bmp", 10, 10);

	//타일
	IMAGEMANAGER->addImage("tile grass", IMAGE("tile/grass"), 288, 54, TRUE, TRANS_COLOR);
	//아이템

	//플레이어
}