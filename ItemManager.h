#pragma once
#include "SingletonBase.h"
#include <vector>
#include "Item.h"

namespace Terraria
{
	class ItemManager : public SingletonBase < ItemManager >
	{
	private:
		std::vector<Item*> _vItem;
		std::vector<Item*>::iterator _viItem;
	public:
		HRESULT initialize();
		void release();

		Item* createItem(std::string itemName);

		std::string getImageName(std::string itemName);
		int getMaxAmount(std::string itemName);

		void inputItemInfo();
		void addItemInfo(string name, string image, string spriteImage, ITEM_TYPE item, EQUIPMENT_TYPE equip, int max, int hp, int mp, int atk, int def);

		ItemManager();
		~ItemManager();
	};
}
