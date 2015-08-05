#include "stdafx.h"
#include "Collision.h"
#include "TileMap.h"

namespace Terraria
{
	void Collision::tileCollision(Unit* unit, TileMap* tileMap)
	{
		if (unit->getUnitState().position == JUMP &&
			tileCollisionFloor(unit, tileMap))
		{
			unit->floor();
		}
		else if (unit->getUnitState().position == FLOOR &&
			!tileCollisionFloor(unit, tileMap))
		{
			unit->freeFall();
		}

		if (!tileCollisionTop(unit, tileMap))
		{
			tileCollisionSide(unit, tileMap);
		}
	}

	bool Collision::tileCollisionFloor(Unit* unit, TileMap* tileMap)
	{
		RECT unitRc = unit->getRect();
		RECT r;
		int x = unit->getX() / METER_TO_PIXEL;
		int y = (unitRc.bottom - METER_TO_PIXEL / 2) / METER_TO_PIXEL;

		int sx, ex;

		//官蹿 面倒 贸府
		sx = x - 1;
		ex = x + 2;

		if (sx < 0) sx = 0;
		if (ex > MAP_SIZE_X) ex = MAP_SIZE_X;

		Tile tile;

		for (int i = sx; i < ex; i++)
		{
			tile = tileMap->getTile(i, y + 1);
			if (unit->getSpeedY() >= -FLOAT_EPSILON && tile.isBlock() &&
				IntersectRect(&r, &unitRc, &tile.getRect()))
			{
				unit->setFloor(tile.getRect().top);
				return true;
			}
		}

		return false;
	}

	bool Collision::tileCollisionTop(Unit* unit, TileMap* tileMap)
	{
		RECT unitRc = unit->getRect();
		RECT r;
		int x = unit->getX() / METER_TO_PIXEL;
		int y = (unitRc.bottom - METER_TO_PIXEL / 2) / METER_TO_PIXEL;

		int sx, ex;

		//玫厘 面倒 贸府
		sx = x - 1;
		ex = x + 2;

		if (sx < 0) sx = 0;
		if (ex > MAP_SIZE_X) ex = MAP_SIZE_X;

		Tile tile;

		for (int i = sx; i < ex; i++)
		{
			tile = tileMap->getTile(i, y - 2);
			if (unit->getSpeedY() < -FLOAT_EPSILON && tile.isBlock() &&
				IntersectRect(&r, &unitRc, &tile.getRect()))
			{
				unit->setSpeedY(0);
				unit->setAccelY(0);
				return true;
			}
		}

		return false;
	}


	bool Collision::tileCollisionSide(Unit* unit, TileMap* tileMap)
	{
		RECT unitRc = unit->getRect();
		RECT leftRc = RECT{ unitRc.left - 1, unitRc.top, unitRc.left, unitRc.bottom };
		RECT rightRc = RECT{ unitRc.right, unitRc.top, unitRc.right + 1, unitRc.bottom };
		RECT r;
		int x = unit->getX() / METER_TO_PIXEL;
		int y = (unitRc.bottom - METER_TO_PIXEL / 2) / METER_TO_PIXEL;

		int sx, ex;

		//玫厘 面倒 贸府
		sx = x - 1;
		ex = x + 2;

		if (sx < 0) sx = 0;
		if (ex > MAP_SIZE_X) ex = MAP_SIZE_X;

		//if (unit->getUnitState().direct == LEFT)
		{
			if (tileMap->getTile(x - 1, y - 1).isBlock() &&
				IntersectRect(&r, &leftRc, &tileMap->getTile(x - 1, y - 1).getRect()))
			{
				unit->setSpeedX(0);
				unit->setAccelX(0);
				unit->setX(tileMap->getTile(x - 1, y - 1).getRect().right + 1 + unit->getWidth() / 2);

				return true;
			}
			else if (unit->getSpeedY() >= -1 && tileMap->getTile(x - 1, y).isBlock() &&
				IntersectRect(&r, &unitRc, &tileMap->getTile(x - 1, y).getRect()))
			{
				unit->setFloor(tileMap->getTile(x - 1, y).getRect().top);

				return false;
			}
		}

		//if (unit->getUnitState().direct == RIGHT)
		{
			if (tileMap->getTile(x + 1, y - 1).isBlock() &&
				IntersectRect(&r, &rightRc, &tileMap->getTile(x + 1, y - 1).getRect()))
			{
				unit->setSpeedX(0);
				unit->setAccelX(0);
				unit->setX(tileMap->getTile(x + 1, y - 1).getRect().left - unit->getWidth() / 2 - 1);

				return true;
			}
			else if (unit->getSpeedY() >= -1 && tileMap->getTile(x + 1, y).isBlock() &&
				IntersectRect(&r, &unitRc, &tileMap->getTile(x + 1, y).getRect()))
			{
				unit->setFloor(tileMap->getTile(x + 1, y).getRect().top);

				return false;
			}
		}

		return false;
	}

	bool Collision::tileCollision(Physical* obj, TileMap* tileMap)
	{
		RECT rc = obj->getRect();
		RECT r;
		int x = obj->getX() / METER_TO_PIXEL;
		int y = obj->getY() / METER_TO_PIXEL;

		if (x < 0 || x > MAP_SIZE_X || y < 0 || y > MAP_SIZE_Y) return false;

		int sx, ex, sy, ey;

		//官蹿 面倒 贸府
		sx = x - 1;
		ex = x + 1;
		sy = y - 1;
		ey = y + 1;

		Tile tile;
		tile = tileMap->getTile(x, y);
		if (tile.isBlock()) return true;


		for (int i = sx; i < ex + 1; i++)
		{
			if (i < 0 || i > MAP_SIZE_Y - 1) continue;
			for (int j = sy; j < ey + 1; j++)
			{
				if (j < 0 || j > MAP_SIZE_Y - 1) continue;

				tile = tileMap->getTile(i, j);
				if (tile.isBlock() && IntersectRect(&r, &rc, &tile.getRect()))
				{
					obj->setSpeed(0);
					obj->setAccel(0);
					
					if (i < x)
					{
						obj->setX((tile.getRect().right + 1) + (obj->getWidth() / 2));
					}
					else if (i > x)
					{
						obj->setX((tile.getRect().left) - (obj->getWidth() / 2));
					}

					if (j < y)
					{
						obj->setY((tile.getRect().bottom + 1) + (obj->getHeight() / 2));
					}
					else if (j > y)
					{
						obj->setY((tile.getRect().top) - (obj->getHeight() / 2));
					}

					return true;
				}
			}		
		}

		return false;
	}
	void Collision::tileCollision(MonsterManager* mm, TileMap* tileMap)
	{
		vUnit* mons = mm->getMonsters();
		viUnit iter = mons->begin();
		for (; iter != mons->end(); iter++)
		{
			tileCollision(*iter, tileMap);
		}
	}

	bool Collision::playerMonsterCollision(Player* player, MonsterManager* mm)
	{
		vUnit* mons = mm->getMonsters();
		RECT r;

		viUnit iter = mons->begin();
		for (; iter != mons->end(); iter++)
		{
			if (IntersectRect(&r, &player->getRect(), &(*iter)->getRect()) &&
				!player->isUnbeatable())
			{
				player->hit((player->getX() < (*iter)->getX()) ? LEFT : RIGHT, (*iter)->getAtk());
				return true;
			}
		}

		return false;
	}

	bool Collision::ammoMonsterCollision(Physical* ammo, MonsterManager* mm, int damage)
	{
		vUnit* mons = mm->getMonsters();
		RECT r;

		viUnit iter = mons->begin();
		for (; iter != mons->end(); iter++)
		{
			if (IntersectRect(&r, &ammo->getRect(), &(*iter)->getRect()))
			{
				(*iter)->hit((ammo->getSpeedX() < 0) ? LEFT : RIGHT, damage);
				return true;
			}
		}

		return false;
	}
}