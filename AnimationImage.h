#pragma once
#include "SpriteImage.h"

class AnimationImage : public SpriteImage
{
private:
	int _frameNum;			// ������ ����
	int _frameIndex;		// ���� ������ ��ȣ

	int _startIndex;		// ���� �ε��� ��ȣ
	int _endIndex;			// �� �ε��� ��ȣ

	float _frameUpdateSec;	// �ʴ� ������ ������Ʈ
	float _elapsedSec;		// �����Ӵ� ��� �ð�

	int _repeat;			// �ݺ��� Ƚ��

	BOOL _isLoop;			// �ݺ� �������
	BOOL _isPlay;			// �ִϸ��̼� ��� ����
	BOOL _isReverse;		// �Ųٷ� ��� �ϴ��� ����

public:
	AnimationImage(){}
	~AnimationImage(){}

	HRESULT initialize(Image* image, int frameColumn, int frameRow);
	HRESULT initialize(Image* image, float centerX, float centerY, int frameColumn, int frameRow);

	void frameUpdate(float elapsedTime);
	
	void setFPS(int framePerSec);
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);

	void start(void);		//�÷��� ����~
	void stop(void);		//����
	void pause(void);		//�Ͻ� ����
	void resume(void);		//�̾ ����

	//getter
	//�R�R�̳�?
	inline BOOL isPlay() { return _isPlay; }
	inline BOOL isLoop() { return _isLoop; }
	inline BOOL isReverse() { return _isReverse; }
};

