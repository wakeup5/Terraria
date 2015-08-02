#pragma once
#include "Tile.h"
#include "TerrariaUnit.h"
#include "DroppedItemManager.h"

namespace Terraria
{
	class TileMap : public Node
	{
	private:
		Tile _tiles[MAP_SIZE_X][MAP_SIZE_Y];

		DroppedItemManager* _dropItemManager;
	public:
		virtual HRESULT initialize(DroppedItemManager* dropItemManager);
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
		void setTileType(int x, int y, TILE_TYPE type);
		void setTileType(POINT p, TILE_TYPE type);

		void setDepth(int x, int y);

		bool pickaxe(int indexX, int indexY);

		TileMap();
		virtual ~TileMap();
	};
}
