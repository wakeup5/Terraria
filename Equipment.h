#pragma once
//#include "Item.h"
#include "common.h"

namespace Terraria
{
	class Equipment : public Node
	{
	private:
		EquipType _type;
		Item* _item = NULL;

	public:
		HRESULT initialize(){ return S_OK; }
		HRESULT initialize(EQUIPMENT_TYPE type);
		void release();
		void update(){}
		void render(HDC hdc);

		bool dress(Item* item);
		bool undress(Item** result = NULL);
		bool swap(Item* item, Item** resultItem);
		
		Item* getItem(){ return _item; }
		bool isEquipped(){ return _item != NULL; }
		

		Equipment();
		virtual ~Equipment();
	};
}

