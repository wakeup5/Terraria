#pragma once
#include "TerrariaNode.h"
#include "TerrariaUnit.h"
#include "Physical.h"

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

	private:
	public:
		static bool tileCollision(Physical* obj, TileMap* tileMap);
	private:
		Collision(){}
		virtual ~Collision(){}
	};
}
