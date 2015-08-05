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
	//������ ���� ����
	_frameWidth = frameW;
	int frameNumWidth = totalW / _frameWidth;

	//������ ���� ����
	_frameHeight = frameH;
	int frameNumHeight = totalH / _frameHeight;

	//�� ������ �� ���..
	_frameNum = frameNumWidth * frameNumHeight;

	//������ ��ġ ����Ʈ �����Ѵ�~~
	_frameList.clear();
	for (int i = 0; i < frameNumHeight; i++)
	{
		for (int j = 0; j < frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//������ ��ǥ ����Ʈ�� �߰�
			_frameList.push_back(framePos);
		}
	}

	//�⺻ ���������� ����~
	setDefPlayFrame();

	return S_OK;
}

//�⺻ �÷��� ����
void Animate::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	//������ ���� ����
	_isLoop = loop;

	//�÷��� ����Ʈ ���� Ŭ����
	_playList.clear();

	//�Դٰ��� �ִϸ��̼�..
	if (reverse)
	{
		//������ �ִϸ��̼��̸�...
		if (_isLoop)
		{
			//���� ������..
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//�ö� ������
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//���� ������..
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//�ö� ������
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	//�ٽ� �ǵ��� ���� �ִϸ��̼��� �ƴϸ�...
	else
	{
		//���� ������..
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

void Animate::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNC cbFunction)
{
	//�ݹ�
	_callbackFunction = static_cast<CALLBACK_FUNC>(cbFunction);
	_callbackFunctionParameter = NULL;
	_obj = NULL;

	setDefPlayFrame(reverse, loop);
}

void Animate::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj)
{
	//�ݹ�
	_callbackFunctionParameter = static_cast<CALLBACK_FUNC_PARAMETER>(cbFunction);
	_callbackFunction = NULL;
	_obj = obj;

	setDefPlayFrame(reverse, loop);
}

void Animate::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	//�R���̳�?
	_isLoop = loop;

	_frameNum = arrLen;

	//�÷��� ����Ʈ ���� Ŭ����
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

void Animate::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNC cbFunction)
{
	//�ݹ�
	_callbackFunction = static_cast<CALLBACK_FUNC>(cbFunction);
	_callbackFunctionParameter = NULL;
	_obj = NULL;

	setPlayFrame(playArr, arrLen, loop);
}

void Animate::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj)
{
	//�ݹ�
	_callbackFunctionParameter = static_cast<CALLBACK_FUNC_PARAMETER>(cbFunction);
	_callbackFunction = NULL;
	_obj = obj;

	setPlayFrame(playArr, arrLen, loop);
}

void Animate::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	//�����̳�?
	_isLoop = loop;

	//�÷��� ����Ʈ ���� Ŭ����
	_playList.clear();

	if (start == end)
	{
		_playList.clear();
		_playList.push_back(start);
		return;
	}

	//���� �������� ���� �����Ӻ��� Ŭ ���
	if (start > end)
	{
		//�ٽ� �ǵ��� ����?
		if (reverse)
		{
			//�����̳�?
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
	//���� �������� ���� �����Ӻ��� ���� ���
	else
	{
		//�ٽ� �ǵ��� ����?
		if (reverse)
		{
			//�����̳�?
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
	//�ݹ�
	_callbackFunction = static_cast<CALLBACK_FUNC>(cbFunction);
	_callbackFunctionParameter = NULL;
	_obj = NULL;

	setPlayFrame(start, end, reverse, loop);
}

void Animate::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj)
{
	//�ݹ�
	_callbackFunctionParameter = static_cast<CALLBACK_FUNC_PARAMETER>(cbFunction);
	_callbackFunction = NULL;
	_obj = obj;

	setPlayFrame(start, end, reverse, loop, cbFunction, obj);
}

void Animate::release(void)
{

}

//�ʴ� ������ ���� Ƚ��~~~
void Animate::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

//������ ������Ʈ~
void Animate::frameUpdate(float elapsedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elapsedTime;

		//������ ������Ʈ �ð��� �Ǿ�����...
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIndex++;
			//������ ������..
			if (_nowPlayIndex == _playList.size())
			{
				//�����̳�?
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

void Animate::start(void)		//�÷��� ����~
{
	_isPlay = true;
	_nowPlayIndex = 0;
}

void Animate::stop(void)		//����
{
	_isPlay = FALSE;
	_nowPlayIndex = 0;
}

void Animate::pause(void)		//�Ͻ� ����
{
	_isPlay = FALSE;
}

void Animate::resume(void)		//�̾ ����
{
	_isPlay = TRUE;
}
