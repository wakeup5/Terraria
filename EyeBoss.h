#pragma once
#include "TerrariaUnit.h"
#include "Player.h"
#include "TEffectManager.h"
#include "DroppedItemManager.h"

namespace Terraria
{
	class EyeBoss : public Unit
	{
	private:
		Player* _player;
		DroppedItemManager* _dm;
		Image* _image;

		float _angleByPlayer;
		float _attackTime;
	public:
		HRESULT initialize(DroppedItemManager* dm, Player* player, int hp, int atk, int def);
		void release();
		void update();
		void render(HDC hdc);

		void hit(UNIT_DIRECT direct, int atk = 0);

		EyeBoss();
		virtual ~EyeBoss();
	};
}
