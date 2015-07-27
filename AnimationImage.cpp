#include "stdafx.h"
#include "AnimationImage.h"

HRESULT AnimationImage::initialize(Image* image, int frameColumn, int frameRow)
{
	return initialize(image, image->getX(), image->getY(), frameColumn, frameRow);
}
HRESULT AnimationImage::initialize(Image* image, float centerX, float centerY, int frameColumn, int frameRow)
{
	SpriteImage::initialize(image, centerX, centerY, frameColumn, frameRow);

	_frameNum = frameColumn * frameRow - 1;

	return S_OK;
}

void AnimationImage::frameUpdate(float elapsedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elapsedTime;

		//프레임 업데이트 시간이 되었으면...
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			
			int frameColByCurFrame = _frameIndex % (getMaxFrameX() + 1);
			int frameRowByCurFrame = _frameIndex / (getMaxFrameX() + 1);

			setFrameX(frameColByCurFrame);
			setFrameY(frameRowByCurFrame);
			
			//역방향 재생이 아닐때
			if (!_isReverse)
			{
				_frameIndex++;

				if (_frameIndex > _endIndex)
				{
					if (_isLoop)
					{
						_frameIndex = _startIndex;
					}
					else
					{
						_frameIndex--;
						_isPlay = false;
					}
					_repeat++;
				}
			}
			//역방향 재생일때
			else
			{
				_frameIndex--;

				if (_frameIndex <= _startIndex)
				{
					if (_isLoop)
					{
						_frameIndex = _endIndex;
					}
					else
					{
						_frameIndex++;
						_isPlay = false;
					}
					_repeat++;
				}
			}

		}
	}
}

void AnimationImage::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}
void AnimationImage::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	if (start > end)
	{
		int temp = start;
		start = end;
		end = temp;
	}

	if (start < 0) start = 0;
	if (end > _frameNum) end = _frameNum;

	_startIndex = start;
	_endIndex = end;
	_isReverse = reverse;
	_isLoop = loop;

	if (!_isReverse)
		_frameIndex = _startIndex;
	else
		_frameIndex = _endIndex;
}

void AnimationImage::start(void)
{
	_isPlay = true;
	if (!_isReverse) 
		_frameIndex = _startIndex;
	else 
		_frameIndex = _endIndex;
}
void AnimationImage::stop(void)
{
	_isPlay = false;
	if (!_isReverse)
		_frameIndex = _startIndex;
	else
		_frameIndex = _endIndex;
}
void AnimationImage::pause(void)
{
	_isPlay = true;
}
void AnimationImage::resume(void)
{
	_isPlay = false;
}