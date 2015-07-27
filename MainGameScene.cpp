#include "stdafx.h"
#include "MainGameScene.h"

using namespace Terraria;

MainGameScene::MainGameScene()
{
}


MainGameScene::~MainGameScene()
{
}

HRESULT MainGameScene::initialize()
{
	_map = new TileMap;
	_map->initialize();

	_pm = new PlayerManager;
	_pm->initialize(_map);

	IMAGEMANAGER->addImage("body 46 image", IMAGE("/item/Female_Body_46_Image"), 38, 32, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("body 46", IMAGE("/item/Female_Body_46"), 80, 1120, TRUE, TRANS_COLOR);
	_body = new Item;
	_body->initialize("body 46 image", "body 46", EQUIP_TOP);

	IMAGEMANAGER->addImage("pant 46 image", IMAGE("/item/Armor_Legs_46_Image"), 22, 18, TRUE, TRANS_COLOR);
	IMAGEMANAGER->addImage("pant 46", IMAGE("/item/Armor_Legs_46"), 80, 1120, TRUE, TRANS_COLOR);
	_pant = new Item;
	_pant->initialize("pant 46 image", "pant 46", EQUIP_PANT);

	IMAGEMANAGER->addImage("pickaxe basic", IMAGE("/item/tool/pickaxe_basic"), 32, 32, TRUE, TRANS_COLOR);
	_pickaxe = new Item;
	_pickaxe->initialize("pickaxe basic", "pickaxe basic", ITEM_TOOL_PICKAXE);

	_pm->getInventory()->setItem(10, _body);
	_pm->getInventory()->setItem(11, _pant);
	_pm->getInventory()->setItem(12, _pickaxe);

	_pm->getPlayer()->setCenter(_map->getWidth() / 2, 0);

	_ui = new UI;
	_ui->initialize(_pm->getPlayer(), _pm->getInventory());

	return S_OK;
}
void MainGameScene::release()
{
	SAFE_RELEASE(_pm);
	SAFE_RELEASE(_map);
	SAFE_RELEASE(_ui);
}
void MainGameScene::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		Item* temp = _pm->getInventory()->getItem(10);
		_pm->getPlayer()->getEquip()->dress(temp);
	}

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		Item* temp = _pm->getInventory()->getItem(11);
		_pm->getPlayer()->getEquip()->dress(temp);
	}

	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		Item* temp = NULL;
		_pm->getPlayer()->getEquip()->undress(EQUIP_TOP, &temp);
		_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), temp);
	}

	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		Item* temp = NULL;
		_pm->getPlayer()->getEquip()->undress(EQUIP_PANT, &temp);
		_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), temp);
	}


	//업데이트 함수
	_pm->update();
	_map->update();
	_ui->update();

	//충돌처리
	_map->collision(_pm->getPlayer());

	//카메라 조작
	_option.setCamera(_pm->getPlayer()->getX(), _map->getWidth(), _pm->getPlayer()->getY(), _map->getHeight());

	//백그라운드
	Background::getSingleton()->change("grass", _option.cameraY(), 0, METER_TO_PIXEL * 40);
	Background::getSingleton()->change("under", _option.cameraY(), METER_TO_PIXEL * 40, METER_TO_PIXEL * 100);
}
void MainGameScene::render()
{
	Background::getSingleton()->render(getMemDC());

	_map->render(getMemDC(), _option.cameraX(), _option.cameraY());
	_pm->render(getMemDC());
	_ui->render(getMemDC());
}