#pragma once
class Action
{
public:
	Action();
	~Action();

	HRESULT initialize();
	void release();
	void update();
	void render();

	void moveTo(int startX, int startY, int endX, int endY, float time);
};

