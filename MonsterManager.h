#pragma once
#include <vector>
#include "TerrariaNode.h"
#include "TerrariaUnit.h"
#include "Zombie.h"

namespace Terraria
{
	typedef std::vector<Unit*> vUnit;
	typedef vUnit::iterator viUnit;

	class Player;
	class MonsterManager : public Node
	{
	private:
		vUnit _vMonster;

		Player* _player;
	public:
		HRESULT initialize(Player* player);
		void release();
		void update();
		void render(HDC hdc);

		inline vUnit* getMonsters(){ return &_vMonster; }

		void createZombie(float x, float y);

		MonsterManager();
		virtual ~MonsterManager();
	};
}