#include "stdafx.h"
#include "PlayerManager.h"

namespace Terraria
{
	PlayerManager::PlayerManager()
	{
	}


	PlayerManager::~PlayerManager()
	{

	}

	HRESULT PlayerManager::initialize(TileMap* tileMap, DroppedItemManager* dropItemManager)
	{
		_player = new Player;
		_player->initialize();

		_inven = new Inventory;
		_inven->initialize();

		_map = tileMap;
		_dropItemManager - dropItemManager;
		return S_OK;
	}
	void PlayerManager::release()
	{

	}
	void PlayerManager::update()
	{
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
			if (_player->getUnitState().action == 0)
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
					else if (select->getItemType() == ITEM_WEAPON_SWORD)
					{

					}
					else if (select->getItemType() == ITEM_BLOCK_GRASS)
					{
						if (_map->getTile(inMouseTilePt.x, inMouseTilePt.y).getType() == TILE_NONE)
						{
							_map->setTileType(inMouseTilePt, TILE_GRASS);
							select->subAmount(1);
						}
					}
					else if (select->getItemType() == ITEM_BLOCK_STONE)
					{
						if (_map->getTile(inMouseTilePt.x, inMouseTilePt.y).getType() == TILE_NONE)
						{
							_map->setTileType(inMouseTilePt, TILE_STONE);
							select->subAmount(1);
						}
					}
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_player->jump();
		}
		
		//_player->setFloor(_option.height());

		_player->update();
	}
	void PlayerManager::render(HDC hdc)
	{
		_player->render(hdc);
	}
}