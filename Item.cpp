#include "stdafx.h"
#include "Item.h"

namespace Terraria
{
	Item::Item()
	{
	}


	Item::~Item()
	{
	}

	HRESULT Item::initialize(string imageName, string spriteImageName, EQUIPMENT_TYPE equipType)
	{
		_image = IMAGEMANAGER->findImage(imageName);
		Image* image = IMAGEMANAGER->findImage(spriteImageName);

		if (_image == NULL || image == NULL) return E_FAIL;

		_spriteImage = image->createSprite(2, 20);

		_equipType = equipType;
		_itemType = ITEM_EQUIP;

		return S_OK;
	}

	HRESULT Item::initialize(string imageName, string spriteImageName, ITEM_TYPE itemType)
	{
		_image = IMAGEMANAGER->findImage(imageName);
		Image* image = IMAGEMANAGER->findImage(spriteImageName);

		if (_image == NULL || image == NULL) return E_FAIL;

		_spriteImage = image->createSprite(2, 20);

		_equipType = EQUIP_NONE;
		_itemType = itemType;

		return S_OK;
	}

	void Item::release()
	{
		SAFE_RELEASE(_spriteImage);
	}

	void Item::imageRender(HDC hdc, float centerX, float centerY)
	{
		if (_image != NULL)
			_image->render(hdc, centerX - _image->getWidth() / 2, centerY - _image->getHeight() / 2);
	}
}
