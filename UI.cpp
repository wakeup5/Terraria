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

	HRESULT UI::initialize(Player* player, Inventory* inven, TileMap* tileMap)
	{
		_player = player;
		_inven = inven;
		_map = tileMap;
		_invenOpen = false;

		_invenBack = IMAGEMANAGER->findImage("ui inven back");
		_invenBackSelect = IMAGEMANAGER->findImage("ui inven back select");
		_minimapBack = IMAGEMANAGER->findImage("ui minimap");

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
		_selectNum = 0;

		_player->setSelectItem(_inven->getItemInfo(_selectNum));

		return S_OK;
	}
	void UI::release()
	{

	}
	void UI::update()
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			_invenOpen = !_invenOpen;
			if (_invenOpen)
			{
				SOUNDMANAGER->play("ui open", _option.volume());
			}
			else
			{
				SOUNDMANAGER->play("ui close", _option.volume());
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			uiClickUpdate();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			uiRClickUpdate();
		}

		if (KEYMANAGER->isOnceKeyDown('1'))
		{
			_selectNum = 0;
			_player->setSelectItem(_inven->getItemInfo(_selectNum));
		}
		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			_selectNum = 1;
			_player->setSelectItem(_inven->getItemInfo(_selectNum));
		}
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			_selectNum = 2;
			_player->setSelectItem(_inven->getItemInfo(_selectNum));
		}
		if (KEYMANAGER->isOnceKeyDown('4'))
		{
			_selectNum = 3;
			_player->setSelectItem(_inven->getItemInfo(_selectNum));
		}
		if (KEYMANAGER->isOnceKeyDown('5'))
		{
			_selectNum = 4;
			_player->setSelectItem(_inven->getItemInfo(_selectNum));
		}
		if (KEYMANAGER->isOnceKeyDown('6'))
		{
			_selectNum = 5;
			_player->setSelectItem(_inven->getItemInfo(_selectNum));
		}
		if (KEYMANAGER->isOnceKeyDown('7'))
		{
			_selectNum = 6;
			_player->setSelectItem(_inven->getItemInfo(_selectNum));
		}
		if (KEYMANAGER->isOnceKeyDown('8'))
		{
			_selectNum = 7;
			_player->setSelectItem(_inven->getItemInfo(_selectNum));
		}
		if (KEYMANAGER->isOnceKeyDown('9'))
		{
			_selectNum = 8;
			_player->setSelectItem(_inven->getItemInfo(_selectNum));
		}
		if (KEYMANAGER->isOnceKeyDown('0'))
		{
			_selectNum = 9;
			_player->setSelectItem(_inven->getItemInfo(_selectNum));
		}

		if (_selectItem == NULL)
		{
			_selectItem2 = _inven->getItemInfo(_selectNum);
			_player->setSelectItem(_inven->getItemInfo(_selectNum));
		}
		//if (_selectItem2 != NULL) setSelectItem(NULL);

		if (_selectItem != NULL && _selectItem->getAmount() <= 0)
		{
			//SAFE_RELEASE(_selectItem);
			_selectItem = NULL;
			_player->setSelectItem(NULL);
		}
		if (_selectItem2 != NULL && _selectItem2->getAmount() <= 0)
		{
			//SAFE_RELEASE(_selectItem2);
			_selectItem2 = NULL;
			_player->setSelectItem(NULL);
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
				if (_selectNum == i)
				{
					_invenBackSelect->render(hdc, _invenRc[i].left, _invenRc[i].top, 200);
				}
				else
				{
					_invenBack->render(hdc, _invenRc[i].left, _invenRc[i].top, 200);
				}
				item = _inven->getItemInfo(i);
				if (item != NULL)
				{
					item->imageRender(hdc, _invenRc[i].left + 55 / 2, _invenRc[i].top + 55 / 2);

					if (item->getAmount() > 1)
					{
						writeText(hdc, to_string(item->getAmount()), _invenRc[i].left + 5, _invenRc[i].top + 2, 20, RGB(50, 50, 50), "HW Andy");
					}
				}
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
				if (_selectNum == i)
				{
					_invenBackSelect->render(hdc, _invenRc[i].left, 10, 150);
				}
				else
				{
					_invenBack->render(hdc, _invenRc[i].left, 10, 150);
				}
				item = _inven->getItemInfo(i);
				if (item != NULL)
				{
					item->imageRender(hdc, _invenRc[i].left + 55 / 2, _invenRc[i].top + 55 / 2);

					if (item->getAmount() > 1)
					{
						writeText(hdc, to_string(item->getAmount()), _invenRc[i].left + 5, _invenRc[i].top + 2, 20, RGB(50, 50, 50), "HW Andy");
					}
				}
			}

			if (_selectItem2 != NULL)
			{
				_selectItem2->getImage()->render(hdc, _option.mouseX(), _option.mouseY());
			}
		}

		if (_selectItem != NULL)
		{
			_selectItem->getImage()->render(hdc, _option.mouseX(), _option.mouseY());
		}	

		//맵, 플레이어
		int textColorValue = 255 - abs(sin(TIMEMANAGER->getWorldTime()) * 127);
		writeText(hdc, "Life : " + to_string(_player->getHp()) + "/" + to_string(_player->getMaxHp()), _option.width() - 160, 10, 25, RGB(textColorValue, textColorValue, textColorValue));

		return;
		int playerX = _player->getX() / METER_TO_PIXEL;
		int playerY = _player->getY() / METER_TO_PIXEL;
		int x, y;
		COLORREF color = RGB(0, 0, 0);

		for (int i = -30; i < 30; i++)
		{
			x = playerX + i;
			if (x < 0 || x > MAP_SIZE_X) continue;

			for (int j = -30; j < 30; j++)
			{
				y = playerY + j;
				if (y < 0 || y > MAP_SIZE_Y) continue;

				if (_map->getTile(x, y).getDarkDepth() > 3)
				{
					SetPixel(hdc, _option.width() - 120 + i, 120 + j, RGB(0, 0, 0));
					continue;
				}

				switch (_map->getTile(x, y).getType())
				{
				case TILE_GRASS:
					color = RGB(200, 100, 100);
					break;
				case TILE_STONE:
					color = RGB(50, 50, 50);
					break;
				case TILE_SILVER:
					color = RGB(180, 180, 180);
					break;
				case TILE_GOLD:
					color = RGB(255, 200, 0);
					break;
				case TILE_NONE: default:
					color = RGB(100, 100, 255);
					break;
				}
				SetPixel(hdc, _option.width() - 120 + i, 120 + j, color);
			}
		}
		_minimapBack->render(hdc, _option.width() - 180, 60);
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

				SOUNDMANAGER->play("ui grab", _option.volume());

				//플레이어 액션 안함
				_player->setAction(ACTION_NONE);
				_player->setActionTime(200);
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

				SOUNDMANAGER->play("ui grab", 0.5);

				//플레이어 액션 안함
				_player->setAction(ACTION_NONE);
				_player->setActionTime(200);
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
