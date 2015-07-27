#pragma once
#include "GameNode.h"

class Button :
	public GameNode
{
private:
	typedef void(*CallbackFunc)(void);

	enum BUTTON_STATE
	{
		BUTTON_DOWN_START,
		BUTTON_DOWN,
		BUTTON_UP_START,
		BUTTON_UP,
		BUTTON_BLOCKED,
		BUTTON_NONE
	};

	SpriteImage* _image;
	BUTTON_STATE _state;

	CallbackFunc _downCallback;
	CallbackFunc _downStartCallback;
	CallbackFunc _upCallback;
	CallbackFunc _upStartCallback;

	float _x, _y;

public:
	Button();
	~Button();

	//HRESULT initialize(Image* image, float x, float y, CallbackFunc callback = NULL);
	HRESULT initialize(Image* image, float x, float y);
	void release();
	void update();
	void render();

	void setCenter(float x, float y){ _x = x; _y = y; }

	void blocked(bool);

	void onCLickDown(CallbackFunc callback){ _downCallback = callback; }
	//void onCLickDownStart(CallbackFunc callback){ _downStartCallback = callback; }
	void onCLickUp(CallbackFunc callback){ _upCallback = callback; }
	//void onCLickUpStart(CallbackFunc callback){ _upStartCallback = callback; }
};

