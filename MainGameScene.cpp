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
	//ITEMMANAGER->inputItemInfo();
	DATAMANAGER->loadDatabase("combine", RESOURCE("data/combine.ini"));
	//ITEMMANAGER->inputCombineInfo();

	TEffectManager::getSingleton()->initialize(1000);
	
	_map = new TileMap;
	_dropItemManager = new DroppedItemManager;
	_pm = new PlayerManager;
	_mm = new MonsterManager;
	_ui = new UI;
	
	_map->initialize(_dropItemManager);
	
	_dropItemManager->initialize(_map);

	_pm->initialize(_map, _dropItemManager, _mm);
	_pm->getPlayer()->setCenter(_map->getWidth() / 2, 100);

	_mm->initialize(_pm->getPlayer());

	_ui->initialize(_pm->getPlayer(), _pm->getInventory(), _map, _dropItemManager);

	//기본 아이템 지급
	_pm->getInventory()->setItem(0, ITEMMANAGER->createItem("pickaxe"));

	_pm->getInventory()->setItem(3, ITEMMANAGER->createItem("sword basic"));
	//_pm->getInventory()->setItem(0, ITEMMANAGER->createItem("gun basic"));
	_pm->getInventory()->setItem(1, ITEMMANAGER->createItem("bow basic"));
	_pm->getInventory()->setItem(2, ITEMMANAGER->createItem("magic basic"));
	
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("arrow", 999));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("bullet", 999));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("tile stone", 999));

	//test
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("ingot silver", 999));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("ingot gold", 999));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("ingot cobalt", 999));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("ingot mythril", 999));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("ingot blood", 999));

	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("blue baloon"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("gray baloon"));
	_pm->getInventory()->setItem(_pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem("green baloon"));

	return S_OK;
}
void MainGameScene::release()
{
	SAFE_RELEASE(_pm);
	SAFE_RELEASE(_map);
	SAFE_RELEASE(_ui);
	SAFE_RELEASE(_dropItemManager);
	SAFE_RELEASE(_mm);

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

	//마법
	_pm->getMagicBall()->collisionMonster(_mm, _pm->getPlayer()->getAtk());

	_dropItemManager->playerCollision(_pm);

	//카메라 조작
	_option.setCamera(_pm->getPlayer()->getX(), _map->getWidth(), _pm->getPlayer()->getY(), _map->getHeight());

	//백그라운드
	Background::getSingleton()->change("grass", _option.cameraY(), 0, METER_TO_PIXEL * 60);
	Background::getSingleton()->change("under", _option.cameraY(), METER_TO_PIXEL * 60, METER_TO_PIXEL * 100);

	//테스트코드
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	{
		_mm->createZombie(_option.inMouseX(), _option.inMouseY());
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		_mm->createEyeBoss(_dropItemManager, _option.inMouseX(), _option.inMouseY());
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
	{
		_mm->createSnakeBoss(_dropItemManager, _map, _pm->getPlayer(), _option.inMouseX(), _option.inMouseY());
	}
}
void MainGameScene::render()
{
	Background::getSingleton()->render(getMemDC());

	_mm->render(getMemDC());
	_map->render(getMemDC(), _option.cameraX(), _option.cameraY());
	_dropItemManager->render(getMemDC());

	TEffectManager::getSingleton()->render(getMemDC());
	
	_pm->render(getMemDC());

	_ui->render(getMemDC());
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