#pragma once
#include "TerrariaNode.h"

namespace Terraria
{
	class CombineUI : public Node
	{
	private:
		Image* _invenBack;
		Image* _invenBackSelect;

		int _num;
		vItem _list;

		RECT _rc[5];

	public:
		HRESULT initialize();
		void release();
		void update();
		void render(HDC hdc);

		void updateList();

		Item* getViewItem();

		CombineUI();
		virtual ~CombineUI();
	};
}