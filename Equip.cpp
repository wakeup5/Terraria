#include "stdafx.h"
#include "Equip.h"

namespace Terraria
{
	Equip::Equip()
	{
	}


	Equip::~Equip()
	{
	}

	HRESULT Equip::initialize()
	{
		for (int i = 0; i < EQUIP_NONE; i++)
		{
			_equipment[i] = new Equipment;
			_equipment[i]->initialize((EQUIPMENT_TYPE)i);
			_equipment[i]->dress(NULL);
		}

		return S_OK;
	}
	void Equip::release()
	{

	}
	void Equip::update()
	{

	}
	void Equip::render(HDC hdc)
	{

	}

	const ItemAbillity Equip::getTotalAbillity()
	{
		ItemAbillity result;

		ZeroMemory(&result, sizeof(result));

		for (int i = 0; i < EQUIP_NONE; i++)
		{
			Item* item = _equipment[i]->getItem();

			if (item == NULL) continue;

			ItemAbillity temp = item->getAbillity();
			result.HP += temp.HP;
			result.MP += temp.MP;
			result.attack += temp.attack;
			result.defense += temp.defense;
		}

		return result;
	}

	bool Equip::dress(Item* item)
	{
		if (item == NULL) return false;
		if (_equipment[item->getEquipType()]->isEquipped()) return false;

		return _equipment[item->getEquipType()]->dress(item);
	}
	bool Equip::undress(EQUIPMENT_TYPE type, Item** result)
	{
		if (!_equipment[type]->isEquipped()) return false;

		return _equipment[type]->undress(result);
	}
	bool Equip::swap(Item* item, Item** result)
	{
		if (item == NULL) return false;

		return _equipment[item->getEquipType()]->swap(item, result);
	}

	bool Equip::isEquipped(EQUIPMENT_TYPE type)
	{
		return _equipment[type]->isEquipped();
	}
	/*
	void Equip::setImageFrame(EQUIPMENT_TYPE type, int frameX, int frameY)
	{
		if (_equipment[type] == NULL || _equipment[type]->getItem() == NULL) return;

		_equipment[type]->getItem()->getSpriteImate()->setFrameY(frameY);
		_equipment[type]->getItem()->getSpriteImate()->setFrameX(frameX);
	}

	void Equip::setImageFrameX(EQUIPMENT_TYPE type, int frameX)
	{
		if (_equipment[type] == NULL || _equipment[type]->getItem() == NULL) return;

		_equipment[type]->getItem()->getSpriteImate()->setFrameX(frameX);
	}
	void Equip::setImageFrameY(EQUIPMENT_TYPE type, int frameY)
	{
		if (_equipment[type] == NULL || _equipment[type]->getItem() == NULL) return;

		_equipment[type]->getItem()->getSpriteImate()->setFrameY(frameY);
	}

	SpriteImage* const Equip::getSpriteImage(EQUIPMENT_TYPE type)
	{
		if (_equipment[type] == NULL || _equipment[type]->getItem() == NULL) return NULL;
		
		return _equipment[type]->getItem()->getSpriteImate();
	}

	void Equip::setCenter(float x, float y)
	{
		for (int i = 0; i < EQUIP_NONE; i++)
		{
			if (_equipment[i] == NULL || _equipment[i]->getItem() == NULL) continue;

			_equipment[i]->getItem()->getSpriteImate()->setCenter(x, y);
		}
	}
	*/

	Item* const Equip::getItem(EQUIPMENT_TYPE type)
	{
		return _equipment[type]->getItem();
	}

	Image* Equip::getEquipImage(EQUIPMENT_TYPE type)
	{
		Image* image = NULL;

		if (_equipment[type]->isEquipped())
		{
			image = _equipment[type]->getItem()->getEquipImage();
		}

		return image;
	}
}