#include "stdafx.h"
#include "Loading.h"


Loading::Loading()
{

}

Loading::~Loading()
{

}
HRESULT Loading::initialize()
{
	_current = 0;
	_loadingBar = new ProgressBar;

	Image* back = IMAGEMANAGER->addImage("loading bar back", IMAGE("/logo/loading bar"), 620, 70, TRUE, TRANS_COLOR);
	Image* bar = IMAGEMANAGER->addImage("loading bar", IMAGE("/logo/loading bar1"), 620, 70, TRUE, TRANS_COLOR);

	_loadingBar->initialize(bar, back, _option.width() / 2, _option.height() - 250);
	return S_OK;
}
void Loading::release()
{

}
void Loading::update()
{
	_loadingBar->update();
}
void Loading::render(HDC hdc)
{
	_loadingBar->render(hdc);
}

void Loading::loadImage(string keyName, const char* fileName, float width, float height, BOOL trans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);
	_vLoadItem.push_back(item);
}
void Loading::loadSound(string keyName, const char* fileName, bool isBackground, bool isLoop)
{
	LoadItem* item = new LoadItem;
	item->initForSound(keyName, fileName, isBackground, isLoop);
	_vLoadItem.push_back(item);
}

BOOL Loading::loadNext(void)
{
	if (_current >= _vLoadItem.size())
	{
		_loadingBar->setInfo(1, 1);
		return false;
	}

	LoadItem* item = _vLoadItem[_current];
	
	switch (item->getLoadingKind())
	{
	case LOADING_TYPE_ADDIMAGE:
	{
		tagImageResource resource = item->getImgResource();
		IMAGEMANAGER->addImage(resource.keyName, resource.fileName, resource.width, resource.height, resource.trans, resource.transColor);
		break;
	}
	case LOADING_TYPE_ADDSOUND:
	{	
		tagSoundResource resource = item->getSoundResource();
		SOUNDMANAGER->addSound(resource.keyName, resource.fileName, resource.isBackground, resource.isLoop);
		break;
	}
	}

	_loadingBar->setInfo((float)_vLoadItem.size(), (float)_current);

	//Ä«¿îÆ®
	_current++;

	return true;
}

LoadItem::LoadItem()
{

}
LoadItem::~LoadItem()
{

}

HRESULT LoadItem::initForImage(string keyName, const char* fileName, float width, float height, BOOL trans, COLORREF transColor)
{
	_type = LOADING_TYPE_ADDIMAGE;

	memset(&_imageResource, 0, sizeof(_imageResource));

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.fileName = fileName;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}
HRESULT LoadItem::initForSound(string keyName, const char* fileName, bool isBackground, bool isLoop)
{
	_type = LOADING_TYPE_ADDSOUND;

	memset(&_soundResource, 0, sizeof(_soundResource));

	_soundResource.fileName = fileName;
	_soundResource.keyName = keyName;
	_soundResource.isBackground = isBackground;
	_soundResource.isLoop = isLoop;

	return S_OK;
}