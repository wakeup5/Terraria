#include "stdafx.h"
#include "Equipment.h"

namespace Terraria
{
	Equipment::Equipment()
	{
	}


	Equipment::~Equipment()
	{
	}

	HRESULT Equipment::initialize(EQUIPMENT_TYPE type)
	{
		_type = type;
		_item = NULL;

		return S_OK;
	}
	void Equipment::release()
	{

	}
	void Equipment::render(HDC hdc)
	{
		if (isEquipped()) _item->render(hdc);
	}

	bool Equipment::dress(Item* item)
	{
		if (item == NULL) return false;
		if (isEquipped() || 
			_type != item->getEquipType()) return false;

		_item = item;
		return true;
	}
	bool Equipment::undress(Item** result)
	{
		if (!isEquipped()) return false;
		
		*result = _item;

		_item = NULL;
		return true;
	}
	bool Equipment::swap(Item* item, Item** resultItem)
	{
		if (_type != item->getEquipType()) return false;

		if (isEquipped())
		{
			*resultItem = _item;
			undress();
		}


		return dress(item);
	}
}