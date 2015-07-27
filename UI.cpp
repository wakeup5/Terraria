#include "stdafx.h"
#include "UI.h"

namespace Terraria
{
	UI::UI()
	{

	}

	UI::~UI()
	{

	}

	HRESULT UI::initialize(Player* player, Inventory* inven)
	{
		_player = player;
		_inven = inven;
		_invenOpen = false;

		_invenBack = IMAGEMANAGER->addImage("inven back", IMAGE("ui/Inventory_Back"), 52, 52, TRUE, RGB(255, 0, 255));

		float x, y;

		for (int i = 0; i < INVENTORY_LENGTH; i++)
		{
			x = 10 + ((i % 10) * 55);
			y = 10 + ((i / 10) * 55);
			_invenRc[i] = makeRect(x, y, 52, 52);
		}

		for (int i = 0; i < EQUIP_NONE; i++)
		{
			x = _option.width() - 55;
			y = 230 + 55 * i;
			_equipRc[i] = makeRect(x, y, 52, 52);
		}

		_player->setSelectItem(_inven->getItemInfo(0));

		return S_OK;
	}
	void UI::release()
	{

	}
	void UI::update()
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			if (_invenOpen)
			{

			}
			else
			{

			}
			_invenOpen = !_invenOpen;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			uiClickUpdate();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			uiRClickUpdate();
		}

	}
	void UI::render(HDC hdc)
	{
		Item* item;
		if (_invenOpen)
		{
			//인벤토리 출력
			for (int i = 0; i < INVENTORY_LENGTH; i++)
			{
				_invenBack->render(hdc, _invenRc[i].left, _invenRc[i].top, 200);
				item = _inven->getItemInfo(i);
				if (item != NULL) item->imageRender(hdc, _invenRc[i].left + 55 / 2, _invenRc[i].top + 55 / 2);
			}

			//장비 장착 정보
			for (int i = 0; i < EQUIP_NONE; i++)
			{
				_invenBack->render(hdc, _equipRc[i].left, _equipRc[i].top, 200);
				item = _player->getEquip()->getItem((EQUIPMENT_TYPE)i);
				if (item != NULL) item->imageRender(hdc, _equipRc[i].left + 55 / 2, _equipRc[i].top + 55 / 2);
			}
			
		}
		else
		{
			//인벤토리 안열어도 10개는 출력
			for (int i = 0; i < 10; i++)
			{
				_invenBack->render(hdc, _invenRc[i].left, 10, 150);
				item = _inven->getItemInfo(i);
				if (item != NULL) item->imageRender(hdc, _invenRc[i].left + 55 / 2, _invenRc[i].top + 55 / 2);
			}
		}

		if (_selectItem != NULL)
		{
			_selectItem->getImage()->render(hdc, _option.mouseX(), _option.mouseY());
		}
	}

	void UI::uiClickUpdate()
	{
		int maxLength = (_invenOpen) ? INVENTORY_LENGTH : 10;
		for (int i = 0; i < maxLength; i++)
		{
			if (PtInRect(&_invenRc[i], _option.mousePt()))
			{
				//선택된 아이템이 없고, 클릭한 자리에 아이템이 있으면 - 아이템 빼옴
				if (_selectItem == NULL && _inven->getItemInfo(i) != NULL)
				{
					_selectItem = _inven->getItem(i);
				}
				//선택된 아이템이 있고, 클릭한 자리에 아이템이 없으면 - 아이템 집어넣음
				else if (_selectItem != NULL && _inven->getItemInfo(i) == NULL)
				{
					_inven->setItem(i, _selectItem);
					_selectItem = NULL;
				}
				//둘다 있을때 - 두개를 바꿈
				else if (_selectItem != NULL && _inven->getItemInfo(i) != NULL)
				{
					_inven->swap(i, _selectItem, &_selectItem);
				}
				_player->setSelectItem(_selectItem);
			}
		}

		Equip* equip = _player->getEquip();
		for (int i = 0; i < EQUIP_NONE; i++)
		{
			if (PtInRect(&_equipRc[i], _option.mousePt()))
			{
				//선택한 아이템과 타입이 다르면 지나감
				if (_selectItem != NULL && _selectItem->getEquipType() != i) continue;

				//선택된 아이템이 없고, 클릭한 자리에 아이템이 있으면 - 아이템 빼옴
				if (_selectItem == NULL && equip->getItem((EQUIPMENT_TYPE)i) != NULL)
				{
					equip->undress((EQUIPMENT_TYPE)i, &_selectItem);
				}
				//선택된 아이템이 있고, 클릭한 자리에 아이템이 없으면 - 아이템 집어넣음
				else if (_selectItem != NULL && equip->getItem((EQUIPMENT_TYPE)i) == NULL)
				{
					equip->dress(_selectItem);
					_selectItem = NULL;
				}
				//둘다 있을때 - 두개를 바꿈
				else if (_selectItem != NULL && equip->getItem((EQUIPMENT_TYPE)i) != NULL)
				{
					equip->swap(_selectItem, &_selectItem);
				}
				_player->setSelectItem(_selectItem);
			}
		}
	}

	void UI::uiRClickUpdate()
	{
		int maxLength = (_invenOpen) ? INVENTORY_LENGTH : 10;
		Equip* equip = _player->getEquip();

		for (int i = 0; i < maxLength; i++)
		{
			if (PtInRect(&_invenRc[i], _option.mousePt()))
			{
				//선택된 자리에 아이템이 있고, 방어구면
				if (_inven->getItemInfo(i) != NULL && _inven->getItemInfo(i)->getItemType() == ITEM_EQUIP)
				{
					//이미 장착된 아이템이 있으면 - 바꿈
					if (equip->isEquipped(_inven->getItemInfo(i)->getEquipType()))
					{
						Item* temp = NULL;
						equip->swap(_inven->getItem(i), &temp);
						_inven->setItem(i, temp);
					}
					//장착된 아이템이 없으면 - 장착
					else
					{
						equip->dress(_inven->getItem(i));
					}
				}
			}
		}

		for (int i = 0; i < EQUIP_NONE; i++)
		{
			if (PtInRect(&_equipRc[i], _option.mousePt()))
			{
				int emptyNum = _inven->getEmptyNum();

				//인벤토리에 빈 곳이 있고, 장착된 아이템이 있으면 - 벗음
				if (emptyNum != INVENTORY_LENGTH &&
					equip->isEquipped((EQUIPMENT_TYPE)i))
				{
					Item* temp = NULL;
					equip->undress((EQUIPMENT_TYPE)i, &temp);
					_inven->setItem(emptyNum, temp);
				}
			}
		}
	}
}
