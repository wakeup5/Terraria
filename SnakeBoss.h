#pragma once
#include "TerrariaUnit.h"
#include "Player.h"

namespace Terraria
{
	enum PIECE
	{
		HEAD, BODY, TAIL
	};
	class SnakePiece;
	class SnakeBoss;
	class TileMap;
	class DroppedItemManager;

	class SnakePiece : public Unit
	{
	private:
		SnakeBoss* _self;
		Image* _image;
	public:
		HRESULT initialize(SnakeBoss* self, PIECE p);
		void release();
		void update();
		void render(HDC hdc);

		virtual void hit(UNIT_DIRECT direct, int atk = 0);

		SnakePiece();
		virtual ~SnakePiece();
	};

	class SnakeBoss : public Unit
	{
	private:
		const int LENGTH = 100;

		SnakePiece* _pieces[100];

		TileMap* _tileMap;
		Player* _player;
		DroppedItemManager* _dm;
	public:
		HRESULT initialize(DroppedItemManager* dm, TileMap* tileMap, Player* _player, float x, float y);
		void release();
		void update();
		void render(HDC hdc);

		void addMonsterList(vector<Unit*>* units);

		bool tileCollision();

		SnakeBoss();
		virtual ~SnakeBoss();
	};
}
