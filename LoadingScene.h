#pragma once
#include "SceneManager.h"
class LoadingScene : public Scene
{
public:
	HRESULT initialize();
	void release();
	void update();
	void render();

	LoadingScene();
	virtual ~LoadingScene();
};

