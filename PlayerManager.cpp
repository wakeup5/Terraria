#include "stdafx.h"
#include "PlayerManager.h"
#include "TileMap.h"

namespace Terraria
{
	PlayerManager::PlayerManager()
	{
	}


	PlayerManager::~PlayerManager()
	{

	}

	HRESULT PlayerManager::initialize(TileMap* tileMap, DroppedItemManager* dropItemManager, MonsterManager* monsterManager)
	{
		_inven = new Inventory;
		_inven->initialize();

		_player = new Player;
		_player->initialize(_inven);

		_ammo = new Ammo;
		_ammo->initialize(20);

		_map = tileMap;
		_dropItemManager - dropItemManager;
		_mm = monsterManager;
		return S_OK;
	}
	void PlayerManager::release()
	{
		SAFE_RELEASE(_player);
		SAFE_RELEASE(_ammo);
		SAFE_RELEASE(_inven);
	}
	void PlayerManager::update()
	{
		_player->update();
		_ammo->update();

		if (KEYMANAGER->isOnceKeyDown('A') || 
			(KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isOnceKeyUp('D')))
		{
			_player->move(LEFT);
		}
		else if (KEYMANAGER->isOnceKeyDown('D') || 
			(KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isOnceKeyUp('A')))
		{
			_player->move(RIGHT);
		}
		else if (KEYMANAGER->isOnceKeyUp('D') ||
			KEYMANAGER->isOnceKeyUp('A'))
		{
			_player->stay();
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			action();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			if (_player->getPosition() == FLOOR)
			{
				_player->jump();
			}
		}
		
		//_player->setFloor(_option.height());

	}
	void PlayerManager::render(HDC hdc)
	{
		_player->render(hdc);
		_ammo->render(hdc);
	}

	void PlayerManager::action()
	{
		if (_player->isAction()) return;

		if (_player->getAction() == ACTION_STAY)
		{
			_player->action();

			Item* select = _player->getSelectItem();
			POINT inMouseTilePt = _map->getPointByMouse(_option.inMousePt());
			if (select != NULL)
			{
				if (select->getItemType() == ITEM_TOOL_PICKAXE)
				{
					_map->pickaxe(inMouseTilePt.x, inMouseTilePt.y);
				}
				else if (select->getItemType() == ITEM_BLOCK_GRASS)
				{
					buildBlock(TILE_GRASS);
				}
				else if (select->getItemType() == ITEM_BLOCK_STONE)
				{
					buildBlock(TILE_STONE);
				}
				else if (select->getItemType() == ITEM_WEAPON_SWORD)
				{
					attackSword();
				}
				else if (select->getItemType() == ITEM_WEAPON_BOW)
				{
					for (int i = 0; i < select->getAbillity().shootNum; i++)
					{
						attackBow();
					}
				}
				else if (select->getItemType() == ITEM_WEAPON_GUN)
				{
					attackGun();
				}
			}
		}
		else if (_player->getAction() == ACTION_NONE)
		{
			_player->setAction(ACTION_STAY);
		}
	}

	void PlayerManager::buildBlock(TILE_TYPE type)
	{
		Item* select = _player->getSelectItem();
		POINT inMouseTilePt = _map->getPointByMouse(_option.inMousePt());
		if (_map->getTile(inMouseTilePt.x, inMouseTilePt.y)->getType() == TILE_NONE)
		{
			_map->setTileType(inMouseTilePt, type);
			select->subAmount(1);
		}
	}

	void PlayerManager::attackSword()
	{
		vUnit* mons = _mm->getMonsters();
		viUnit iter = mons->begin();

		RECT atkRect = makeRectCenter(_player->getX(), _player->getY(), METER_TO_PIXEL * 7, METER_TO_PIXEL * 7);
		RECT r;

		for (; iter != mons->end(); iter++)
		{
			if (IntersectRect(&r, &atkRect, &(*iter)->getRect()))
			{
				(*iter)->hit((UNIT_DIRECT)_player->getDirect(), _player->getAtk());

				TEffectManager::getSingleton()->createEffects(
					(*iter)->getX(), (*iter)->getY(), //x, y
					8, _option.getMouseAngle(_player->getX(), _player->getY()), METER_TO_PIXEL * 10, // angle 
					"blood", 1, 5, 1000, true); //option
			}
		}
	}

	void PlayerManager::attackBow()
	{
		if (_player->getArrow() == NULL) return;

		float angle = myUtil::getAngle(_player->getX(), _player->getY(), _option.inMouseX(), _option.inMouseY());
		_ammo->fireArrow(_player->getX(), _player->getY(), angle + (RANDOM->getFloat(0.1) - 0.05), METER_TO_PIXEL * 50);

		_player->getArrow()->subAmount(1);
		SOUNDMANAGER->play("arrow", _option.volume() / 4);
	}

	void PlayerManager::attackGun()
	{
		if (_player->getBullet() == NULL) return;

		float angle = myUtil::getAngle(_player->getX(), _player->getY(), _option.inMouseX(), _option.inMouseY());
		_ammo->fireBullet(_player->getX(), _player->getY(), angle, METER_TO_PIXEL * 100);

		_player->getBullet()->subAmount(1);
		SOUNDMANAGER->play("bullet", _option.volume() / 4);
	}
}