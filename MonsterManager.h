#pragma once
#include <vector>
#include "TerrariaNode.h"
#include "TerrariaUnit.h"
#include "Zombie.h"
#include "EyeBoss.h"
#include "TileMap.h"
#include "SnakeBoss.h"
//#include "DroppedItemManager.h"

namespace Terraria
{
	typedef std::vector<Unit*> vUnit;
	typedef vUnit::iterator viUnit;

	class DroppedItemManager;
	class Player;
	class MonsterManager : public Node
	{
	private:
		vUnit _vMonster;

		Player* _player;
	public:
		HRESULT initialize(Player* player);
		void release();
		void update();
		void render(HDC hdc);

		inline vUnit* getMonsters(){ return &_vMonster; }

		void createZombie(float x, float y);
		void createEyeBoss(DroppedItemManager* dm, float x, float y);
		void createSnakeBoss(DroppedItemManager* dm, TileMap* tileMap, Player* player, float x, float y);

		MonsterManager();
		virtual ~MonsterManager();
	};
}