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

	HRESULT CombineUI::initialize(Inventory* inven)
	{
		_inven = inven;
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

		_num = min(_list.size() - 1, max(0, _num));
	}
	void CombineUI::render(HDC hdc)
	{
		if (_list.size() == 0) return;

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
		deleteList();
		_list.clear();

		Table firstList;
		Item* temp;
		string tempName;
		int tempAmount;

		Table* table = DATABASE->getTable("combine");
		Table::iterator iter;
		for (iter = table->begin(); iter != table->end(); iter++)
		{
			tempName = (*iter)->find("name1")->second;
			tempAmount = atoi((*iter)->find("amount1")->second.c_str());

			temp = _inven->findItem(tempName);

			if (temp != NULL && temp->getAmount() >= tempAmount)
			{
				tempName = (*iter)->find("name2")->second;
				tempAmount = atoi((*iter)->find("amount2")->second.c_str());
				if (tempName == "" || tempAmount <= 0)
				{
					tempName = (*iter)->find("resultname")->second;
					tempAmount = atoi((*iter)->find("resultamount")->second.c_str());
					_list.push_back(ITEMMANAGER->createItem(tempName, tempAmount));
				}
				else
				{
					firstList.insert(*iter);
				}
			}
		}

		for (iter = firstList.begin(); iter != firstList.end(); iter++)
		{
			tempName = (*iter)->find("name2")->second;
			tempAmount = atoi((*iter)->find("amount2")->second.c_str());

			temp = _inven->findItem(tempName);

			if (temp != NULL && temp->getAmount() >= tempAmount)
			{
				tempName = (*iter)->find("resultname")->second;
				tempAmount = atoi((*iter)->find("resultamount")->second.c_str());
				_list.push_back(ITEMMANAGER->createItem(tempName, tempAmount));
			}
		}

		//_num = max(0, _list.size() - 1);
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

	Item* CombineUI::getCombineItem()
	{
		Item* result = NULL;
		for (int i = 0; i < 5; i++)
		{
			if (PtInRect(&_rc[i], _option.mousePt()))
			{
				if (_num + (i - 2) < 0 || _num + (i - 2) > _list.size() - 1) return NULL;

				result = ITEMMANAGER->createItem(_list[_num + (i - 2)]->getName(), _list[_num + (i - 2)]->getAmount());
				break;
			}
		}
		if (result == NULL) return NULL;

		Row* row = DATABASE->get("combine", result->getName());
		string tempName = row->find("name1")->second.c_str();
		int tempAmount = atoi(row->find("amount1")->second.c_str());

		_inven->findItem(tempName)->subAmount(tempAmount);
		
		tempName = row->find("name2")->second.c_str();
		tempAmount = atoi(row->find("amount2")->second.c_str());
		if (tempName != "" && tempAmount > 0)
		{
			_inven->findItem(tempName)->subAmount(tempAmount);
		}

		return result;
	}

	void CombineUI::deleteList()
	{
		for (int i = 0; i < _list.size(); i++)
		{
			_list[i]->release();
		}

		_list.clear();
	}
}