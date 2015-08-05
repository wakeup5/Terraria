#pragma once
#include "TerrariaNode.h"
#include "TerrariaUnit.h"
#include "Physical.h"
#include "PlayerManager.h"
#include "MonsterManager.h"

namespace Terraria
{
	class TileMap;
	class Collision : public Node
	{
	private:
		static bool tileCollisionFloor(Unit* unit, TileMap* tileMap);
		static bool tileCollisionTop(Unit* unit, TileMap* tileMap);
		static bool tileCollisionSide(Unit* unit, TileMap* tileMap);
	public:
		static void tileCollision(Unit* unit, TileMap* tileMap);
		static bool tileCollision(Physical* obj, TileMap* tileMap);
		static void tileCollision(MonsterManager* mm, TileMap* tileMap);

		static bool playerMonsterCollision(Player* player, MonsterManager* mm);

		static bool ammoMonsterCollision(Physical* ammo, MonsterManager* mm, int damage);
	private:
		Collision(){}
		virtual ~Collision(){}
	};
}
