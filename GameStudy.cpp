#include "stdafx.h"
#include "GameStudy.h"

#include "TestScene.h"
#include "LogoScene.h"
#include "MainScene.h"
#include "MainGameScene.h"
#include "ItemManager.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);

	imageLoad();
	soundLoad();

	ITEMMANAGER->initialize();

	Terraria::Background::getSingleton()->initailize();

	SCENEMANAGER->addScene("test", new TestScene());

	SCENEMANAGER->addScene("logo", new LogoScene());
	SCENEMANAGER->addScene("main", new MainScene());
	SCENEMANAGER->addScene("mainGame", new MainGameScene());
	SCENEMANAGER->changeScene("main");

	_option.setVolume(0.5);

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();

	ITEMMANAGER->release();
	ITEMMANAGER->releaseSingleton();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

	EFFECTMANAGER->update();
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
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
	IMAGEMANAGER->addImage("tile grass", IMAGE("tile/grass"), 288, 270, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("tile stone", IMAGE("tile/stone"), 288, 270, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("tile silver", IMAGE("tile/silver"), 288, 270, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("tile gold", IMAGE("tile/gold"), 288, 270, TRUE, TRANS_COLOR);

	IMAGEMANAGER->addImage("tile dark", IMAGE("tile/dark"), 16, 16);

	//아이템
	IMAGEMANAGER->addImage("body 46 image", IMAGE("/item/Female_Body_46_Image"), 38, 32, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("body 46", IMAGE("/item/Female_Body_46"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("pant 46 image", IMAGE("/item/Armor_Legs_46_Image"), 22, 18, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("pant 46", IMAGE("/item/Armor_Legs_46"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("pickaxe basic", IMAGE("/item/tool/pickaxe_basic"), 32, 32, TRUE, TRANS_COLOR);

	IMAGEMANAGER->addImage("item tile grass", IMAGE("/item/tile/tile grass"), 16, 16, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("item tile stone", IMAGE("/item/tile/tile stone"), 16, 16, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("item tile silver", IMAGE("/item/tile/tile silver"), 16, 16, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("item tile gold", IMAGE("/item/tile/tile gold"), 16, 16, TRUE, TRANS_COLOR);

	IMAGEMANAGER->addImage("helmet silver", IMAGE("/item/equip/helmet silver"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("helmet silver image", IMAGE("/item/equip/helmet silver image"), 24, 22, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("body silver", IMAGE("/item/equip/body silver"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("body silver image", IMAGE("/item/equip/body silver image"), 30, 18, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("pant silver", IMAGE("/item/equip/pant silver"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("pant silver image", IMAGE("/item/equip/pant silver image"), 22, 18, TRUE, TRANS_COLOR);

	IMAGEMANAGER->addImage("helmet gold", IMAGE("/item/equip/helmet gold"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("helmet gold image", IMAGE("/item/equip/helmet gold image"), 26, 22, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("body gold", IMAGE("/item/equip/body gold"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("body gold image", IMAGE("/item/equip/body gold image"), 30, 18, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("pant gold", IMAGE("/item/equip/pant gold"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("pant gold image", IMAGE("/item/equip/pant gold image"), 22, 18, TRUE, TRANS_COLOR);

	IMAGEMANAGER->addImage("body costume", IMAGE("/item/equip/body costume"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("body costume image", IMAGE("/item/equip/body costume image"), 32, 32, TRUE, TRANS_COLOR);

	IMAGEMANAGER->addImage("sword basic", IMAGE("/item/weapon/sword basic"), 32, 32, TRUE, TRANS_COLOR);

	//플레이어
	IMAGEMANAGER->addImage("player head", IMAGE("player/head"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("player body", IMAGE("player/body"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("player leg", IMAGE("player/leg"), 80, 1120, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("player hair", IMAGE("player/hair"), 80, 1120, TRUE, TRANS_COLOR);

	//배경
	IMAGEMANAGER->addImage("bgSky", IMAGE("background/sky"), 48, 1300, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("bg grass hear", IMAGE("background/grass/hear"), 1024, 509, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("bg grass that", IMAGE("background/grass/that"), 1024, 346, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("bg grass there", IMAGE("background/grass/there"), 1024, 435, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("bgUnder", IMAGE("background/under"), 160, 96, TRUE, TRANS_COLOR);

	//ui
	IMAGEMANAGER->addImage("ui inven back", IMAGE("ui/Inventory_Back"), 52, 52, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ui inven back select", IMAGE("ui/inventory_back_select"), 52, 52, TRUE, TRANS_COLOR);
}

void GameStudy::soundLoad()
{
	//타일
	SOUNDMANAGER->addSound("grass dig 0", SOUND("tile/grass dig 0.wav"), false, false);
	SOUNDMANAGER->addSound("grass dig 1", SOUND("tile/grass dig 1.wav"), false, false);
	SOUNDMANAGER->addSound("grass dig 2", SOUND("tile/grass dig 2.wav"), false, false);

	SOUNDMANAGER->addSound("iron dig 0", SOUND("tile/iron dig 0.wav"), false, false);
	SOUNDMANAGER->addSound("iron dig 1", SOUND("tile/iron dig 1.wav"), false, false);
	SOUNDMANAGER->addSound("iron dig 2", SOUND("tile/iron dig 2.wav"), false, false);

	//플레이어
	SOUNDMANAGER->addSound("player run", SOUND("player/run.wav"), false, false);

	//ui
	SOUNDMANAGER->addSound("ui grab", SOUND("ui/grab.wav"), false, false);
	SOUNDMANAGER->addSound("ui open", SOUND("ui/menu_open.wav"), false, false);
	SOUNDMANAGER->addSound("ui close", SOUND("ui/menu_close.wav"), false, false);
}