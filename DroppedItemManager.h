#pragma once
#include <string>
#include <set>
#include "common.h"
#include "DroppedItem.h"
#include "TerrariaNode.h"
//#include "PlayerManager.h"
//#include "TileMap.h"
#include "Collision.h"

namespace Terraria
{
	class PlayerManager;
	class TileMap;
	class DroppedItemManager : public Node
	{
	private:
		std::set<DroppedItem*> _sItem;
		std::set<DroppedItem*>::iterator _siItem;

		TileMap* _tileMap;
	public:
		HRESULT initialize(TileMap* tileMap);
		void release();
		void update();
		void render(HDC hdc);

		DroppedItem* createDroppedItem(std::string itemName, int amount, float x, float y, float speedX = 0.0f);

	private:
		void eathOtherCollision();

	public:
		bool playerCollision(PlayerManager* pm);
		void removeDroppedItem(DroppedItem* item);

		DroppedItemManager();
		virtual ~DroppedItemManager();
	};
}