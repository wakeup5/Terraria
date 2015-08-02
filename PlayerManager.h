#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Inventory.h"
#include "TileMap.h"
#include "DroppedItemManager.h"

namespace Terraria
{
	class PlayerManager : public GameNode
	{
	private:
		Player* _player;
		Inventory* _inven;
		TileMap* _map;
		DroppedItemManager* _dropItemManager;
	public:
		HRESULT initialize(TileMap* tileMap, DroppedItemManager* dropItemManager);
		void release();
		void update();
		void render(HDC hdc);

		Player* getPlayer(){ return _player; }
		Inventory* getInventory(){ return _inven; }

		PlayerManager();
		virtual ~PlayerManager();
	};
}


