#include "stdafx.h"
#include "LoadingScene.h"


LoadingScene::LoadingScene()
{

}

LoadingScene::~LoadingScene()
{

}

HANDLE thread;
DWORD dwThread;

DWORD WINAPI loadingThread1(LPVOID lpParam)
{
	Loading* load = (Loading*)lpParam;

	while (load->loadNext());// { Sleep(RANDOM->getIntTo(20, 200)); }

	SCENEMANAGER->changeScene("mainGame");

	return 0;
}

HRESULT LoadingScene::initialize()
{
	_loading = new Loading;
	_loading->initialize();

	loadingImage();
	loadingSound();
	
	_logo = IMAGEMANAGER->addImage("mainLogo", "resource/image/main/logo.bmp", 486, 142, TRUE, TRANS_COLOR);
	_logo->setCenter(_option.width() / 2, 120);

	thread = CreateThread(NULL, 0, loadingThread1, _loading, 0, &dwThread);

	_offsetX = 0;

	return S_OK;
}
void LoadingScene::release()
{
	_loading->release();
	SAFE_DELETE(_loading);
}
void LoadingScene::update()
{
	_option.setCamera(_offsetX += 3, 0);
}
void LoadingScene::render()
{
	Terraria::Background::getSingleton()->render(getMemDC());
	_logo->sizeRotateRender(getMemDC(), 0.8 - (sin(TIMEMANAGER->getWorldTime() / 2) * 0.15), (sin(TIMEMANAGER->getWorldTime() / 3) * 0.2));

	if (_loading != NULL) _loading->render(getMemDC());
}

void LoadingScene::loadingImage()
{
	//타일
	_loading->loadImage("tile grass", IMAGE("tile/grass"), 288, 270, TRUE, TRANS_COLOR);
	_loading->loadImage("tile stone", IMAGE("tile/stone"), 288, 270, TRUE, TRANS_COLOR);
	_loading->loadImage("tile silver", IMAGE("tile/silver"), 288, 270, TRUE, TRANS_COLOR);
	_loading->loadImage("tile gold", IMAGE("tile/gold"), 288, 270, TRUE, TRANS_COLOR);

	_loading->loadImage("tile dark", IMAGE("tile/dark"), 16, 16, FALSE, TRANS_COLOR);

	//아이템
	_loading->loadImage("body 46 image", IMAGE("/item/Female_Body_46_Image"), 38, 32, TRUE, TRANS_COLOR);
	_loading->loadImage("body 46", IMAGE("/item/Female_Body_46"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("pant 46 image", IMAGE("/item/Armor_Legs_46_Image"), 22, 18, TRUE, TRANS_COLOR);
	_loading->loadImage("pant 46", IMAGE("/item/Armor_Legs_46"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("pickaxe basic", IMAGE("/item/tool/pickaxe_basic"), 32, 32, TRUE, TRANS_COLOR);

	_loading->loadImage("item tile grass", IMAGE("/item/tile/tile grass"), 16, 16, TRUE, TRANS_COLOR);
	_loading->loadImage("item tile stone", IMAGE("/item/tile/tile stone"), 16, 16, TRUE, TRANS_COLOR);
	_loading->loadImage("item tile silver", IMAGE("/item/tile/tile silver"), 16, 16, TRUE, TRANS_COLOR);
	_loading->loadImage("item tile gold", IMAGE("/item/tile/tile gold"), 16, 16, TRUE, TRANS_COLOR);

	_loading->loadImage("helmet silver", IMAGE("/item/equip/helmet silver"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("helmet silver image", IMAGE("/item/equip/helmet silver image"), 24, 22, TRUE, TRANS_COLOR);
	_loading->loadImage("body silver", IMAGE("/item/equip/body silver"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("body silver image", IMAGE("/item/equip/body silver image"), 30, 18, TRUE, TRANS_COLOR);
	_loading->loadImage("pant silver", IMAGE("/item/equip/pant silver"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("pant silver image", IMAGE("/item/equip/pant silver image"), 22, 18, TRUE, TRANS_COLOR);

	_loading->loadImage("helmet gold", IMAGE("/item/equip/helmet gold"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("helmet gold image", IMAGE("/item/equip/helmet gold image"), 26, 22, TRUE, TRANS_COLOR);
	_loading->loadImage("body gold", IMAGE("/item/equip/body gold"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("body gold image", IMAGE("/item/equip/body gold image"), 30, 18, TRUE, TRANS_COLOR);
	_loading->loadImage("pant gold", IMAGE("/item/equip/pant gold"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("pant gold image", IMAGE("/item/equip/pant gold image"), 22, 18, TRUE, TRANS_COLOR);

	_loading->loadImage("body costume", IMAGE("/item/equip/body costume"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("body costume image", IMAGE("/item/equip/body costume image"), 32, 32, TRUE, TRANS_COLOR);

	_loading->loadImage("sword basic", IMAGE("/item/weapon/sword basic"), 32, 32, TRUE, TRANS_COLOR);
	_loading->loadImage("bow basic", IMAGE("/item/weapon/bow basic"), 16, 32, TRUE, TRANS_COLOR);
	_loading->loadImage("gun basic", IMAGE("/item/weapon/gun basic"), 56, 20, TRUE, TRANS_COLOR);
	_loading->loadImage("magic basic", IMAGE("/item/weapon/magic basic"), 28, 28, TRUE, TRANS_COLOR);

	//아이템 화살
	_loading->loadImage("arrow", IMAGE("/item/weapon/arrow"), 14, 32, TRUE, TRANS_COLOR);
	_loading->loadImage("arrow image", IMAGE("/item/weapon/arrow image"), 14, 32, TRUE, TRANS_COLOR);

	_loading->loadImage("bullet", IMAGE("/item/weapon/bullet"), 12, 12, TRUE, TRANS_COLOR);
	_loading->loadImage("bullet image", IMAGE("/item/weapon/bullet image"), 2, 20, TRUE, TRANS_COLOR);

	//플레이어
	_loading->loadImage("player head", IMAGE("player/head"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("player body", IMAGE("player/body"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("player leg", IMAGE("player/leg"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("player hair", IMAGE("player/hair"), 80, 1120, TRUE, TRANS_COLOR);

	//ui
	_loading->loadImage("ui inven back", IMAGE("ui/Inventory_Back"), 52, 52, TRUE, RGB(255, 0, 255));
	_loading->loadImage("ui inven back select", IMAGE("ui/inventory_back_select"), 52, 52, TRUE, TRANS_COLOR);

	_loading->loadImage("ui minimap", IMAGE("ui/minimap"), 120, 120, TRUE, TRANS_COLOR);

	//몬스터
	_loading->loadImage("monster zombie1", IMAGE("/monster/zombie1"), 68, 162, TRUE, TRANS_COLOR);
	_loading->loadImage("monster zombie2", IMAGE("/monster/zombie2"), 68, 162, TRUE, TRANS_COLOR);
	_loading->loadImage("monster zombie3", IMAGE("/monster/zombie3"), 68, 162, TRUE, TRANS_COLOR);
	_loading->loadImage("monster zombie4", IMAGE("/monster/zombie4"), 68, 162, TRUE, TRANS_COLOR);

	//이펙트
	_loading->loadImage("blood", IMAGE("blood"), 16, 80, TRUE, TRANS_COLOR);
}

void LoadingScene::loadingSound()
{
	//타일
	_loading->loadSound("grass dig 0", SOUND("tile/grass dig 0.wav"), false, false);
	_loading->loadSound("grass dig 1", SOUND("tile/grass dig 1.wav"), false, false);
	_loading->loadSound("grass dig 2", SOUND("tile/grass dig 2.wav"), false, false);

	_loading->loadSound("iron dig 0", SOUND("tile/iron dig 0.wav"), false, false);
	_loading->loadSound("iron dig 1", SOUND("tile/iron dig 1.wav"), false, false);
	_loading->loadSound("iron dig 2", SOUND("tile/iron dig 2.wav"), false, false);

	//플레이어
	_loading->loadSound("player run", SOUND("player/run.wav"), false, false);
	_loading->loadSound("player jump", SOUND("player/jump.wav"), false, false);

	_loading->loadSound("hit 1", SOUND("player/Female_Hit_0.wav"), false, false);
	_loading->loadSound("hit 2", SOUND("player/Female_Hit_1.wav"), false, false);
	_loading->loadSound("hit 3", SOUND("player/Female_Hit_2.wav"), false, false);

	//ui
	_loading->loadSound("ui grab", SOUND("ui/grab.wav"), false, false);
	_loading->loadSound("ui open", SOUND("ui/menu_open.wav"), false, false);
	_loading->loadSound("ui close", SOUND("ui/menu_close.wav"), false, false);

	//아이템
	_loading->loadSound("arrow", SOUND("item/arrow.wav"), false, false);
	_loading->loadSound("bullet", SOUND("item/bullet.wav"), false, false);
}