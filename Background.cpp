#include "stdafx.h"
#include "Background.h"

namespace Terraria
{
	Background::Background()
	{
		
	}

	Background::~Background()
	{

	}

	HRESULT Background::initailize()
	{
		//¹è°æ
		IMAGEMANAGER->addImage("bgSky", IMAGE("background/sky"), 48, 1300, TRUE, TRANS_COLOR);
		IMAGEMANAGER->addImage("bg grass hear", IMAGE("background/grass/hear"), 1024, 509, TRUE, TRANS_COLOR);
		IMAGEMANAGER->addImage("bg grass that", IMAGE("background/grass/that"), 1024, 346, TRUE, TRANS_COLOR);
		IMAGEMANAGER->addImage("bg grass there", IMAGE("background/grass/there"), 1024, 435, TRUE, TRANS_COLOR);
		IMAGEMANAGER->addImage("bgUnder", IMAGE("background/under"), 160, 96, TRUE, TRANS_COLOR);

		BgSet temp;
		temp.bg = IMAGEMANAGER->findImage("bgSky");
		temp.hear = IMAGEMANAGER->findImage("bg grass hear");
		temp.that = IMAGEMANAGER->findImage("bg grass that");
		temp.there = IMAGEMANAGER->findImage("bg grass there");
		temp.height = 450;

		_bgMap.insert(make_pair("grass", temp));
		_select = temp;

		temp.bg = IMAGEMANAGER->findImage("bgUnder");
		temp.hear = NULL;
		temp.that = NULL;
		temp.there = NULL;
		temp.height = 450;

		_bgMap.insert(make_pair("under", temp));


		return S_OK;
	}
	void Background::render(HDC hdc)
	{
		if (_bgMap.size() < 0) return;

		if (_select.bg != NULL ) 
			_select.bg->loopRender(
				hdc, 
				&makeRect(0, 0, _option.width(), _option.height()),
				_option.cameraX() / 5,
				_option.cameraY() / 5);

		if (_select.there != NULL)
			_select.there->loopRender(
				hdc, 
				&makeRect(0, _option.height() - (_option.cameraY() / 20) - _select.there->getHeight(), _option.width(), _option.height()),
				_option.cameraX() / 5, 
				0);
		
		if (_select.that != NULL)
			_select.that->loopRender(
				hdc, 
				&makeRect(0, _option.height() - (_option.cameraY() / 12) + 80 - _select.that->getHeight(), _option.width(), _option.height()),
				_option.cameraX() / 3, 
				0);
		
		if (_select.hear != NULL)
			_select.hear->loopRender(
				hdc,
				&makeRect(0, _option.height() - (_option.cameraY() / 8) + 250 - _select.hear->getHeight(), _option.width(), _option.height()),
				_option.cameraX() / 2,
				0);
	}

	void Background::change(string key)
	{
		_bgMapIter = _bgMap.find(key);

		if (_bgMapIter != _bgMap.end())
		{
			_select = _bgMapIter->second;
		}
		else
		{
			_select = _bgMap.begin()->second;
		}
	}

	void Background::change(string key, float offset, float min, float max)
	{
		if (offset > min && offset < max)
		{
			change(key);
		}
	}

}