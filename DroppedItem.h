#pragma once
#include "Physical.h"

namespace Terraria
{
	class Item;
	class DroppedItemManager;
	class DroppedItem : public Physical
	{
	private:
		std::string _itemName;
		Image* _image;
		int _amount;
		int _maxAmount;

		DroppedItemManager* _container;
	public:
		HRESULT initialize(){ return S_OK; }
		HRESULT initialize(string itemName, int amount = 1);
		void release();
		void update();
		void render(HDC hdc);

		std::string getName(){ return _itemName; }
		int getAmount(){ return _amount; }
		void addAmount(UINT amount){ _amount += amount; if (_amount > _maxAmount) _amount = _maxAmount; }

		bool isFull(){ return _amount == _maxAmount; }

		void setManager(DroppedItemManager* manager){ _container = manager; }

		DroppedItem();
		virtual ~DroppedItem();
	};
}