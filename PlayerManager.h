#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Inventory.h"
//#include "TileMap.h"
#include "DroppedItemManager.h"
#include "MonsterManager.h"
#include "Ammo.h"
#include "MagicBall.h"

namespace Terraria
{
	class TileMap;
	class PlayerManager : public GameNode
	{
	private:
		Player* _player;
		Inventory* _inven;
		TileMap* _map;
		DroppedItemManager* _dropItemManager;
		MonsterManager* _mm;

		Ammo* _ammo;
		MagicBall* _mBall;
	public:
		HRESULT initialize(TileMap* tileMap, DroppedItemManager* dropItemManager, MonsterManager* monstarManager);
		void release();
		void update();
		void render(HDC hdc);

		void action();

		Player* getPlayer(){ return _player; }
		Inventory* getInventory(){ return _inven; }

		void buildBlock(TILE_TYPE type);
		void attackSword();
		void attackBow();
		void attackGun();
		void attackMagic();

		Ammo* getAmmo(){ return _ammo; }
		MagicBall* getMagicBall(){ return _mBall; }

		PlayerManager();
		virtual ~PlayerManager();
	};
}


