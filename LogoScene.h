#pragma once
#include "SceneManager.h"
class LogoScene :
	public Scene
{
private:
	enum LOGO_STATE
	{
		LOGO_STATE_START,
		LOGO_STATE_VIEW,
		LOGO_STATE_END
	};
	Image* _logo;
	Image* _logoBlack;

	int _alpha;
	LOGO_STATE _state;
	float _time;

public:
	LogoScene();
	~LogoScene();

	HRESULT initialize();
	void release();
	void update();
	void render();
};

