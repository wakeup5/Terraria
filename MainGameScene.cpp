#include "stdafx.h"
#include "MainGameScene.h"
#include "PlayerManager.h"
#include "TileMap.h"
#include "TEffectManager.h"

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

	TEffectManager::getSingleton()->initialize(1000);
	
	_map = new TileMap;
	_dropItemManager = new DroppedItemManager;
	_pm = new PlayerManager;
	_mm = new MonsterManager;
	_ui = new UI;
	
	_map->initialize(_dropItemManager);
	
	_dropItemManager->initialize(_map);

	_pm->initialize(_map, _dropItemManager, _mm);
	_pm->getPlayer()->setCenter(100, 100);

	_mm->initialize(_pm->getPlayer());

	_ui->initialize(_pm->getPlayer(), _pm->getInventory(), _map);

	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("body test"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("pickaxe"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("body gold"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("pant gold"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("helmet gold"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("body silver"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("pant silver"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("helmet silver"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("body costume"));
	_pm->getInventory()->setItem(3, ITEMMANAGER->createItem("sword basic"));
	_pm->getInventory()->setItem(0, ITEMMANAGER->createItem("gun basic"));
	_pm->getInventory()->setItem(1, ITEMMANAGER->createItem("bow basic"));
	_pm->getInventory()->setItem(2, ITEMMANAGER->createItem("magic basic"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("arrow", 999));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("bullet", 999));

	return S_OK;
}
void MainGameScene::release()
{
	SAFE_RELEASE(_pm);
	SAFE_RELEASE(_map);
	SAFE_RELEASE(_ui);
	SAFE_RELEASE(_dropItemManager);

	TEffectManager::getSingleton()->release();
	TEffectManager::getSingleton()->releaseSingleton();
}
void MainGameScene::update()
{
	//업데이트 함수
	_map->update();
	_ui->update();
	_pm->update();
	_dropItemManager->update();
	_mm->update();

	TEffectManager::getSingleton()->update();

	//충돌처리
	Collision::tileCollision(_pm->getPlayer(), _map);
	Collision::tileCollision(_mm, _map);
	if (Collision::playerMonsterCollision(_pm->getPlayer(), _mm))
	{

	}
	//화살 충돌 체크
	lAmmo* ammo = _pm->getAmmo()->getAmmo();
	liAmmo iter = ammo->begin();
	for (; iter != ammo->end();)
	{
		if (Collision::tileCollision(static_cast<Physical*>(*iter), _map))
		{
			SAFE_RELEASE(*iter);
			iter = ammo->erase(iter);
		}
		else if (Collision::ammoMonsterCollision(static_cast<Physical*>(*iter), _mm, _pm->getPlayer()->getAtk()))
		{
			//bloodEffect((*iter)->getX(), (*iter)->getY());

			TEffectManager::getSingleton()->createEffects(
				(*iter)->getX(), (*iter)->getY(), //x, y
				8, _option.getMouseAngle(_pm->getPlayer()->getX(), _pm->getPlayer()->getY()), METER_TO_PIXEL * 10, // angle 
				"blood", 1, 5, 1000, true); //option

			SAFE_RELEASE(*iter);
			iter = ammo->erase(iter);
		}
		else
		{
			iter++;
		}
	}

	_dropItemManager->playerCollision(_pm);

	//카메라 조작
	_option.setCamera(_pm->getPlayer()->getX(), _map->getWidth(), _pm->getPlayer()->getY(), _map->getHeight());

	//백그라운드
	Background::getSingleton()->change("grass", _option.cameraY(), 0, METER_TO_PIXEL * 60);
	Background::getSingleton()->change("under", _option.cameraY(), METER_TO_PIXEL * 60, METER_TO_PIXEL * 100);

	//테스트코드
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		_mm->createZombie(_option.inMouseX(), _option.inMouseY());
	}
}
void MainGameScene::render()
{
	Background::getSingleton()->render(getMemDC());

	_map->render(getMemDC(), _option.cameraX(), _option.cameraY());
	_dropItemManager->render(getMemDC());
	_pm->render(getMemDC());
	_mm->render(getMemDC());
	_ui->render(getMemDC());

	TEffectManager::getSingleton()->render(getMemDC());
}

void MainGameScene::bloodEffect(float x, float y)
{
	return;
	/*
	float angle;
	float speed;
	for (int i = 0; i < 16; i++)
	{
		angle = (((float)i / 16) * M_PI * 2);
		speed = (METER_TO_PIXEL * RANDOM->getFloatTo(3, 10));

		TEffectManager::getSingleton()->createEffect(
			x, y, //x, y
			angle + RANDOM->getFloatTo(-0.1, 0.1), // angle 
			speed + (speed * 2 * sin(angle - _option.getMouseAngle(_pm->getPlayer()->getX(), _pm->getPlayer()->getY()))), //speed
			"blood", 1, 5, 1000, false, true); //option
	}
	*/
}