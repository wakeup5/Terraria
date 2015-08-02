#pragma once
#include <list>
#include <string>

enum LOADING_TYPE
{
	LOADING_TYPE_ADDIMAGE_00,
	LOADING_TYPE_ADDIMAGE_01,
	LOADING_TYPE_ADDIMAGE_02,
	LOADING_TYPE_ADDFRAMEIMAGE_00,
	LOADING_TYPE_ADDFRAMEIMAGE_01,
	LOADING_TYPE_ADDSOUND,
	LOADING_TYPE_END,
};

struct tagImageResource
{
	std::string keyname;
	const char* filename;
	int x, y;
	int width, height;
	bool trans;
	COLORREF transColor;
};

class LoadItem
{
private:
	LOADING_TYPE _type;

	tagImageResource _imgResource;

public:
	LoadItem();
	virtual ~LoadItem();
};

class Loading
{
private:

public:
	HRESULT initialize();
	void release();
	void update();
	void render();

	Loading();
	virtual ~Loading();
};

