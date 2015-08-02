#pragma once
#include "common.h"
#include "TerrariaNode.h"

namespace Terraria
{
	class Item : public Node
	{
	private:
		std::string _itemName;

		EquipType _equipType;
		ItemType _itemType;

		Image* _image;
		Image* _equipImage;
		SpriteImage* _spriteImage;

		ItemAbillity _abillity;

		int _maxAmount;
		int _currentAmount;
	public:
		HRESULT initialize(string itemName, string imageName, string spriteImageName, EQUIPMENT_TYPE type = EQUIP_NONE);
		HRESULT initialize(string itemName, string imageName, string spriteImageName, ITEM_TYPE type = ITEM_NONE, int maxAmount = 1);
		HRESULT initialize(string itemName, string imageName, string spriteImageName, ITEM_TYPE type, EQUIPMENT_TYPE equipType, int maxAmount, int hp, int mp, int attack, int defense);
		void release();
		void imageRender(HDC hdc, float centerX, float centerY);

		void setEquipType(EQUIPMENT_TYPE type){ _equipType = type; }
		EquipType getEquipType(){ return _equipType; }

		void setItemType(ITEM_TYPE type){ _itemType = type; }
		ItemType getItemType(){ return _itemType; }

		Image* getImage(){ return _image; }
		Image* getEquipImage(){ return _equipImage; }

		void setAbillity(float hp, float mp, float attack, float defense)
		{
			_abillity.HP = hp;
			_abillity.MP = mp;
			_abillity.attack = attack;
			_abillity.defense = defense;
		}

		ItemAbillity getAbillity() { return _abillity; }

		bool isMaxAmount(){ return _maxAmount == _currentAmount; }
		bool isEmpty(){ return _currentAmount <= 0; }
		void addAmount(int amount = 1){ _currentAmount += amount; if (_currentAmount > _maxAmount) _currentAmount = _maxAmount; }
		void subAmount(int amount = 1){ _currentAmount -= amount; }
		int getAmount(){ return _currentAmount; }

		string getName(){ return _itemName; }

		Item();
		virtual ~Item();
	};
}

