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

	HRESULT UI::initialize(Player* player, Inventory* inven, TileMap* tileMap, DroppedItemManager* dm)
	{
		_player = player;
		_inven = inven;
		_map = tileMap;
		_dm = dm;
		_invenOpen = false;

		_combineUI = new CombineUI;
		_combineUI->initialize(_inven);

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
		_combineUI->release();
	}
	void UI::update()
	{
		keyUpdate();
		_combineUI->update();

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

		viewInfo();
	}
	void UI::keyUpdate()
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			_invenOpen = !_invenOpen;
			if (_invenOpen)
			{
				SOUNDMANAGER->play("ui open", _option.volume());
				_combineUI->updateList();
			}
			else
			{
				SOUNDMANAGER->play("ui close", _option.volume());
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			uiClickUpdate();
			_combineUI->updateList();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			uiRClickUpdate();
			_combineUI->updateList();
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
	}
	void UI::viewInfo()
	{
		//if (_viewItem != NULL) return;

		//아이템에 마우스 올렸을때 보이는 정보
		int length = (_invenOpen ? INVENTORY_LENGTH : 10);
		RECT r;
		for (int i = 0; i < length; i++)
		{
			if (PtInRect(&_invenRc[i], _option.mousePt()) && _inven->getItemInfo(i) != NULL)
			{
				_viewItem = _inven->getItemInfo(i);
				return;
			}
		}

		for (int i = 0; i < EQUIP_NONE; i++)
		{
			if (PtInRect(&_equipRc[i], _option.mousePt()) && _player->getEquip()->getItem((EQUIPMENT_TYPE)i) != NULL)
			{
				_viewItem = _player->getEquip()->getItem((EQUIPMENT_TYPE)i);
				return;
			}
		}

		_viewItem = _combineUI->getViewItem();

		//_viewItem = NULL;
	}
	void UI::render(HDC hdc)
	{
		if (_invenOpen)
		{
			invenOpenRender(hdc);
			_combineUI->render(hdc);
		}
		else
		{
			invenCloseRender(hdc);
		}


		if (_selectItem != NULL)
		{
			_selectItem->getImage()->render(hdc, _option.mouseX(), _option.mouseY());
			if (_selectItem->getAmount() > 1)
			{
				writeText(hdc, to_string(_selectItem->getAmount()), _option.mouseX() + 10, _option.mouseY() + 10, 25, RGB(255, 255, 255));
			}
		}	

		if (_viewItem != NULL)
		{
			viewInfoRender(hdc);
		}

		//맵, 플레이어
		int textColorValue = 255 - abs(sin(TIMEMANAGER->getWorldTime()) * 127);
		char lifeStr[16];
		sprintf_s(lifeStr, "Life : %.0f/%d", _player->getHp(), _player->getMaxHp());
		writeText(hdc, lifeStr, _option.width() - 160, 10, 25, RGB(textColorValue, textColorValue, textColorValue));

		sprintf_s(lifeStr, "Mana : %.0f/%d", _player->getMp(), _player->getMaxMp());
		writeText(hdc, lifeStr, _option.width() - 160, 40, 25, RGB(textColorValue, textColorValue, textColorValue));
	}

	void UI::invenOpenRender(HDC hdc)
	{
		Item* item;
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
	void UI::invenCloseRender(HDC hdc)
	{
		Item* item;
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
	void UI::viewInfoRender(HDC hdc)
	{
		float x = _option.mouseX() + 10;
		float y = _option.mouseY() + 10;
		if (x > _option.width() - 150) x = _option.width() - 150;
		if (y > _option.height() - 150) y = _option.height() - 150;
		RECT rc = makeRect(x, y, 200, 200);
		char str[200];
		sprintf_s(str, "%s\n", _viewItem->getName().c_str());

		if (_viewItem->getItemType() <= ITEM_EQUIP) sprintf_s(str, "%s%s\n", str, "Equipment");
		else if (_viewItem->getItemType() <= ITEM_WEAPON_MAGIC) sprintf_s(str, "%s%s\n", str, "Weapon");
		else if (_viewItem->getItemType() <= ITEM_TOOL_AXE) sprintf_s(str, "%s%s\n", str, "Tool");
		else if (_viewItem->getItemType() <= ITEM_AMMO_BULLET) sprintf_s(str, "%s%s\n", str, "Ammo");
		else if (_viewItem->getItemType() <= ITEM_BLOCK_PLATFORM) sprintf_s(str, "%s%s\n", str, "Block");
		else if (_viewItem->getItemType() <= ITEM_MATERIAL) sprintf_s(str, "%s%s\n", str, "Material");

		if (_viewItem->getAbillity().attack > 0) sprintf_s(str, "%sattack : %.0f\n", str, _viewItem->getAbillity().attack);
		if (_viewItem->getAbillity().defense > 0) sprintf_s(str, "%sdefense : %.0f\n", str, _viewItem->getAbillity().defense);
		if (_viewItem->getAbillity().HP > 0) sprintf_s(str, "%sHP : %.0f\n", str, _viewItem->getAbillity().HP);
		if (_viewItem->getAbillity().MP > 0) sprintf_s(str, "%sMP : %.0f\n", str, _viewItem->getAbillity().MP);
		if (_viewItem->getAbillity().shootNum > 0) sprintf_s(str, "%sshooting num : %d\n", str, _viewItem->getAbillity().shootNum);
		if (_viewItem->getAbillity().mana > 0) sprintf_s(str, "%smana : %d\n", str, _viewItem->getAbillity().mana);
		if (_viewItem->getAbillity().doubleJump == true) sprintf_s(str, "%s%s\n", str, "can double jump");
		if (_viewItem->getAbillity().fastRun) sprintf_s(str, "%s%s\n", str, "can fast run");
		if (_viewItem->getAbillity().fly) sprintf_s(str, "%s%s\n", str, "can fly");

		int textColorValue = 255 - abs(sin(TIMEMANAGER->getWorldTime()) * 80);
		HFONT f = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "HW Andy"), of = (HFONT)SelectObject(hdc, f);
		COLORREF oc = SetTextColor(hdc, RGB(textColorValue, textColorValue, textColorValue));
		DrawText(hdc, str, 200, &rc, 0);
		SetTextColor(hdc, oc);
		SelectObject(hdc, of);
		DeleteObject(f);
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
				//둘다 있는데 같은건데 맥스 갯수가 아니면
				else if (_selectItem != NULL && 
					_inven->getItemInfo(i)->getName() == _selectItem->getName() && 
					!_inven->getItemInfo(i)->isMaxAmount())
				{
					_inven->getItemInfo(i)->addAmount(_selectItem->getAmount());
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

		//인벤을 클릭했을때
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
				return;
			}
		}

		//장착 장비를 클릭했을때
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
				return;
			}
		}

		//조합대 클릭
		Item* temp = _combineUI->getCombineItem();
		if (_selectItem == NULL)
		{
			_selectItem = temp;
			return;
		}
		else if (temp != NULL && _selectItem->getName() == temp->getName())
		{
			_selectItem->addAmount(temp->getAmount());
			return;
		}

		//밖을 클릭했을때 - 드랍
		if (_selectItem != NULL)
		{
			float x = (_player->getView() == LEFT) ? -METER_TO_PIXEL * 1.5 : METER_TO_PIXEL * 1.5;
			float speed = x * 10;
			float angle = (_player->getView() == LEFT) ? M_PI : 0;
			_dm->createDroppedItem(_selectItem->getName(), _selectItem->getAmount(), _player->getX() + x, _player->getY(), speed, angle);
			_selectItem = NULL;
			_player->setSelectItem(NULL);
		}
	}
}

/*
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

if (_map->getTile(x, y)->getDarkDepth() > 3)
{
SetPixel(hdc, _option.width() - 120 + i, 120 + j, RGB(0, 0, 0));
continue;
}

switch (_map->getTile(x, y)->getType())
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
*/