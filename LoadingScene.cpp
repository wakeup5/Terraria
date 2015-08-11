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
	_loading->loadImage("pickaxe basic", IMAGE("/item/tool/pickaxe_basic"), 32, 32, TRUE, TRANS_COLOR);

	_loading->loadImage("item tile grass", IMAGE("/item/tile/tile grass"), 16, 16, TRUE, TRANS_COLOR);
	_loading->loadImage("item tile stone", IMAGE("/item/tile/tile stone"), 16, 16, TRUE, TRANS_COLOR);
	_loading->loadImage("item tile silver", IMAGE("/item/tile/tile silver"), 16, 16, TRUE, TRANS_COLOR);
	_loading->loadImage("item tile gold", IMAGE("/item/tile/tile gold"), 16, 16, TRUE, TRANS_COLOR);

	//	방어구 - 실버
	_loading->loadImage("helmet silver", IMAGE("/item/equip/helmet silver"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("helmet silver image", IMAGE("/item/equip/helmet silver image"), 24, 22, TRUE, TRANS_COLOR);
	_loading->loadImage("body silver", IMAGE("/item/equip/body silver"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("body silver image", IMAGE("/item/equip/body silver image"), 30, 18, TRUE, TRANS_COLOR);
	_loading->loadImage("pant silver", IMAGE("/item/equip/pant silver"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("pant silver image", IMAGE("/item/equip/pant silver image"), 22, 18, TRUE, TRANS_COLOR);

	//	방어구 - 골드
	_loading->loadImage("helmet gold", IMAGE("/item/equip/helmet gold"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("helmet gold image", IMAGE("/item/equip/helmet gold image"), 26, 22, TRUE, TRANS_COLOR);
	_loading->loadImage("body gold", IMAGE("/item/equip/body gold"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("body gold image", IMAGE("/item/equip/body gold image"), 30, 18, TRUE, TRANS_COLOR);
	_loading->loadImage("pant gold", IMAGE("/item/equip/pant gold"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("pant gold image", IMAGE("/item/equip/pant gold image"), 22, 18, TRUE, TRANS_COLOR);

	//	방어구 - 코발트
	_loading->loadImage("head cobalt magic", IMAGE("/item/equip/head/head cobalt magic"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("head cobalt magic image", IMAGE("/item/equip/head/head cobalt magic image"), 22, 20, TRUE, TRANS_COLOR);
	_loading->loadImage("head cobalt shooter", IMAGE("/item/equip/head/head cobalt shooter"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("head cobalt shooter image", IMAGE("/item/equip/head/head cobalt shooter image"), 26, 18, TRUE, TRANS_COLOR);
	_loading->loadImage("head cobalt warrior", IMAGE("/item/equip/head/head cobalt warrior"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("head cobalt warrior image", IMAGE("/item/equip/head/head cobalt warrior image"), 28, 18, TRUE, TRANS_COLOR);

	_loading->loadImage("body cobalt", IMAGE("/item/equip/body/body cobalt"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("body cobalt image", IMAGE("/item/equip/body/body cobalt image"), 30, 20, TRUE, TRANS_COLOR);

	_loading->loadImage("pant cobalt", IMAGE("/item/equip/pant/pant cobalt"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("pant cobalt image", IMAGE("/item/equip/pant/pant cobalt image"), 22, 18, TRUE, TRANS_COLOR);

	//	방어구 - 미스릴
	_loading->loadImage("head mythril magic", IMAGE("/item/equip/head/head mythril magic"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("head mythril magic image", IMAGE("/item/equip/head/head mythril magic image"), 28, 14, TRUE, TRANS_COLOR);
	_loading->loadImage("head mythril shooter", IMAGE("/item/equip/head/head mythril shooter"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("head mythril shooter image", IMAGE("/item/equip/head/head mythril shooter image"), 24, 20, TRUE, TRANS_COLOR);
	_loading->loadImage("head mythril warrior", IMAGE("/item/equip/head/head mythril warrior"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("head mythril warrior image", IMAGE("/item/equip/head/head mythril warrior image"), 20, 20, TRUE, TRANS_COLOR);

	_loading->loadImage("body mythril", IMAGE("/item/equip/body/body mythril"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("body mythril image", IMAGE("/item/equip/body/body mythril image"), 30, 20, TRUE, TRANS_COLOR);

	_loading->loadImage("pant mythril", IMAGE("/item/equip/pant/pant mythril"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("pant mythril image", IMAGE("/item/equip/pant/pant mythril image"), 22, 18, TRUE, TRANS_COLOR);

	//	방어구 - 블러드
	_loading->loadImage("head blood magic", IMAGE("/item/equip/head/head blood magic"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("head blood magic image", IMAGE("/item/equip/head/head blood magic image"), 26, 24, TRUE, TRANS_COLOR);
	_loading->loadImage("head blood shooter", IMAGE("/item/equip/head/head blood shooter"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("head blood shooter image", IMAGE("/item/equip/head/head blood shooter image"), 32, 26, TRUE, TRANS_COLOR);
	_loading->loadImage("head blood warrior", IMAGE("/item/equip/head/head blood warrior"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("head blood warrior image", IMAGE("/item/equip/head/head blood warrior image"), 30, 20, TRUE, TRANS_COLOR);

	_loading->loadImage("body blood", IMAGE("/item/equip/body/body blood"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("body blood image", IMAGE("/item/equip/body/body blood image"), 30, 20, TRUE, TRANS_COLOR);

	_loading->loadImage("pant blood", IMAGE("/item/equip/pant/pant blood"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("pant blood image", IMAGE("/item/equip/pant/pant blood image"), 22, 18, TRUE, TRANS_COLOR);

	//	방어구 - 코스튬
	_loading->loadImage("body 46 image", IMAGE("/item/Female_Body_46_Image"), 38, 32, TRUE, TRANS_COLOR);
	_loading->loadImage("body 46", IMAGE("/item/Female_Body_46"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("pant 46 image", IMAGE("/item/Armor_Legs_46_Image"), 22, 18, TRUE, TRANS_COLOR);
	_loading->loadImage("pant 46", IMAGE("/item/Armor_Legs_46"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("body costume", IMAGE("/item/equip/body costume"), 80, 1120, TRUE, TRANS_COLOR);
	_loading->loadImage("body costume image", IMAGE("/item/equip/body costume image"), 32, 32, TRUE, TRANS_COLOR);

	//	무기
	_loading->loadImage("sword basic", IMAGE("/item/weapon/sword basic"), 32, 32, TRUE, TRANS_COLOR);
	_loading->loadImage("bow basic", IMAGE("/item/weapon/bow basic"), 16, 32, TRUE, TRANS_COLOR);
	_loading->loadImage("gun basic", IMAGE("/item/weapon/gun basic"), 56, 20, TRUE, TRANS_COLOR);
	_loading->loadImage("magic basic", IMAGE("/item/weapon/magic basic"), 28, 28, TRUE, TRANS_COLOR);

	//	무기 - 실버
	_loading->loadImage("bow silver", IMAGE("/item/weapon/bow silver"), 16, 32, TRUE, TRANS_COLOR);
	_loading->loadImage("sword silver", IMAGE("/item/weapon/sword silver"), 32, 32, TRUE, TRANS_COLOR);
	_loading->loadImage("magic silver", IMAGE("/item/weapon/magic silver"), 36, 36, TRUE, TRANS_COLOR);

	//	무기 - 골드
	_loading->loadImage("bow gold", IMAGE("/item/weapon/bow gold"), 16, 32, TRUE, TRANS_COLOR);
	_loading->loadImage("sword gold", IMAGE("/item/weapon/sword gold"), 32, 32, TRUE, TRANS_COLOR);
	_loading->loadImage("magic gold", IMAGE("/item/weapon/magic gold"), 44, 44, TRUE, TRANS_COLOR);

	//	무기 - 코발트
	_loading->loadImage("bow cobalt", IMAGE("/item/weapon/bow cobalt"), 18, 36, TRUE, TRANS_COLOR);
	_loading->loadImage("sword cobalt", IMAGE("/item/weapon/sword cobalt"), 50, 50, TRUE, TRANS_COLOR);
	_loading->loadImage("magic cobalt", IMAGE("/item/weapon/magic cobalt"), 40, 40, TRUE, TRANS_COLOR);

	//	무기 - 미스릴
	_loading->loadImage("bow mythril", IMAGE("/item/weapon/bow mythril"), 30, 62, TRUE, TRANS_COLOR);
	_loading->loadImage("sword mythril", IMAGE("/item/weapon/sword mythril"), 44, 46, TRUE, TRANS_COLOR);
	_loading->loadImage("magic mythril", IMAGE("/item/weapon/magic mythril"), 42, 42, TRUE, TRANS_COLOR);

	//	무기 - 블러드
	_loading->loadImage("bow luna", IMAGE("/item/weapon/bow luna"), 32, 54, TRUE, TRANS_COLOR);
	_loading->loadImage("sword luna", IMAGE("/item/weapon/sword luna"), 50, 58, TRUE, TRANS_COLOR);
	_loading->loadImage("magic luna", IMAGE("/item/weapon/magic luna"), 26, 30, TRUE, TRANS_COLOR);

	//악세서리
	_loading->loadImage("blue baloon image", IMAGE("/item/equip/acc/blue baloon image"), 28, 48, TRUE, TRANS_COLOR);
	_loading->loadImage("blue baloon", IMAGE("/item/equip/acc/blue baloon"), 104, 224, TRUE, TRANS_COLOR);
	_loading->loadImage("gray baloon image", IMAGE("/item/equip/acc/gray baloon image"), 28, 48, TRUE, TRANS_COLOR);
	_loading->loadImage("gray baloon", IMAGE("/item/equip/acc/gray baloon"), 104, 224, TRUE, TRANS_COLOR);
	_loading->loadImage("green baloon image", IMAGE("/item/equip/acc/green baloon image"), 28, 48, TRUE, TRANS_COLOR);
	_loading->loadImage("green baloon", IMAGE("/item/equip/acc/green baloon"), 104, 224, TRUE, TRANS_COLOR);
	_loading->loadImage("purple baloon image", IMAGE("/item/equip/acc/purple baloon image"), 28, 48, TRUE, TRANS_COLOR);
	_loading->loadImage("purple baloon", IMAGE("/item/equip/acc/purple baloon"), 104, 224, TRUE, TRANS_COLOR);
	_loading->loadImage("gold baloon image", IMAGE("/item/equip/acc/gold baloon image"), 28, 48, TRUE, TRANS_COLOR);
	_loading->loadImage("gold baloon", IMAGE("/item/equip/acc/gold baloon"), 104, 224, TRUE, TRANS_COLOR);
	_loading->loadImage("master baloon image", IMAGE("/item/equip/acc/master baloon image"), 28, 48, TRUE, TRANS_COLOR);
	_loading->loadImage("master baloon", IMAGE("/item/equip/acc/master baloon"), 104, 224, TRUE, TRANS_COLOR);

	//	잉곳
	_loading->loadImage("ingot silver", IMAGE("/item/meterial/ingot silver"), 30, 24, TRUE, TRANS_COLOR);
	_loading->loadImage("ingot gold", IMAGE("/item/meterial/ingot gold"), 30, 24, TRUE, TRANS_COLOR);
	_loading->loadImage("ingot cobalt", IMAGE("/item/meterial/ingot cobalt"), 30, 24, TRUE, TRANS_COLOR);
	_loading->loadImage("ingot mythril", IMAGE("/item/meterial/ingot mythril"), 30, 24, TRUE, TRANS_COLOR);
	_loading->loadImage("ingot blood", IMAGE("/item/meterial/ingot blood"), 30, 24, TRUE, TRANS_COLOR);

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

	_loading->loadImage("boss eye", IMAGE("/monster/eye boss"), 160, 160, TRUE, TRANS_COLOR);
	_loading->loadImage("boss eye dead 1", IMAGE("/monster/eye dead 1"), 20, 24, TRUE, TRANS_COLOR);
	_loading->loadImage("boss eye dead 2", IMAGE("/monster/eye dead 2"), 52, 80, TRUE, TRANS_COLOR);
	_loading->loadImage("boss eye dead 3", IMAGE("/monster/eye dead 3"), 48, 52, TRUE, TRANS_COLOR);
	_loading->loadImage("boss eye dead 4", IMAGE("/monster/eye dead 4"), 46, 32, TRUE, TRANS_COLOR);

	_loading->loadImage("boss snake head", IMAGE("/monster/snake head"), 50, 102, TRUE, TRANS_COLOR);
	_loading->loadImage("boss snake body", IMAGE("/monster/snake body"), 50, 46, TRUE, TRANS_COLOR);
	_loading->loadImage("boss snake tail", IMAGE("/monster/snake tail"), 50, 102, TRUE, TRANS_COLOR);

	//이펙트
	_loading->loadImage("blood", IMAGE("blood"), 16, 80, TRUE, TRANS_COLOR);
	_loading->loadImage("magic effect water", IMAGE("water"), 52, 216, TRUE, TRANS_COLOR);
	_loading->loadImage("magic effect greenball", IMAGE("green"), 30, 150, TRUE, TRANS_COLOR);
	_loading->loadImage("magic effect bullet", IMAGE("magic bullet"), 10, 10, TRUE, TRANS_COLOR);
	_loading->loadImage("magic effect bagic", IMAGE("basic"), 24, 216, TRUE, TRANS_COLOR);
	_loading->loadImage("magic effect electro", IMAGE("electro"), 34, 64, TRUE, TRANS_COLOR);
	_loading->loadImage("magic effect pink", IMAGE("pink"), 36, 144, TRUE, TRANS_COLOR);
	_loading->loadImage("magic effect graind", IMAGE("graind"), 22, 112, TRUE, TRANS_COLOR);

	_loading->loadImage("effect jump", IMAGE("player/jump"), 30, 150, TRUE, TRANS_COLOR);
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

	_loading->loadSound("boss", SOUND("monster/Roar_0.wav"), false, false);
	//_loading->loadSound("bosske", SOUND("monster/Roar_2.wav"), false, false);
	_loading->loadSound("monster hit", SOUND("monster/NPC_Hit_1.wav"), false, false);
	_loading->loadSound("snake hit", SOUND("monster/NPC_Hit_4.wav"), false, false);

	_loading->loadSound("monster dead", SOUND("monster/NPC_Killed_10.wav"), false, false);
	_loading->loadSound("snake dead", SOUND("monster/NPC_Killed_14.wav"), false, false); 
	_loading->loadSound("zombie dead", SOUND("monster/NPC_Killed_1.wav"), false, false);
}