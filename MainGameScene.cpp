#include "stdafx.h"
#include "MainGameScene.h"
#include "PlayerManager.h"
#include "TileMap.h"

using namespace Terraria;

MainGameScene::MainGameScene()
{
}


MainGameScene::~MainGameScene()
{
}

HRESULT MainGameScene::initialize()
{
	DATAMANAGER->loadDatabase("item", RESOURCE("data/item.ini"));
	ITEMMANAGER->inputItemInfo();
	
	_map = new TileMap;
	_dropItemManager = new DroppedItemManager;
	
	_map->initialize(_dropItemManager);
	_dropItemManager->initialize(_map);

	_pm = new PlayerManager;
	_pm->initialize(_map, _dropItemManager);
	_pm->getPlayer()->setCenter(100, 100);

	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("body test"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("pickaxe"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("body gold"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("pant gold"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("helmet gold"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("body silver"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("pant silver"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("helmet silver"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("body costume"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("sword basic"));

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
	SAFE_RELEASE(_dropItemManager);
}
void MainGameScene::update()
{
	//업데이트 함수
	_map->update();
	_ui->update();
	_pm->update();
	_dropItemManager->update();

	//충돌처리
	Collision::tileCollision(_pm->getPlayer(), _map);
	_dropItemManager->playerCollision(_pm);

	//카메라 조작
	_option.setCamera(_pm->getPlayer()->getX(), _map->getWidth(), _pm->getPlayer()->getY(), _map->getHeight());

	//백그라운드
	Background::getSingleton()->change("grass", _option.cameraY(), 0, METER_TO_PIXEL * 60);
	Background::getSingleton()->change("under", _option.cameraY(), METER_TO_PIXEL * 60, METER_TO_PIXEL * 100);

	//테스트코드
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0) && _ui->getSelectItem() != NULL)
	{
		_dropItemManager->createDroppedItem(_ui->getSelectItem()->getName(), _ui->getSelectItem()->getAmount(), _pm->getPlayer()->getX() + 100, _pm->getPlayer()->getY(), 200);
	}
}
void MainGameScene::render()
{
	Background::getSingleton()->render(getMemDC());

	_map->render(getMemDC(), _option.cameraX(), _option.cameraY());
	_dropItemManager->render(getMemDC());
	_pm->render(getMemDC());
	_ui->render(getMemDC());
}