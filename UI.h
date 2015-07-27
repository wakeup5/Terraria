#pragma once
#include "TerrariaNode.h"
#include "Player.h"
#include "Inventory.h"

namespace Terraria
{
	class UI : public Node
	{
	private:
		Player* _player;
		Inventory* _inven;

		bool _invenOpen;
		RECT _invenRc[INVENTORY_LENGTH];
		RECT _equipRc[EQUIP_NONE];

		Image* _invenBack;

		Item* _selectItem = NULL;
	public:
		HRESULT initialize(Player* player, Inventory* inven);
		void release();
		void update();
		void render(HDC hdc);

		inline Item* getSelectItem(){ return _selectItem; }
		inline void setSelectItem(Item* item){ _selectItem = item; }

	private:
		void uiClickUpdate();
		void uiRClickUpdate();
	public:
		UI();
		virtual ~UI();
	};
}