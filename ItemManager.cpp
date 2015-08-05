#include "stdafx.h"
#include "ItemManager.h"

namespace Terraria
{
	ItemManager::ItemManager()
	{
	}


	ItemManager::~ItemManager()
	{
	}

	HRESULT ItemManager::initialize()
	{
		return S_OK;
	}
	void ItemManager::release()
	{
		for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
		{
			SAFE_RELEASE(*_viItem);
		}

		_vItem.clear();
	}

	Item* ItemManager::createItem(std::string itemName, int amount)
	{
		Item* item = NULL;

		Row* row = DATABASE->get("item", itemName);

		if (row == NULL) return NULL;

		string imageName = row->find("image")->second;
		string spriteImageName = row->find("spriteimage")->second;
		ITEM_TYPE itemType = (ITEM_TYPE)atoi(row->find("itemtype")->second.c_str());
		EQUIPMENT_TYPE equipType = (EQUIPMENT_TYPE)atoi(row->find("equiptype")->second.c_str());
		int maxAmount = atoi(row->find("maxamount")->second.c_str());
		int hp = atoi(row->find("hp")->second.c_str());
		int mp = atoi(row->find("mp")->second.c_str());
		int attack = atoi(row->find("attack")->second.c_str());
		int defense = atoi(row->find("defense")->second.c_str());
		int atkSpeed = atoi(row->find("atkspeed")->second.c_str());
		int shootNum = atoi(row->find("shootnum")->second.c_str());

		item = new Item;
		item->initialize(itemName, imageName, spriteImageName, itemType, equipType, maxAmount, hp, mp, attack, defense, atkSpeed, shootNum);
		item->addAmount(amount);

		_vItem.push_back(item);

		return item;
	}

	string ItemManager::getImageName(string itemName)
	{
		Row* row = DATABASE->get("item", itemName);

		if (row == NULL) return "";

		return row->find("image")->second;
	}

	int ItemManager::getMaxAmount(string itemName)
	{
		Row* row = DATABASE->get("item", itemName);

		if (row == NULL) return 0;

		return atoi(row->find("maxamount")->second.c_str());
	}

	void ItemManager::inputItemInfo()
	{
		if (!DATABASE->isExistTable("item")) DATABASE->addTable("item");

		addItemInfo("body test", "body 46 image", "body 46", ITEM_EQUIP, EQUIP_TOP, 1, 10, 0, 0, 10);
		addItemInfo("pant test", "pant 46 image", "pant 46", ITEM_EQUIP, EQUIP_PANT, 1, 10, 0, 0, 10);

		addItemInfo("pickaxe", "pickaxe basic", "pickaxe basic", ITEM_TOOL_PICKAXE, EQUIP_NONE, 1, 0, 0, 0, 0, 250);

		addItemInfo("tile grass", "item tile grass", "item tile grass", ITEM_BLOCK_GRASS, EQUIP_NONE, 999, 0, 0, 0, 0);
		addItemInfo("tile stone", "item tile stone", "item tile stone", ITEM_BLOCK_STONE, EQUIP_NONE, 999, 0, 0, 0, 0);
		addItemInfo("tile silver", "item tile silver", "item tile silver", ITEM_BLOCK_SILVER, EQUIP_NONE, 999, 0, 0, 0, 0);
		addItemInfo("tile gold", "item tile gold", "item tile gold", ITEM_BLOCK_GOLD, EQUIP_NONE, 999, 0, 0, 0, 0);

		addItemInfo("body silver", "body silver image", "body silver", ITEM_EQUIP, EQUIP_TOP, 1, 10, 10, 0, 5);
		addItemInfo("helmet silver", "helmet silver image", "helmet silver", ITEM_EQUIP, EQUIP_HELMET, 1, 10, 20, 0, 5);
		addItemInfo("pant silver", "pant silver image", "pant silver", ITEM_EQUIP, EQUIP_PANT, 1, 10, 10, 0, 5);

		addItemInfo("body gold", "body gold image", "body gold", ITEM_EQUIP, EQUIP_TOP, 1, 20, 20, 0, 10);
		addItemInfo("helmet gold", "helmet gold image", "helmet gold", ITEM_EQUIP, EQUIP_HELMET, 1, 20, 20, 0, 10);
		addItemInfo("pant gold", "pant gold image", "pant gold", ITEM_EQUIP, EQUIP_PANT, 1, 20, 20, 0, 10);

		addItemInfo("body costume", "body costume image", "body costume", ITEM_EQUIP, EQUIP_TOP, 1, 0, 0, 0, 0);

		addItemInfo("sword basic", "sword basic", "sword basic", ITEM_WEAPON_SWORD, EQUIP_NONE, 1, 0, 0, 20, 0, 100);
		addItemInfo("bow basic", "bow basic", "bow basic", ITEM_WEAPON_BOW, EQUIP_NONE, 1, 0, 0, 10, 0, 200, 1);
		addItemInfo("gun basic", "gun basic", "gun basic", ITEM_WEAPON_GUN, EQUIP_NONE, 1, 0, 0, 10, 0, 80, 1);
		addItemInfo("magic basic", "magic basic", "magic basic", ITEM_WEAPON_MAGIC, EQUIP_NONE, 1, 0, 0, 12, 0, 200);

		addItemInfo("arrow", "arrow", "arrow image", ITEM_AMMO_ARROW, EQUIP_NONE, 999, 0, 0, 10, 0, 0);
		addItemInfo("bullet", "bullet", "bullet image", ITEM_AMMO_BULLET, EQUIP_NONE, 999, 0, 0, 8, 0, 0);

		DATAMANAGER->saveDatabase("item", RESOURCE("/data/item.ini"));
	}

	void ItemManager::addItemInfo(
		string name, string image, string spriteImage, ITEM_TYPE item, EQUIPMENT_TYPE equip, 
		int max, int hp, int mp, int atk, int def, float atkSpeed, int shootNum)
	{
		Row row;
		
		row.insert(make_pair("key", name));
		row.insert(make_pair("image", image));
		row.insert(make_pair("spriteimage", spriteImage));
		row.insert(make_pair("itemtype", to_string(item)));
		row.insert(make_pair("equiptype", to_string(equip)));
		row.insert(make_pair("maxamount", to_string(max)));
		row.insert(make_pair("hp", to_string(hp)));
		row.insert(make_pair("mp", to_string(mp)));
		row.insert(make_pair("attack", to_string(atk)));
		row.insert(make_pair("defense", to_string(def)));
		row.insert(make_pair("atkspeed", to_string(atkSpeed)));
		row.insert(make_pair("shootnum", to_string(shootNum)));

		if (DATABASE->get("item", name) == NULL)
		{
			DATABASE->add("item", name, row);
		}
		else
		{
			DATABASE->modify("item", name, row);
		}
	}
}
