#include "stdafx.h"
#include "Tile.h"

namespace Terraria
{
	HRESULT Tile::initialize(int x, int y)
	{
		_idX = x;
		_idY = y;
		_type = TILE_NONE;
		updateRect();

		_exist = 15;
		_tileImage = NULL;
		return S_OK;
	}

	void Tile::render(HDC hdc)
	{
		float x = (_idX * METER_TO_PIXEL) - _option.cameraX() + (_option.width() / 2);
		float y = (_idY * METER_TO_PIXEL) - _option.cameraY() + (_option.height() / 2);
		//if (_type != TILE_NONE) drawRectangle(hdc, x, y, METER_TO_PIXEL, METER_TO_PIXEL);//Rectangle(hdc, _rc.left, _rc.top + y, _rc.right + x, _rc.bottom + y);
		if (_tileImage != NULL) _tileImage->render(hdc, x, y);
	}

	void Tile::setType(TILE_TYPE type)
	{
		_type = type;
		SAFE_DELETE(_tileImage);

		switch (type)
		{
		case TILE_GRASS:
			_tileImage = IMAGEMANAGER->findImage("tile grass")->createSprite(16, 3);
			break;
		}

		if (_tileImage != NULL) _tileImage->setFrame(_exist, RANDOM->getInt(3));
	}

	Tile::Tile()
	{

	}
	Tile::~Tile()
	{

	}
}