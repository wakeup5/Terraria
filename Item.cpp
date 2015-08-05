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

	HRESULT Item::initialize(string itemName, string imageName, string spriteImageName, EQUIPMENT_TYPE equipType)
	{
		_itemName = itemName;
		_image = IMAGEMANAGER->findImage(imageName);
		_equipImage = IMAGEMANAGER->findImage(spriteImageName);

		if (_image == NULL || _equipImage == NULL) return E_FAIL;

		//_spriteImage = _equipImage->createSprite(2, 20);

		_equipType = equipType;
		_itemType = ITEM_EQUIP;

		_maxAmount = 1;
		_currentAmount = 1;

		return S_OK;
	}

	HRESULT Item::initialize(string itemName, string imageName, string spriteImageName, ITEM_TYPE itemType, int maxAmount)
	{
		_itemName = itemName;
		_image = IMAGEMANAGER->findImage(imageName);
		Image* image = IMAGEMANAGER->findImage(spriteImageName);

		if (_image == NULL || image == NULL) return E_FAIL;

		_spriteImage = image->createSprite(2, 20);

		_equipType = EQUIP_NONE;
		_itemType = itemType;

		_maxAmount = maxAmount;
		if (_maxAmount <= 0) _maxAmount = 1;
		else if (_maxAmount > 999) _maxAmount = 999;

		_currentAmount = 1;
		return S_OK;
	}

	HRESULT Item::initialize(
		string itemName, string imageName, string spriteImageName, ITEM_TYPE type, EQUIPMENT_TYPE equipType,
		int maxAmount, int hp, int mp, int attack, int defense, float atkSpeed, int shootNum)
	{
		if (type == ITEM_EQUIP)
		{
			initialize(itemName, imageName, spriteImageName, equipType);
		}
		else
		{
			initialize(itemName, imageName, spriteImageName, type, maxAmount);
		}

		setAbillity(hp, mp, attack, defense, atkSpeed, shootNum);

		return S_OK;
	}

	void Item::release()
	{
		SAFE_RELEASE(_spriteImage);
	}

	void Item::imageRender(HDC hdc, float centerX, float centerY)
	{
		if (_image != NULL) _image->render(hdc, centerX - _image->getWidth() / 2, centerY - _image->getHeight() / 2);
	}
}
