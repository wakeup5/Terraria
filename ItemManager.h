#pragma once
#include "SingletonBase.h"
#include <vector>
#include "Item.h"

namespace Terraria
{
	typedef std::vector<Item*> vItem;
	typedef vItem::iterator viItem;
	class ItemManager : public SingletonBase < ItemManager >
	{
	private:
		vItem _vItem;
		viItem _viItem;
	public:
		HRESULT initialize();
		void release();

		Item* createItem(std::string itemName, int amount = 1);

		std::string getImageName(std::string itemName);
		int getMaxAmount(std::string itemName);

		void inputItemInfo();
		void addItemInfo(string name, string image, string spriteImage, 
			ITEM_TYPE item, EQUIPMENT_TYPE equip, int max, int hp, int mp, int atk, int def, float atkSpeed = 333, int shootNum = 0);

		ItemManager();
		~ItemManager();
	};
}
