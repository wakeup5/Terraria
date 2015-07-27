#pragma once
#include "SceneManager.h"
#include "Button.h"
class MainScene :
	public Scene
{
private:
	Button* _singlePlayer;
	Button* _setting;
	Button* _exit;
	Image* _black;

	bool _startAlpha;
	int _alpha;
	float _time;

	Image* _bgSky;
	Image* _bgMountain;
	Image* _bgTree;
	float _offsetX;

	Image* _logo;

public:
	MainScene();
	~MainScene();

	HRESULT initialize();
	void release();
	void update();
	void render();

	void startBlackAlpha();
};

