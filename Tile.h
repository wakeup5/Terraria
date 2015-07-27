#pragma once
#include "TerrariaObject.h"

namespace Terraria
{
	class Tile : public Node
	{
	private:
		int _idX;
		int _idY;

		RECT _rc;

		TileType _type;

		SpriteImage* _tileImage;

		int _exist;
	public:
		HRESULT initialize(int x, int y);
		void render(HDC hdc);

		void setIdX(int x){ _idX = x; updateRect(); }
		void setIdY(int y){ _idY = y; updateRect(); }

		int getIdX(){ return _idX; }
		int getIdY(){ return _idY; }

		RECT getRect(){ return _rc; }

		void setType(TILE_TYPE type);
		TILE_TYPE getType(){ return _type; } 

		bool isBlock(){ return _type != TILE_NONE; }

		void addExistDirect(TILE_EXIST_DIRECT tile)
		{ 
			_exist |= tile; 
			if (_tileImage != NULL) _tileImage->setFrame(_exist, RANDOM->getInt(3)); 
		}
		void subExistDirect(TILE_EXIST_DIRECT tile)
		{ 
			if (myUtil::existBit(_exist, tile)) _exist -= tile; 
			if (_tileImage != NULL) _tileImage->setFrame(_exist, RANDOM->getInt(3));
		}
	private:
		void updateRect(){ _rc = makeRect(_idX * METER_TO_PIXEL, _idY * METER_TO_PIXEL, METER_TO_PIXEL, METER_TO_PIXEL); }

	public:
		Tile();
		virtual ~Tile();
	};
	
}
