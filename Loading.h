#pragma once
#include <list>
#include <string>
#include "ProgressBar.h"

enum LOADING_TYPE
{
	LOADING_TYPE_ADDIMAGE,
	LOADING_TYPE_ADDSOUND,
	LOADING_TYPE_END,
};

struct tagImageResource
{
	string keyName;
	const char* fileName;
	int width, height;
	bool trans;
	COLORREF transColor;
};

struct tagSoundResource
{
	string keyName;
	const char* fileName;
	bool isBackground;
	bool isLoop;
};

class LoadItem
{
private:
	LOADING_TYPE _type;

	tagImageResource _imageResource;
	tagSoundResource _soundResource;

public:
	HRESULT initForImage(string keyName, const char* fileName, float width, float height, BOOL trans, COLORREF transColor);
	HRESULT initForSound(string keyName, const char* fileName, bool isBackground, bool isLoop);

	//로딩 종류 접근자
	LOADING_TYPE getLoadingKind(void) { return _type; }

	//이미지리소스 접근자
	tagImageResource getImgResource(void) { return _imageResource; }
	tagSoundResource getSoundResource(){ return _soundResource; }

	LoadItem();
	virtual ~LoadItem();
};

class Loading
{
private:
	typedef vector<LoadItem*> arrLoadItem;
	typedef vector<LoadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;

	Image* _background;
	int _current;

	ProgressBar* _loadingBar;
public:
	HRESULT initialize();
	void release();
	void update();
	void render(HDC hdc);

	void loadImage(string keyName, const char* fileName, float width, float height, BOOL trans, COLORREF transColor);
	void loadSound(string keyName, const char* fileName, bool isBackground, bool isLoop);

	BOOL loadNext(void);

	Loading();
	virtual ~Loading();
};

