#pragma once
#include "TerrariaNode.h"
#include "Inventory.h"

namespace Terraria
{
	class CombineUI : public Node
	{
	private:
		Inventory* _inven;

		Image* _invenBack;
		Image* _invenBackSelect;

		int _num;
		vItem _list;

		RECT _rc[5];

	public:
		HRESULT initialize(Inventory* inven);
		void release();
		void update();
		void render(HDC hdc);

		void updateList();

		Item* getViewItem();
		Item* getCombineItem();

		void deleteList();

		CombineUI();
		virtual ~CombineUI();
	};
}