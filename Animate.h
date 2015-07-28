#pragma once

#include <vector>

typedef void(*CALLBACK_FUNC)(void);
typedef void(*CALLBACK_FUNC_PARAMETER)(void*);

class Animate
{
public:
	typedef std::vector<POINT> _vFrameList;		//프레임의 좌표 리스트...
	typedef std::vector<int> _vPlayList;		//플레이 인덱스 리스트..

private:
	int _frameNum;			//프레임 수

	_vFrameList _frameList;	//프레임의 좌표 벡터
	_vPlayList _playList;	//플레이 인덱스 벡터

	int _frameWidth;		//프레임 가로 크기
	int _frameHeight;		//프레임 세로 크기

	BOOL _isLoop;				//뺑뺑이냐?
	float _frameUpdateSec;	//초당 프레임 업데이트
	float _elapsedSec;		//프레임당 경과 시간

	DWORD _nowPlayIndex;	//현재 프레임 인덱스
	BOOL _isPlay;			//지금 플레이 중이냐?

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


	void start(void);		//플레이 시작~
	void stop(void);		//정지
	void pause(void);		//일시 정지
	void resume(void);		//이어서 시작

	//뻉뻉이냐?
	inline BOOL isPlay(void) { return _isPlay; }

	//프레임 위치를 얻어온당
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIndex]]; }

	//프레임 가로 크기 얻어온다
	inline int getFrameWidth(void) { return _frameWidth; }

	//프레임 세로 크기 얻어온다
	inline int getFrameHeight(void) { return _frameHeight; }
public:
	Animate();
	virtual ~Animate();
};

