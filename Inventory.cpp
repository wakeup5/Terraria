#include "stdafx.h"
#include "Inventory.h"

namespace Terraria
{
	Inventory::Inventory()
	{
	}


	Inventory::~Inventory()
	{

	}
	HRESULT Inventory::initialize()
	{
		for (int i = 0; i < INVENTORY_LENGTH; i++)
		{
			_inven[i] = NULL;
		}
		return S_OK;
	}
	void Inventory::release()
	{

	}
	void Inventory::update()
	{

	}
	void Inventory::render(HDC hdc)
	{

	}

	Item* const Inventory::getItemInfo(int num)
	{
		if (!isExist(num)) return NULL;
		return _inven[num];
	}
	Item* Inventory::getItem(int num)
	{
		if (!isExist(num)) return NULL;

		Item* result = _inven[num];
		_inven[num] = NULL;
		return result;
	}

	bool Inventory::setItem(int num, Item* item)
	{
		if (isExist(num)) return false;

		_inven[num] = item;

		return true;
	}
	bool Inventory::swap(int num, Item* item, Item** result)
	{
		if (num < 0 || num > INVENTORY_LENGTH) return false;

		Item* temp = item;

		if (isExist(num))
		{
			*result = _inven[num];
			_inven[num] = NULL;
		}
		else
		{
			*result = NULL;
		}

		_inven[num] = temp;

		return true;
	}
	bool Inventory::isExist(int num)
	{
		if (num < 0 || num > INVENTORY_LENGTH) return false;

		return _inven[num] != NULL;
	}

	int Inventory::getEmptyNum()
	{
		for (int i = 10; i < INVENTORY_LENGTH; i++)
		{
			if (_inven[i] == NULL) return i;
		}

		return INVENTORY_LENGTH;
	}

	Item* Inventory::findItem(std::string itemName)
	{
		for (int i = 0; i < INVENTORY_LENGTH; i++)
		{
			if (_inven[i] == NULL) continue;
			if (_inven[i]->getName() == itemName)
			{
				return _inven[i];
			}
		}

		return NULL;
	}
}