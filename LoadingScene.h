#pragma once
#include "SceneManager.h"
#include "Loading.h"

class LoadingScene : public Scene
{
private:
	Loading* _loading;

	Image* _logo;
	float _offsetX;
public:
	HRESULT initialize();
	void release();
	void update();
	void render();

	void loadingImage();
	void loadingSound();

	LoadingScene();
	virtual ~LoadingScene();
};

