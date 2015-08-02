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

		_exist = 0;
		_tileImage = NULL;

		_darkDepth = 4;

		_tileNum = RANDOM->getInt(3);

		return S_OK;
	}

	void Tile::render(HDC hdc)
	{
		float x = (_idX * METER_TO_PIXEL) - _option.cameraX() + (_option.width() / 2);
		float y = (_idY * METER_TO_PIXEL) - _option.cameraY() + (_option.height() / 2);
		
		if (_tileImage != NULL) _tileImage->render(hdc, x, y);
	}

	void Tile::setType(TILE_TYPE type)
	{
		_type = type;
		SAFE_DELETE(_tileImage);

		switch (type)
		{
		case TILE_GRASS:
			_tileImage = IMAGEMANAGER->findImage("tile grass")->createSprite(16, 15);
			_hp = 2;
			break;
		case TILE_STONE:
			_tileImage = IMAGEMANAGER->findImage("tile stone")->createSprite(16, 15);
			_hp = 3;
			break;
		case TILE_SILVER:
			_tileImage = IMAGEMANAGER->findImage("tile silver")->createSprite(16, 15);
			_hp = 3;
			break;
		case TILE_GOLD:
			_tileImage = IMAGEMANAGER->findImage("tile gold")->createSprite(16, 15);
			_hp = 2;
			break;
		}
		_tileNum = RANDOM->getInt(3);
		setDarkDepth(_darkDepth);
	}

	void Tile::setDarkDepth(int depth)
	{
		_darkDepth = depth;
		if (_darkDepth < 0) _darkDepth = 0;
		if (_darkDepth > 4) _darkDepth = 4;

		if (_tileImage != NULL) _tileImage->setFrame(_exist, _tileNum + _darkDepth * 3);
	}

	bool Tile::pickaxe()
	{
		_hp--;

		if (_type == TILE_GRASS)
		{
			int num = RANDOM->getInt(3);
			if (num == 0) SOUNDMANAGER->play("grass dig 2", _option.volume());
			if (num == 1) SOUNDMANAGER->play("grass dig 1", _option.volume());
			if (num == 2) SOUNDMANAGER->play("grass dig 0", _option.volume());
		}
		else if (_type != TILE_NONE)
		{
			int num = RANDOM->getInt(3);
			if (num == 0) SOUNDMANAGER->play("iron dig 0", _option.volume());
			if (num == 1) SOUNDMANAGER->play("iron dig 1", _option.volume());
			if (num == 2) SOUNDMANAGER->play("iron dig 2", _option.volume());
		}

		if (_hp <= 0)
		{
			setType(TILE_NONE);
			return true;
		}

		return false;
	}

	Tile::Tile()
	{

	}
	Tile::~Tile()
	{

	}
}