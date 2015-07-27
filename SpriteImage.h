#pragma once
#include "Image.h"
#include "TimeManager.h"

class Image;
class SpriteImage
{
private:
	Image* _image;

	float _centerX;
	float _centerY;

	int _currentFrameCol;
	int _currentFrameRow;
	int _maxFrameCol;
	int _maxFrameRow;
	int _frameWidth;
	int _frameHeight;

	int _frameNum;

	float _time = 0;
	CheckTimer* _timer;

	RECT _imageScale;

	void setBoundingBox()
	{
		_imageScale = makeRectCenter(_centerX, _centerY, _frameWidth, _frameHeight);
	}
public:
	SpriteImage();
	virtual ~SpriteImage();

	//������ ����
	//�� ���̿� �࿭ ����
	HRESULT initialize(Image* image, int frameColumn, int frameRow, int frameX = 0, int frameY = 0);
	HRESULT initialize(Image* image, float centerX, float centerY, int frameColumn, int frameRow, int frameX = 0, int frameY = 0);

	//������ ����
	virtual void render(HDC hdc, BYTE alpha = 255);
	virtual void render(HDC hdc, float destX, float destY, BYTE alpha = 255);

	virtual void release();
	
	//getter setter
	void setImage(Image* image){ _image = image; }
	Image* getImage(){ return _image; }

	RECT getRect(){ setBoundingBox(); return _imageScale; }

	inline void setFrameX(int frameX)
	{
		if (frameX > _maxFrameCol) _currentFrameCol = _maxFrameCol;
		else if (frameX < 0) _currentFrameCol = 0;
		else _currentFrameCol = frameX;
	}
	inline void setFrameY(int frameY)
	{
		if (frameY > _maxFrameRow) _currentFrameRow = _maxFrameRow;
		else if (frameY < 0) _currentFrameRow = 0;
		else _currentFrameRow = frameY;
	}
	inline void setFrame(int x, int y){ setFrameX(x); setFrameY(y); }
	inline void setCenter(float x, float y){ _centerX = x; _centerY = y; }
	inline void setX(float x){ _centerX = x; }
	inline void setY(float y){ _centerY = y; }

	inline POINT getCenter(){ return POINT{ _centerX, _centerY }; }
	inline float getX(){ return _centerX; }
	inline float getY(){ return _centerY; }

	inline int getMaxFrameX(){ return _maxFrameCol; }
	inline int getMaxFrameY(){ return _maxFrameRow; }

	inline int getFrameX(){ return _currentFrameCol; }
	inline int getFrameY(){ return _currentFrameRow; }

	inline int getFrameWidth(){ return _frameWidth; }
	inline int getFrameHeight(){ return _frameHeight; }

	//frame move
	void nextFrameX();
	void nextFrameY();
	void prevFrameX();
	void prevFrameY();

	void nextFrame();
	void prevFrame();

	void nextFrameX(float mSecond);
	void nextFrameY(float mSecond);
	void prevFrameX(float mSecond);
	void prevFrameY(float mSecond);

	void nextFrame(float mSecond);
	void prevFrame(float mSecond);
};

