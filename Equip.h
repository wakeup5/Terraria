#pragma once
#include "TerrariaObject.h"
#include "Equipment.h"

namespace Terraria
{
	class Equip : public Node
	{
	private:
		Equipment* _equipment[EQUIP_NONE];

	public:
		HRESULT initialize();
		void release();
		void update();
		void render(HDC hdc);

		const ItemAbillity getTotalAbillity();

		bool dress(Item* item);
		bool undress(EQUIPMENT_TYPE type, Item** result = NULL);
		bool swap(Item* item, Item** result);

		bool isEquipped(EQUIPMENT_TYPE type);

		void setImageFrame(EQUIPMENT_TYPE type, int frameX, int frameY);
		void setImageFrameX(EQUIPMENT_TYPE type, int frameX);
		void setImageFrameY(EQUIPMENT_TYPE type, int frameY);
		SpriteImage* const getSpriteImage(EQUIPMENT_TYPE type);

		void setCenter(float x, float y);

		Item* const getItem(EQUIPMENT_TYPE type);

		Equip();
		virtual ~Equip();
	};
}

