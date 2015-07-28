#pragma once
#include "Tile.h"
#include "TerrariaUnit.h"

namespace Terraria
{
	class TileMap : public Node
	{
	private:
		Tile _tiles[MAP_SIZE_X][MAP_SIZE_Y];

	public:
		virtual HRESULT initialize();
		virtual void release();
		virtual void update();
		virtual void render(HDC hdc);
		void render(HDC hdc, int playerX, int playerY);

		bool collision(Unit* unit);
		bool collision(POINT point);

		Tile getTile(int x, int y){ return _tiles[x][y]; }

		float getWidth(){ return _tiles[MAP_SIZE_X - 1][0].getRect().right; }
		float getHeight(){ return _tiles[0][MAP_SIZE_Y - 1].getRect().bottom; }

		POINT getPointByMouse(POINT mouse){ return makePoint(mouse.x / METER_TO_PIXEL, mouse.y / METER_TO_PIXEL); }
		void setTileType(int x, int y, TILE_TYPE type)
		{ 
			_tiles[x][y].setType(type); 
			if (type == TILE_NONE)
			{
				if (x > 0) _tiles[x - 1][y].subExistDirect(TILE_EXIST_RIGHT);
				if (y > 0) _tiles[x][y - 1].subExistDirect(TILE_EXIST_BOTTOM);
				if (x < MAP_SIZE_X - 1) _tiles[x + 1][y].subExistDirect(TILE_EXIST_LEFT);
				if (y < MAP_SIZE_Y - 1) _tiles[x][y + 1].subExistDirect(TILE_EXIST_TOP);
			}
		}
		void setTileType(POINT p, TILE_TYPE type)
		{ 
			_tiles[p.x][p.y].setType(type);
			if (type == TILE_NONE)
			{
				if (p.x > 0) _tiles[p.x - 1][p.y].subExistDirect(TILE_EXIST_RIGHT);
				if (p.y > 0) _tiles[p.x][p.y - 1].subExistDirect(TILE_EXIST_BOTTOM);
				if (p.x < MAP_SIZE_X - 1) _tiles[p.x + 1][p.y].subExistDirect(TILE_EXIST_LEFT);
				if (p.y < MAP_SIZE_Y - 1) _tiles[p.x][p.y + 1].subExistDirect(TILE_EXIST_TOP);
			}
		}

		bool pickaxe(int indexX, int indexY);

		TileMap();
		virtual ~TileMap();
	};
}
