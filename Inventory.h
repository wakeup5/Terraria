#pragma once
#include "TerrariaNode.h"
#include "Item.h"
#include "common.h"

namespace Terraria
{
	class Inventory : public Node
	{
	private:
		Item* _inven[INVENTORY_LENGTH];

	public:
		HRESULT initialize();
		void release();
		void update();
		void render(HDC hdc);

		Item* getList(){ return (Item*)_inven; }
		int getLength(){ return INVENTORY_LENGTH; }

		Item* const getItemInfo(int num);
		Item* getItem(int num);

		bool setItem(int num, Item* item);
		bool swap(int num, Item* item, Item** result);
		bool isExist(int num);

		int getEmptyNum();

		Inventory();
		virtual ~Inventory();
	};
}