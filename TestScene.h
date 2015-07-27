#pragma once
#include "SceneManager.h"
#include "Physical.h"
#include "player.h"
#include "PlayerManager.h"
#include "Item.h"
#include "TileMap.h"

class TestScene :
	public Scene
{
private:
	
public:
	TestScene();
	~TestScene();

	HRESULT initialize();
	void release();
	void update();
	void render();
};

