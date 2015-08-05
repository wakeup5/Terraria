#include "stdafx.h"
#include "Animate.h"


Animate::Animate(void)
	: _frameWidth(0),
	_frameHeight(0),
	_isLoop(FALSE),
	_frameUpdateSec(0),
	_elapsedSec(0),
	_nowPlayIndex(0),
	_isPlay(FALSE)
{
}

Animate::~Animate(void)
{
}

HRESULT Animate::init(int totalW, int totalH, int frameW, int frameH)
{
	//프레임 가로 갯수
	_frameWidth = frameW;
	int frameNumWidth = totalW / _frameWidth;

	//프레임 세로 갯수
	_frameHeight = frameH;
	int frameNumHeight = totalH / _frameHeight;

	//총 프레임 수 계산..
	_frameNum = frameNumWidth * frameNumHeight;

	//프레임 위치 리스트 셋팅한당~~
	_frameList.clear();
	for (int i = 0; i < frameNumHeight; i++)
	{
		for (int j = 0; j < frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//프레임 좌표 리스트에 추가
			_frameList.push_back(framePos);
		}
	}

	//기본 프레임으로 셋팅~
	setDefPlayFrame();

	return S_OK;
}

//기본 플레이 셋팅
void Animate::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	//뺑뺑이 여부 대입
	_isLoop = loop;

	//플레이 리스트 벡터 클리어
	_playList.clear();

	//왔다갔다 애니메이션..
	if (reverse)
	{
		//뺑뺑이 애니메이션이면...
		if (_isLoop)
		{
			//갈때 프레임..
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//올때 프레임
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//갈때 프레임..
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//올때 프레임
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	//다시 되돌아 오는 애니메이션이 아니면...
	else
	{
		//갈때 프레임..
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

void Animate::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNC cbFunction)
{
	//콜백
	_callbackFunction = static_cast<CALLBACK_FUNC>(cbFunction);
	_callbackFunctionParameter = NULL;
	_obj = NULL;

	setDefPlayFrame(reverse, loop);
}

void Animate::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj)
{
	//콜백
	_callbackFunctionParameter = static_cast<CALLBACK_FUNC_PARAMETER>(cbFunction);
	_callbackFunction = NULL;
	_obj = obj;

	setDefPlayFrame(reverse, loop);
}

void Animate::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	//뻉뺑이냐?
	_isLoop = loop;

	_frameNum = arrLen;

	//플레이 리스트 벡터 클리어
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

void Animate::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNC cbFunction)
{
	//콜백
	_callbackFunction = static_cast<CALLBACK_FUNC>(cbFunction);
	_callbackFunctionParameter = NULL;
	_obj = NULL;

	setPlayFrame(playArr, arrLen, loop);
}

void Animate::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj)
{
	//콜백
	_callbackFunctionParameter = static_cast<CALLBACK_FUNC_PARAMETER>(cbFunction);
	_callbackFunction = NULL;
	_obj = obj;

	setPlayFrame(playArr, arrLen, loop);
}

void Animate::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	//뺑뺑이냐?
	_isLoop = loop;

	//플레이 리스트 벡터 클리어
	_playList.clear();

	if (start == end)
	{
		_playList.clear();
		_playList.push_back(start);
		return;
	}

	//시작 프레임이 종료 프레임보다 클 경우
	if (start > end)
	{
		//다시 되돌아 오냐?
		if (reverse)
		{
			//뺑뺑이냐?
			if (_isLoop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i >= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	//시작 프레임이 종료 프레임보다 작을 경우
	else
	{
		//다시 되돌아 오냐?
		if (reverse)
		{
			//뺑뺑이냐?
			if (_isLoop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}
				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}
				for (int i = end - 1; i >= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

void Animate::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNC cbFunction)
{
	//콜백
	_callbackFunction = static_cast<CALLBACK_FUNC>(cbFunction);
	_callbackFunctionParameter = NULL;
	_obj = NULL;

	setPlayFrame(start, end, reverse, loop);
}

void Animate::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj)
{
	//콜백
	_callbackFunctionParameter = static_cast<CALLBACK_FUNC_PARAMETER>(cbFunction);
	_callbackFunction = NULL;
	_obj = obj;

	setPlayFrame(start, end, reverse, loop, cbFunction, obj);
}

void Animate::release(void)
{

}

//초당 프레임 갱신 횟수~~~
void Animate::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

//프레임 업데이트~
void Animate::frameUpdate(float elapsedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elapsedTime;

		//프레임 업데이트 시간이 되었으면...
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIndex++;
			//끝까지 같으면..
			if (_nowPlayIndex == _playList.size())
			{
				//뺑뺑이냐?
				if (_isLoop)
				{
					_nowPlayIndex = 0;
				}
				else
				{
					if (_obj == NULL)
					{
						if (_callbackFunction != NULL) _callbackFunction();
					}
					else
					{
						if (_callbackFunctionParameter != NULL)
						{
							_callbackFunctionParameter(_obj);
						}
					}

					_nowPlayIndex--;
					_isPlay = FALSE;
				}
			}
		}
	}
}

void Animate::start(void)		//플레이 시작~
{
	_isPlay = true;
	_nowPlayIndex = 0;
}

void Animate::stop(void)		//정지
{
	_isPlay = FALSE;
	_nowPlayIndex = 0;
}

void Animate::pause(void)		//일시 정지
{
	_isPlay = FALSE;
}

void Animate::resume(void)		//이어서 시작
{
	_isPlay = TRUE;
}
