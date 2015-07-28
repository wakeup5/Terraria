#pragma once
#include "TerrariaNode.h"
#include "TerrariaUnit.h"
#include "TileMap.h"

namespace Terraria
{
	class Collision : public Node
	{
	public:
		static void tileCollision(Unit* unit, TileMap* tileMap);
	private:
		static bool tileCollisionFloor(Unit* unit, TileMap* tileMap);
		static bool tileCollisionTop(Unit* unit, TileMap* tileMap);
		static bool tileCollisionSide(Unit* unit, TileMap* tileMap);
	private:
		Collision(){}
		virtual ~Collision(){}
	};
}
