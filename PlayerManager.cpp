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
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_player->order(ORDER_MOVE_LEFT);
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_player->order(ORDER_MOVE_RIGHT);
		}
		else
		{
			_player->order(ORDER_NONE);
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			if (_player->getSelectItem() != NULL && _player->getSelectItem()->getItemType() == ITEM_TOOL_PICKAXE)
			{
				_player->addOrder(ORDER_ATTACK);

				if (_map->collision(_option.inMousePt()))
				{
					POINT p = { _option.inMouseX() / METER_TO_PIXEL, _option.inMouseY() / METER_TO_PIXEL };
					_map->setTileType(p, TILE_NONE);
				}
			}
			else
			{
				_player->addOrder(ORDER_ATTACK);
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_player->order(ORDER_JUMP);
		}
		
		//_player->setFloor(_option.height());

		_player->update();
		_inven->isExist(1);
	}
	void PlayerManager::render(HDC hdc)
	{
		_player->render(hdc);
	}
}