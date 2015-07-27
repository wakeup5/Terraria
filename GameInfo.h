#pragma once
class GameInfo
{
private:
	int _screenStartX;
	int _screenStartY;

	int _screenWidth;
	int _screenHeight;

	POINT _mousePoint;
	POINT _innerMousePoint;

	float _cameraX;
	float _cameraY;
public:
	GameInfo();
	~GameInfo();
	void setScreenSize(int width, int height);

	inline int width(){ return _screenWidth; }
	inline int height(){ return _screenHeight; }

	inline void setStart(int x, int y)
	{
		_screenStartX = x;
		_screenStartY = y;
	}

	inline void setSize(int width, int height)
	{
		_screenHeight = height;
		_screenWidth = width;
	}

	inline POINT mousePt(){ return _mousePoint; }
	inline long mouseX(){ return _mousePoint.x; }
	inline long mouseY(){ return _mousePoint.y; }

	inline POINT inMousePt(){ return _innerMousePoint; }
	inline long inMouseX(){ return _innerMousePoint.x; }
	inline long inMouseY(){ return _innerMousePoint.y; }

	void setMousePoint(POINT p){ _mousePoint = p; setInMousePoint(_mousePoint); }
	void setInMousePoint(POINT p);

	inline float cameraX(){ return _cameraX; }
	inline float cameraY(){ return _cameraY; }

	inline void setCamera(float x, float y){ _cameraX = x; _cameraY = y; setInMousePoint(_mousePoint); }

	void setCamera(float x, float maxX, float y, float maxY);
};

