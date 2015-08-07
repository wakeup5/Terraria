#pragma once
#include "TerrariaNode.h"
#include "Player.h"
#include "Inventory.h"
#include "TileMap.h"
#include "CombineUI.h"

namespace Terraria
{
	class UI : public Node
	{
	private:
		Player* _player;
		Inventory* _inven;
		TileMap* _map;

		CombineUI* _combineUI;

		bool _invenOpen;
		RECT _invenRc[INVENTORY_LENGTH];
		RECT _equipRc[EQUIP_NONE];

		

		Image* _invenBack;
		Image* _invenBackSelect;
		Image* _minimapBack;

		Item* _selectItem = NULL;
		Item* _selectItem2 = NULL;

		Item* _viewItem = NULL;

		int _selectNum = 0;
	public:
		HRESULT initialize(Player* player, Inventory* inven, TileMap* tileMap);
		void release();
		void update();
		void render(HDC hdc);

		void keyUpdate();
		void viewInfo();

		void invenOpenRender(HDC hdc);
		void invenCloseRender(HDC hdc);
		void viewInfoRender(HDC hdc);

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