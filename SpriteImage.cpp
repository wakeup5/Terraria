#include "stdafx.h"
#include "SpriteImage.h"


SpriteImage::SpriteImage()
{
	_currentFrameCol = 0;
	_currentFrameRow = 0;
	_maxFrameCol = 0;
	_maxFrameRow = 0;
	_frameWidth = 0;
	_frameHeight = 0;
}

SpriteImage::~SpriteImage()
{

}

HRESULT SpriteImage::initialize(Image* image, int frameColumn, int frameRow, int frameX, int frameY)
{
	return initialize(image, image->getX(), image->getY(), frameColumn, frameRow, frameX, frameY);
}

HRESULT SpriteImage::initialize(Image* image, float centerX, float centerY, int frameColumn, int frameRow, int frameX, int frameY)
{
	_image = image;

	_centerX = centerX;
	_centerY = centerY;

	_maxFrameCol = frameColumn - 1;
	_maxFrameRow = frameRow - 1;

	_frameWidth = _image->getWidth() / frameColumn;
	_frameHeight = _image->getHeight() / frameRow;

	_currentFrameCol = frameX;
	_currentFrameRow = frameY;

	setBoundingBox();

	_time = 0;
	//_timer = TIMEMANAGER->addTimer();

	return S_OK;
}

//ÇÁ·¹ÀÓ ·»´õ
void SpriteImage::render(HDC hdc, BYTE alpha)
{
	SpriteImage::render(hdc, _centerX - _frameWidth / 2, _centerY - _frameHeight / 2, alpha);
}

void SpriteImage::render(HDC hdc, float destX, float destY, BYTE alpha)
{
	_image->render(hdc, destX, destY, _currentFrameCol * _frameWidth, _currentFrameRow * _frameHeight, _frameWidth, _frameHeight, alpha);
}

void SpriteImage::release()
{
	_image->removeSpriteImage(this);
}

void SpriteImage::nextFrameX()
{
	if (_currentFrameCol++ >= _maxFrameCol) _currentFrameCol = 0;
}
void SpriteImage::nextFrameY()
{
	if (_currentFrameRow++ >= _maxFrameRow) _currentFrameRow = 0;
}

void SpriteImage::prevFrameX()
{
	if (_currentFrameCol-- <= 0) _currentFrameCol = _maxFrameCol;
}
void SpriteImage::prevFrameY()
{
	if (_currentFrameRow-- <= 0) _currentFrameRow = _maxFrameRow;
}

void SpriteImage::nextFrame()
{
	if (_currentFrameCol++ >= _maxFrameCol)
	{
		_currentFrameCol = 0;

		if (_currentFrameRow++ >= _maxFrameRow) _currentFrameRow = 0;
	}
}
void SpriteImage::prevFrame()
{
	if (_currentFrameCol-- <= 0)
	{
		_currentFrameCol = _maxFrameCol;

		if (_currentFrameRow-- <= 0) _currentFrameRow = _maxFrameRow;
	}
}


void SpriteImage::nextFrameX(float second)
{
	if (_time + second < TIMEMANAGER->getWorldTime())
	{
		_time = TIMEMANAGER->getWorldTime();
		nextFrameX();
	}
}
void SpriteImage::nextFrameY(float second)
{
	if (_time + second < TIMEMANAGER->getWorldTime())
	{
		_time = TIMEMANAGER->getWorldTime();
		nextFrameY();
	}
}
void SpriteImage::prevFrameX(float second)
{
	if (_time + second < TIMEMANAGER->getWorldTime())
	{
		_time = TIMEMANAGER->getWorldTime();
		prevFrameX();
	}
}
void SpriteImage::prevFrameY(float second)
{
	if (_time + second < TIMEMANAGER->getWorldTime())
	{
		_time = TIMEMANAGER->getWorldTime();
		prevFrameY();
	}
}
void SpriteImage::nextFrame(float second)
{
	if (_time + second < TIMEMANAGER->getWorldTime())
	{
		_time = TIMEMANAGER->getWorldTime();
		nextFrame();
	}
}
void SpriteImage::prevFrame(float second)
{
	if (_time + second < TIMEMANAGER->getWorldTime())
	{
		_time = TIMEMANAGER->getWorldTime();
		prevFrame();
	}
}