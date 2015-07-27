#include "stdafx.h"
#include "TileMap.h"

namespace Terraria
{
	TileMap::TileMap()
	{

	}

	TileMap::~TileMap()
	{

	}

	HRESULT TileMap::initialize()
	{
		//ZeroMemory(&_tiles, sizeof(**_tiles) * MAP_SIZE_X * MAP_SIZE_Y);
		
		Image* image = IMAGEMANAGER->addImage("map basic", IMAGE("tile/map_basic"), MAP_SIZE_X, MAP_SIZE_Y);

		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			for (int y = 0; y < MAP_SIZE_Y; y++)
			{
				_tiles[x][y].initialize(x, y);
			}
		}

		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			for (int y = 0; y < MAP_SIZE_Y; y++)
			{
				COLORREF p = GetPixel(image->getMemDC(), x, y);

				if (p == RGB(0, 0, 0))
				{
					_tiles[x][y].setType(TILE_GRASS);

				}
				else
				{
					if (x > 0) _tiles[x - 1][y].subExistDirect(TILE_EXIST_RIGHT);
					if (y > 0) _tiles[x][y - 1].subExistDirect(TILE_EXIST_BOTTOM);
					if (x < MAP_SIZE_X - 1) _tiles[x + 1][y].subExistDirect(TILE_EXIST_LEFT);
					if (y < MAP_SIZE_Y - 1) _tiles[x][y + 1].subExistDirect(TILE_EXIST_TOP);
				}
			}
		}

		return S_OK;
	}
	void TileMap::release()
	{

	}
	void TileMap::update()
	{
		
	}
	void TileMap::render(HDC hdc)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			for (int y = 0; y < MAP_SIZE_Y; y++)
			{
				_tiles[x][y].render(hdc);
			}
		}
	}

	void TileMap::render(HDC hdc, int playerX, int playerY)
	{
		RECT r;
		int unitIdX = playerX / METER_TO_PIXEL;
		int unitIdY = playerY / METER_TO_PIXEL;

		int sx = (unitIdX - (_option.width() / METER_TO_PIXEL) / 2) - 5;
		int ex = (unitIdX + (_option.width() / METER_TO_PIXEL) / 2) + 5;
		int sy = (unitIdY - (_option.height() / METER_TO_PIXEL) / 2) - 5;
		int ey = (unitIdY + (_option.height() / METER_TO_PIXEL) / 2) + 5;

		if (sx < 0) sx = 0;
		if (ex > MAP_SIZE_X) ex = MAP_SIZE_X;
		if (sy < 0) sy = 0;
		if (ey > MAP_SIZE_Y) ey = MAP_SIZE_Y;

		for (int x = sx; x < ex; x++)
		{
			for (int y = sy; y < ey; y++)
			{
				_tiles[x][y].render(hdc);
			}
		}
	}

	bool TileMap::collision(POINT point)
	{
		return _tiles[point.x / METER_TO_PIXEL][point.y / METER_TO_PIXEL].getType() != TILE_NONE;
	}

	bool TileMap::collision(Unit* unit)
	{
		RECT r, unitRc = unit->getRect();
		RECT topRc = RECT{ unitRc.left + 2, unitRc.top - 1, unitRc.right, unitRc.bottom - 2 };
		RECT bottomRc = RECT{ unitRc.left, unitRc.top, unitRc.right, unitRc.bottom + 1 };
		RECT leftRc = RECT{ unitRc.left - 1, unitRc.top, unitRc.right , unitRc.bottom };
		RECT rightRc = RECT{ unitRc.left, unitRc.top, unitRc.right + 1, unitRc.bottom };

		int x = unit->getX() / METER_TO_PIXEL;
		int y = (unitRc.bottom - METER_TO_PIXEL / 2) / METER_TO_PIXEL;

		int sx, ex;

		//바닥 충돌 처리
		sx = x - 1;
		ex = x + 2;

		if (sx < 0) sx = 0;
		if (ex > MAP_SIZE_X) ex = MAP_SIZE_X;

		unit->setState(UNIT_STATE_FREEFALL);
		unit->setAccelY(GRAVITY_ACCEL);

		for (int i = sx; i < ex; i++)
		{
			if (unit->getSpeedY() >= -FLOAT_EPSILON && _tiles[i][y + 1].isBlock() &&
				IntersectRect(&r, &bottomRc, &_tiles[i][y + 1].getRect()))
			{
				unit->setFloor(_tiles[i][y + 1].getRect().top);
			}
		}

		//천장 충돌 처리
		for (int i = sx; i < ex; i++)
		{
			if (unit->getSpeedY() < -FLOAT_EPSILON && _tiles[i][y - 2].isBlock() &&
				IntersectRect(&r, &topRc, &_tiles[i][y - 2].getRect()))
			{
				unit->setSpeedY(0);
				unit->setAccelY(0);
			}
		}

		//좌우 충돌 처리
		if (_tiles[x - 1][y - 1].isBlock() &&
			IntersectRect(&r, &leftRc, &_tiles[x - 1][y - 1].getRect()))
		{
			unit->setSpeedX(0);
			unit->setAccelX(0);
			unit->setX(_tiles[x - 1][y - 1].getRect().right + 1 + unit->getWidth() / 2);
		}
		else if (unit->getSpeedY() >= -1 && 	_tiles[x - 1][y].isBlock() &&
			IntersectRect(&r, &unit->getRect(), &_tiles[x - 1][y].getRect()))
		{
			unit->setFloor(_tiles[x - 1][y].getRect().top);
		}

		if (_tiles[x + 1][y - 1].isBlock() &&
			IntersectRect(&r, &rightRc, &_tiles[x + 1][y - 1].getRect()))
		{
			unit->setSpeedX(0);
			unit->setAccelX(0);
			unit->setX(_tiles[x + 1][y - 1].getRect().left - unit->getWidth() / 2);
		}
		else if (unit->getSpeedY() >= -1 && _tiles[x + 1][y].isBlock() &&
			IntersectRect(&r, &unit->getRect(), &_tiles[x + 1][y].getRect()))
		{
			unit->setFloor(_tiles[x + 1][y].getRect().top);
		}

		if (unit->getSpeedY() >= -1 && _tiles[x][y].isBlock() &&
			IntersectRect(&r, &unit->getRect(), &_tiles[x][y].getRect()))
		{
			unit->setFloor(_tiles[x][y].getRect().top);
		}

		//화면 밖으로 못 나감
		if (unitRc.left < 0)
		{
			unit->setSpeedX(0);
			unit->setAccelX(0);
			unit->setX(0 + unit->getWidth() / 2);
		}

		if (unitRc.right >= _tiles[MAP_SIZE_X - 1][0].getRect().right)
		{
			unit->setSpeedX(0);
			unit->setAccelX(0);
			unit->setX(_tiles[MAP_SIZE_X - 1][0].getRect().right - unit->getWidth() / 2);
		}

		if (unitRc.top < 0)
		{
			unit->setSpeedY(0);
			unit->setAccelY(0);
			unit->setY(0 + unit->getHeight() / 2);
		}

		if (unitRc.bottom >= _tiles[0][MAP_SIZE_Y - 1].getRect().bottom)
		{
			unit->setSpeedY(0);
			unit->setAccelY(0);
			unit->setY(_tiles[0][MAP_SIZE_Y - 1].getRect().bottom - unit->getHeight() / 2);
		}

		return false;
	}
}