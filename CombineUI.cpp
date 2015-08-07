#include "stdafx.h"
#include "CombineUI.h"

namespace Terraria
{
	CombineUI::CombineUI()
	{

	}

	CombineUI::~CombineUI()
	{

	}

	HRESULT CombineUI::initialize()
	{
		_invenBack = IMAGEMANAGER->findImage("ui inven back");
		_invenBackSelect = IMAGEMANAGER->findImage("ui inven back select");

		_num = 0;

		for (int i = 0; i < 5; i++)
		{
			_rc[i] = makeRect(10, _option.height() - (55 * (i + 1)) - 10, 55, 55);
		}

		//test
		for (int i = 0; i < 10; i++)
		{
			_list.push_back(ITEMMANAGER->createItem("bow basic"));
		}
		return S_OK;
	}
	void CombineUI::release()
	{
		viItem iter;
		while ((iter = _list.begin()) != _list.end())
		{
			_list.erase(iter);
		}

		_list.clear();
	}
	void CombineUI::update()
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP)) _num = max(0, _num - 1);
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) _num = min(_list.size() - 1, _num + 1);
	}
	void CombineUI::render(HDC hdc)
	{
		int start = max(_num - 2, 0);
		int end = min(_num + 2, _list.size() - 1) + 1;

		Image* itemImage = NULL;
		for (int i = start, j = 2 + (start - _num); i < end; i++, j++)
		{
			if (i == _num) _invenBackSelect->render(hdc, _rc[j].left, _rc[j].top);
			else _invenBack->render(hdc, _rc[j].left, _rc[j].top, 255 - (abs(j - 2) * 100));

			if (_list[i] == NULL || (itemImage = _list[i]->getImage()) == NULL) continue;
			itemImage->render(hdc, _rc[j].left + (55 - itemImage->getWidth()) / 2, _rc[j].top + (55 - itemImage->getHeight()) / 2);
		}

		writeText(hdc, "Combine", 10, _option.height() - 315, 25, RGB(255, 255, 255));
	}

	void CombineUI::updateList()
	{
		_num = _list.size() - 1;
	}

	Item* CombineUI::getViewItem()
	{
		Item* result = NULL;
		for (int i = 0; i < 5; i++)
		{
			if (PtInRect(&_rc[i], _option.mousePt()))
			{
				if (_num + (i - 2) < 0 || _num + (i - 2) > _list.size() - 1) return NULL;

				result = _list[_num + (i - 2)];
				break;
			}
		}

		return result;
	}
}