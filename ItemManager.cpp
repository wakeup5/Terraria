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
		for (int i = 0; i < _vItem.size(); i++)
		{
			SAFE_RELEASE(_vItem[i]);
		}

		_vItem.clear();
	}

	void ItemManager::update()
	{
		for (int i = 0; i < _vItem.size(); i++)
		{
			if (_vItem[i]->isDelete())
			{
				SAFE_RELEASE(_vItem[i]);
				_vItem.erase(_vItem.begin() + i);
				i--;
			}
		}
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
		int mana = atoi(row->find("mana")->second.c_str());
		bool doubleJump = atoi(row->find("doublejump")->second.c_str());
		bool fastRun = atoi(row->find("fastrun")->second.c_str());
		bool fly = atoi(row->find("fly")->second.c_str());

		item = new Item;
		item->initialize(itemName, imageName, spriteImageName, itemType, equipType, maxAmount, hp, mp, attack, defense, atkSpeed, shootNum, mana, doubleJump, fastRun, fly);
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

		//도구
		addItemInfo("pickaxe", "pickaxe basic", "pickaxe basic", ITEM_TOOL_PICKAXE, EQUIP_NONE, 1, 0, 0, 0, 0, 250);

		//타일
		addItemInfo("tile grass", "item tile grass", "item tile grass", ITEM_BLOCK_GRASS, EQUIP_NONE, 999, 0, 0, 0, 0);
		addItemInfo("tile stone", "item tile stone", "item tile stone", ITEM_BLOCK_STONE, EQUIP_NONE, 999, 0, 0, 0, 0);
		addItemInfo("tile silver", "item tile silver", "item tile silver", ITEM_BLOCK_SILVER, EQUIP_NONE, 999, 0, 0, 0, 0);
		addItemInfo("tile gold", "item tile gold", "item tile gold", ITEM_BLOCK_GOLD, EQUIP_NONE, 999, 0, 0, 0, 0);

		//방어구
		//방어구 - 실버
		addItemInfo("helmet silver", "helmet silver image", "helmet silver", ITEM_EQUIP, EQUIP_HELMET, 1, 20, 20, 0, 2);
		addItemInfo("body silver", "body silver image", "body silver", ITEM_EQUIP, EQUIP_TOP, 1, 10, 0, 0, 1);
		addItemInfo("pant silver", "pant silver image", "pant silver", ITEM_EQUIP, EQUIP_PANT, 1, 10, 0, 0, 1);

		//방어구 - 골드
		addItemInfo("helmet gold", "helmet gold image", "helmet gold", ITEM_EQUIP, EQUIP_HELMET, 1, 50, 50, 0, 3);
		addItemInfo("body gold", "body gold image", "body gold", ITEM_EQUIP, EQUIP_TOP, 1, 20, 0, 0, 2);
		addItemInfo("pant gold", "pant gold image", "pant gold", ITEM_EQUIP, EQUIP_PANT, 1, 20, 0, 0, 2);

		//방어구 - 코발트
		addItemInfo("helmet cobalt magician", "head cobalt magic image", "head cobalt magic", ITEM_EQUIP, EQUIP_HELMET, 1, 20, 80, 0, 2);
		addItemInfo("helmet cobalt ranger", "head cobalt shooter image", "head cobalt shooter", ITEM_EQUIP, EQUIP_HELMET, 1, 20, 0, 0, 3);
		addItemInfo("helmet cobalt warrior", "head cobalt warrior image", "head cobalt warrior", ITEM_EQUIP, EQUIP_HELMET, 1, 80, 0, 0, 5);

		addItemInfo("body cobalt", "body cobalt image", "body cobalt", ITEM_EQUIP, EQUIP_TOP, 1, 50, 0, 0, 5);

		addItemInfo("pant cobalt", "pant cobalt image", "pant cobalt", ITEM_EQUIP, EQUIP_PANT, 1, 30, 0, 0, 3);

		//방어구 - 미스릴
		addItemInfo("helmet mythril magician", "head mythril magic image", "head mythril magic", ITEM_EQUIP, EQUIP_HELMET, 1, 20, 100, 0, 4);
		addItemInfo("helmet mythril ranger", "head mythril shooter image", "head mythril shooter", ITEM_EQUIP, EQUIP_HELMET, 1, 20, 0, 0, 5);
		addItemInfo("helmet mythril warrior", "head mythril warrior image", "head mythril warrior", ITEM_EQUIP, EQUIP_HELMET, 1, 20, 0, 0, 10);

		addItemInfo("body mythril", "body mythril image", "body mythril", ITEM_EQUIP, EQUIP_TOP, 1, 100, 0, 0, 10);

		addItemInfo("pant mythril", "pant mythril image", "pant mythril", ITEM_EQUIP, EQUIP_PANT, 1, 50, 0, 0, 5);

		//방어구 - 블러드
		addItemInfo("helmet blood magician", "head blood magic image", "head blood magic", ITEM_EQUIP, EQUIP_HELMET, 1, 20, 150, 0, 10);
		addItemInfo("helmet blood ranger", "head blood shooter image", "head blood shooter", ITEM_EQUIP, EQUIP_HELMET, 1, 20, 0, 0, 14);
		addItemInfo("helmet blood warrior", "head blood warrior image", "head blood warrior", ITEM_EQUIP, EQUIP_HELMET, 1, 20, 0, 0, 20);

		addItemInfo("body blood", "body blood image", "body blood", ITEM_EQUIP, EQUIP_TOP, 1, 150, 0, 0, 20);

		addItemInfo("pant blood", "pant blood image", "pant blood", ITEM_EQUIP, EQUIP_PANT, 1, 100, 0, 0, 10);

		//방어구 - 코스튬
		addItemInfo("body test", "body 46 image", "body 46", ITEM_EQUIP, EQUIP_TOP, 1, 10, 0, 0, 10);
		addItemInfo("pant test", "pant 46 image", "pant 46", ITEM_EQUIP, EQUIP_PANT, 1, 10, 0, 0, 10);
		addItemInfo("body costume", "body costume image", "body costume", ITEM_EQUIP, EQUIP_TOP, 1, 0, 0, 0, 0);

		//무기
		addItemInfo("bow basic", "bow basic", "bow basic", ITEM_WEAPON_BOW, EQUIP_NONE, 1, 0, 0, 10, 0, 200, 1);
		addItemInfo("sword basic", "sword basic", "sword basic", ITEM_WEAPON_SWORD, EQUIP_NONE, 1, 0, 0, 20, 0, 250);
		addItemInfo("magic basic", "magic basic", "magic basic", ITEM_WEAPON_MAGIC, EQUIP_NONE, 1, 0, 0, 12, 0, 200);

		//무기 - 실버
		addItemInfo("bow silver", "bow silver", "bow silver", ITEM_WEAPON_BOW, EQUIP_NONE, 1, 0, 0, 15, 0, 190, 1);
		addItemInfo("sword silver", "sword silver", "sword silver", ITEM_WEAPON_SWORD, EQUIP_NONE, 1, 0, 0, 30, 0, 240);
		addItemInfo("gun I", "gun basic", "gun basic", ITEM_WEAPON_GUN, EQUIP_NONE, 1, 0, 0, 15, 0, 150, 1);
		addItemInfo("magic silver", "magic silver", "magic silver", ITEM_WEAPON_MAGIC, EQUIP_NONE, 1, 0, 0, 12, 0, 200, 0, 3);
		//무기 - 골드
		addItemInfo("bow gold", "bow gold", "bow gold", ITEM_WEAPON_BOW, EQUIP_NONE, 1, 0, 0, 15, 0, 180, 2);
		addItemInfo("sword gold", "sword gold", "sword gold", ITEM_WEAPON_SWORD, EQUIP_NONE, 1, 0, 0, 40, 0, 230);
		addItemInfo("gun II", "gun basic", "gun basic", ITEM_WEAPON_GUN, EQUIP_NONE, 1, 0, 0, 25, 0, 135, 1);
		addItemInfo("magic gold", "magic gold", "magic gold", ITEM_WEAPON_MAGIC, EQUIP_NONE, 1, 0, 0, 12, 0, 200, 0, 5);
		//무기 - 코발트
		addItemInfo("bow cobalt", "bow cobalt", "bow cobalt", ITEM_WEAPON_BOW, EQUIP_NONE, 1, 0, 0, 20, 0, 170, 2);
		addItemInfo("sword cobalt", "sword cobalt", "sword cobalt", ITEM_WEAPON_SWORD, EQUIP_NONE, 1, 0, 0, 50, 0, 220);
		addItemInfo("gun III", "gun basic", "gun basic", ITEM_WEAPON_GUN, EQUIP_NONE, 1, 0, 0, 35, 0, 110, 1);
		addItemInfo("magic cobalt", "magic cobalt", "magic cobalt", ITEM_WEAPON_MAGIC, EQUIP_NONE, 1, 0, 0, 12, 0, 200, 0, 10);
		//무기 - 미스릴
		addItemInfo("bow mythril", "bow mythril", "bow mythril", ITEM_WEAPON_BOW, EQUIP_NONE, 1, 0, 0, 25, 0, 160, 3);
		addItemInfo("sword mythril", "sword mythril", "sword mythril", ITEM_WEAPON_SWORD, EQUIP_NONE, 1, 0, 0, 60, 0, 210);
		addItemInfo("gun IV", "gun basic", "gun basic", ITEM_WEAPON_GUN, EQUIP_NONE, 1, 0, 0, 45, 0, 95, 1);
		addItemInfo("magic mythril", "magic mythril", "magic mythril", ITEM_WEAPON_MAGIC, EQUIP_NONE, 1, 0, 0, 12, 0, 200, 0, 20);
		//무기 - 블러드
		addItemInfo("bow luna", "bow luna", "bow luna", ITEM_WEAPON_BOW, EQUIP_NONE, 1, 0, 0, 30, 0, 150, 4);
		addItemInfo("sword luna", "sword luna", "sword luna", ITEM_WEAPON_SWORD, EQUIP_NONE, 1, 0, 0, 70, 0, 200);
		addItemInfo("gun V", "gun basic", "gun basic", ITEM_WEAPON_GUN, EQUIP_NONE, 1, 0, 0, 55, 0, 80, 1);
		addItemInfo("magic luna", "magic luna", "magic luna", ITEM_WEAPON_MAGIC, EQUIP_NONE, 1, 0, 0, 12, 0, 200, 0, 35);

		//악세서리
		addItemInfo("blue baloon", "blue baloon image", "blue baloon", ITEM_EQUIP, EQUIP_ACCESSORY, 0, 0, 0, 0, 0, 250, 0, 0, true);
		addItemInfo("gray baloon", "gray baloon image", "gray baloon", ITEM_EQUIP, EQUIP_ACCESSORY, 0, 0, 0, 0, 0, 250, 0, 0, false, true);
		addItemInfo("green baloon", "green baloon image", "green baloon", ITEM_EQUIP, EQUIP_ACCESSORY, 0, 0, 0, 0, 0, 250, 0, 0, false, false, true);
		addItemInfo("purple baloon", "purple baloon image", "purple baloon", ITEM_EQUIP, EQUIP_ACCESSORY, 0, 0, 0, 0, 0, 250, 0, 0, true, true);
		addItemInfo("gold baloon", "gold baloon image", "gold baloon", ITEM_EQUIP, EQUIP_ACCESSORY, 0, 0, 0, 0, 0, 250, 0, 0, false, true, true);
		addItemInfo("master baloon", "master baloon image", "master baloon", ITEM_EQUIP, EQUIP_ACCESSORY, 0, 0, 0, 0, 0, 250, 0, 0, true, true, true);

		//탄환
		addItemInfo("arrow", "arrow", "arrow image", ITEM_AMMO_ARROW, EQUIP_NONE, 999, 0, 0, 0, 0, 0);
		addItemInfo("bullet", "bullet", "bullet image", ITEM_AMMO_BULLET, EQUIP_NONE, 999, 0, 0, 0, 0, 0);

		//잉곳
		addItemInfo("ingot silver", "ingot silver", "ingot silver", ITEM_MATERIAL, EQUIP_NONE, 999, 0, 0, 0, 0, 0);
		addItemInfo("ingot gold", "ingot gold", "ingot gold", ITEM_MATERIAL, EQUIP_NONE, 999, 0, 0, 0, 0, 0);
		addItemInfo("ingot cobalt", "ingot cobalt", "ingot cobalt", ITEM_MATERIAL, EQUIP_NONE, 999, 0, 0, 0, 0, 0);
		addItemInfo("ingot mythril", "ingot mythril", "ingot mythril", ITEM_MATERIAL, EQUIP_NONE, 999, 0, 0, 0, 0, 0);
		addItemInfo("ingot blood", "ingot blood", "ingot blood", ITEM_MATERIAL, EQUIP_NONE, 999, 0, 0, 0, 0, 0);

		DATAMANAGER->saveDatabase("item", RESOURCE("/data/item.ini"));
	}

	void ItemManager::inputCombineInfo()
	{
		if (!DATABASE->isExistTable("combine")) DATABASE->addTable("combine");

		addCombineInfo("ingot silver", 1, "tile silver", 2, "", 0);
		addCombineInfo("ingot gold", 1, "tile gold", 2, "", 0);

		//방어구
		//방어구 - 실버
		addCombineInfo("helmet silver", 1, "ingot silver", 2);
		addCombineInfo("body silver", 1, "ingot silver", 2);
		addCombineInfo("pant silver", 1, "ingot cobalt", 2);
		//방어구 - 골드
		addCombineInfo("helmet gold", 1, "helmet silver", 1, "ingot gold", 2);
		addCombineInfo("body gold", 1, "body silver", 1, "ingot gold", 2);
		addCombineInfo("pant gold", 1, "pant silver", 1, "ingot gold", 2);
		//방어구 - 코발트
		addCombineInfo("helmet cobalt magician", 1, "helmet gold", 1, "ingot cobalt", 2);
		addCombineInfo("helmet cobalt ranger", 1, "helmet gold", 1, "ingot cobalt", 2);
		addCombineInfo("helmet cobalt warrior", 1, "helmet gold", 1, "ingot cobalt", 2);

		addCombineInfo("body cobalt", 1, "body gold", 1, "ingot cobalt", 2);

		addCombineInfo("pant cobalt", 1, "pant gold", 1, "ingot cobalt", 2);
		//방어구 - 미스릴
		addCombineInfo("helmet mythril magician", 1, "helmet cobalt magician", 1, "ingot mythril", 2);
		addCombineInfo("helmet mythril ranger", 1, "helmet cobalt ranger", 1, "ingot mythril", 2);
		addCombineInfo("helmet mythril warrior", 1, "helmet cobalt warrior", 1, "ingot mythril", 2);

		addCombineInfo("body mythril", 1, "body cobalt", 1, "ingot mythril", 2);

		addCombineInfo("pant mythril", 1, "pant cobalt", 1, "ingot mythril", 2);
		//방어구 - 블러드
		addCombineInfo("helmet blood magician", 1, "helmet mythril magician", 1, "ingot blood", 2);
		addCombineInfo("helmet blood ranger", 1, "helmet mythril ranger", 1, "ingot blood", 2);
		addCombineInfo("helmet blood warrior", 1, "helmet mythril warrior", 1, "ingot blood", 2);

		addCombineInfo("body blood", 1, "body mythril", 1, "ingot blood", 2);

		addCombineInfo("pant blood", 1, "pant mythril", 1, "ingot blood", 2);

		//무기
		//소모품
		addCombineInfo("arrow", 10, "tile stone", 1);
		addCombineInfo("bullet", 10, "tile stone", 1);
		//무기 - 실버
		addCombineInfo("bow silver", 1, "ingot silver", 2, "bow basic", 1);
		addCombineInfo("sword silver", 1, "ingot silver", 2, "sword basic", 1);
		addCombineInfo("gun I", 1, "ingot silver", 2);
		addCombineInfo("magic silver", 1, "ingot silver", 1);
		//무기 - 골드
		addCombineInfo("bow gold", 1, "ingot gold", 2, "bow silver", 1);
		addCombineInfo("sword gold", 1, "ingot gold", 2, "sword silver", 1);
		addCombineInfo("gun II", 1, "ingot gold", 2, "gun I", 1);
		addCombineInfo("magic gold", 1, "ingot gold", 1);
		//무기 - 코발트
		addCombineInfo("bow cobalt", 1, "ingot cobalt", 2, "bow gold", 1);
		addCombineInfo("sword cobalt", 1, "ingot cobalt", 2, "sword gold", 1);
		addCombineInfo("gun III", 1, "ingot cobalt", 2, "gun II", 1);
		addCombineInfo("magic cobalt", 1, "ingot cobalt", 1);
		//무기 - 미스릴
		addCombineInfo("bow mythril", 1, "ingot mythril", 2, "bow cobalt", 1);
		addCombineInfo("sword mythril", 1, "ingot mythril", 2, "sword cobalt", 1);
		addCombineInfo("gun IV", 1, "ingot mythril", 2, "gun III", 1);
		addCombineInfo("magic mythril", 1, "ingot mythril", 1);
		//무기 - 블러드
		addCombineInfo("bow luna", 1, "ingot blood", 2, "bow mythril", 1);
		addCombineInfo("sword luna", 1, "ingot blood", 2, "sword mythril", 1);
		addCombineInfo("gun V", 1, "ingot blood", 2, "gun IV", 1);
		addCombineInfo("magic luna", 1, "ingot blood", 1);

		//악세서리
		addCombineInfo("purple baloon", 1, "blue baloon", 1, "gray baloon", 1);
		addCombineInfo("gold baloon", 1, "green baloon", 1, "gray baloon", 1);
		addCombineInfo("master baloon", 1, "purple baloon", 1, "green baloon", 1);
		addCombineInfo("master baloon", 1, "gold baloon", 1, "blue baloon", 1);

		DATAMANAGER->saveDatabase("combine", RESOURCE("/data/combine.ini"));
	}

	void ItemManager::addItemInfo(
		string name, string image, string spriteImage, ITEM_TYPE item, EQUIPMENT_TYPE equip, 
		int max, int hp, int mp, int atk, int def, float atkSpeed, int shootNum,
		int mana, bool doubleJump, bool fastRun, bool fly)
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
		row.insert(make_pair("mana", to_string(mana)));
		row.insert(make_pair("doublejump", to_string(doubleJump)));
		row.insert(make_pair("fastrun", to_string(fastRun)));
		row.insert(make_pair("fly", to_string(fly)));

		if (DATABASE->get("item", name) == NULL)
		{
			DATABASE->add("item", name, row);
		}
		else
		{
			DATABASE->modify("item", name, row);
		}
	}
	void ItemManager::addCombineInfo(string resultName, int resultAmount, string name1, int amount1, string name2, int amount2)
	{
		Row row;

		row.insert(make_pair("key", resultName));
		row.insert(make_pair("resultname", resultName));
		row.insert(make_pair("resultamount", to_string(resultAmount)));
		row.insert(make_pair("name1", name1));
		row.insert(make_pair("amount1", to_string(amount1)));
		row.insert(make_pair("name2", name2));
		row.insert(make_pair("amount2", to_string(amount2)));

		if (DATABASE->get("combine", resultName) == NULL)
		{
			DATABASE->add("combine", resultName, row);
		}
		else
		{
			DATABASE->modify("combine", resultName, row);
		}
	}
}
