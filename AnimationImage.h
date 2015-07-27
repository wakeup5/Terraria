#pragma once
#include "SpriteImage.h"

class AnimationImage : public SpriteImage
{
private:
	int _frameNum;			// 프레임 갯수
	int _frameIndex;		// 현재 프레임 번호

	int _startIndex;		// 시작 인덱스 번호
	int _endIndex;			// 끝 인덱스 번호

	float _frameUpdateSec;	// 초당 프레임 업데이트
	float _elapsedSec;		// 프레임당 경과 시간

	int _repeat;			// 반복한 횟수

	BOOL _isLoop;			// 반복 재생인지
	BOOL _isPlay;			// 애니메이션 재생 여부
	BOOL _isReverse;		// 거꾸로 재생 하는지 여부

public:
	AnimationImage(){}
	~AnimationImage(){}

	HRESULT initialize(Image* image, int frameColumn, int frameRow);
	HRESULT initialize(Image* image, float centerX, float centerY, int frameColumn, int frameRow);

	void frameUpdate(float elapsedTime);
	
	void setFPS(int framePerSec);
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);

	void start(void);		//플레이 시작~
	void stop(void);		//정지
	void pause(void);		//일시 정지
	void resume(void);		//이어서 시작

	//getter
	//뻉뻉이냐?
	inline BOOL isPlay() { return _isPlay; }
	inline BOOL isLoop() { return _isLoop; }
	inline BOOL isReverse() { return _isReverse; }
};

