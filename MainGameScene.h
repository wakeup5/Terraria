#pragma once
#include "SceneManager.h"
#include "Physical.h"
#include "player.h"
#include "PlayerManager.h"
#include "Item.h"
#include "TileMap.h"
#include "UI.h"
#include "Collision.h"

class MainGameScene : public Scene
{
private:
	Terraria::TileMap* _map;
	Terraria::PlayerManager* _pm;

	Terraria::Item* _body;
	Terraria::Item* _pant;

	Terraria::Item* _pickaxe;


	Terraria::UI* _ui;
public:
	HRESULT initialize();
	void release();
	void update();
	void render();

	MainGameScene();
	virtual ~MainGameScene();
};

