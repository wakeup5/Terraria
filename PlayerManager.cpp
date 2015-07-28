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

	HRESULT PlayerManager::initialize(TileMap* tileMap)
	{
		_player = new Player;
		_player->initialize();

		_inven = new Inventory;
		_inven->initialize();

		_map = tileMap;
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

				if (_player->getSelectItem() != NULL)
				{
					if (_player->getSelectItem()->getItemType() == ITEM_TOOL_PICKAXE)
					{
						_map->pickaxe(_option.inMouseX() / METER_TO_PIXEL, _option.inMouseY() / METER_TO_PIXEL);
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