#pragma once

namespace Terraria
{
	class Item : public Node
	{
	private:
		EquipType _equipType;
		ItemType _itemType;

		Image* _image;
		Image* _equipImage;
		SpriteImage* _spriteImage;

		ItemAbillity _abillity;
	public:
		HRESULT initialize(string imageName, string spriteImageName, EQUIPMENT_TYPE type = EQUIP_NONE);
		HRESULT initialize(string imageName, string spriteImageName, ITEM_TYPE type = ITEM_NONE);
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

		Item();
		virtual ~Item();
	};
}

