#pragma once

#include <vector>

typedef void(*CALLBACK_FUNC)(void);
typedef void(*CALLBACK_FUNC_PARAMETER)(void*);

class Animate
{
public:
	typedef std::vector<POINT> _vFrameList;		//�������� ��ǥ ����Ʈ...
	typedef std::vector<int> _vPlayList;		//�÷��� �ε��� ����Ʈ..

private:
	int _frameNum;			//������ ��

	_vFrameList _frameList;	//�������� ��ǥ ����
	_vPlayList _playList;	//�÷��� �ε��� ����

	int _frameWidth;		//������ ���� ũ��
	int _frameHeight;		//������ ���� ũ��

	BOOL _isLoop;				//�����̳�?
	float _frameUpdateSec;	//�ʴ� ������ ������Ʈ
	float _elapsedSec;		//�����Ӵ� ��� �ð�

	DWORD _nowPlayIndex;	//���� ������ �ε���
	BOOL _isPlay;			//���� �÷��� ���̳�?

	void* _obj;

	CALLBACK_FUNC_PARAMETER _callbackFunctionParameter;
	CALLBACK_FUNC _callbackFunction;

public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	void setFPS(int framePerSec);
	void frameUpdate(float elapsedTime);

	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNC cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj);

	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNC cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj);

	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNC cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj);


	void start(void);		//�÷��� ����~
	void stop(void);		//����
	void pause(void);		//�Ͻ� ����
	void resume(void);		//�̾ ����

	//�R�R�̳�?
	inline BOOL isPlay(void) { return _isPlay; }

	//������ ��ġ�� ���´�
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIndex]]; }

	//������ ���� ũ�� ���´�
	inline int getFrameWidth(void) { return _frameWidth; }

	//������ ���� ũ�� ���´�
	inline int getFrameHeight(void) { return _frameHeight; }
public:
	Animate();
	virtual ~Animate();
};

