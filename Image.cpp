#include "stdafx.h"
#include "Image.h"

#pragma comment (lib, "msimg32.lib")

Image::Image() 
	:_imageInfo(NULL),
	_fileName(NULL),
	_trans(FALSE),
	_transColor(RGB(0, 0, 0)),
	_blendImage(NULL)
{

}

Image::~Image()
{

}

HRESULT Image::initialize(int width, int height)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new ImageInfo;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);

	_fileName = NULL;

	_trans = TRUE;
	_transColor = RGB(255, 0, 255);

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new ImageInfo;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);

	ReleaseDC(_hWnd, hdc);

	_width = width;
	_height = height;
	_centerX = width / 2;
	_centerY = height / 2;

	setBoundingBox();

	//이미지 리소스를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}
/// 이미지 로드 : 파일 명, 이미지 폭, 이미지 높이, 제외여부, 제외할 색
HRESULT Image::initialize(const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	return initialize(fileName, width / 2, height / 2, width, height, trans, transColor);
}
/// 이미지 로드 : 파일 명, 중심 좌표 x, 중심 좌표 y, 이미지 폭, 이미지 높이, 제외여부, 제외할 색
HRESULT Image::initialize(const char* fileName, float centerX, float centerY, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new ImageInfo;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);

	_fileName = NULL;

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new ImageInfo;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);

	_angleImage = new ImageInfo;
	_angleImage->resID = 0;
	_angleImage->hMemDC = CreateCompatibleDC(hdc);
	_angleImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, max(width * 1.42, height * 1.42), max(width * 1.42, height * 1.42));
	_angleImage->hOBit = (HBITMAP)SelectObject(_angleImage->hMemDC, _angleImage->hBit);
	
	ReleaseDC(_hWnd, hdc);

	_width = width;
	_height = height;
	_centerX = centerX;
	_centerY = centerY;

	setBoundingBox();

	//이미지 리소스를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

/// 이미지 자원 반환
void Image::release(void)
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//SelectObject(_angleImage->hMemDC, _angleImage->hOBit);
		////DeleteObject(_angleImage->hBit);
		//DeleteDC(_angleImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_blendImage);
		SAFE_DELETE(_angleImage);
		SAFE_DELETE(_fileName);

		_trans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	std::vector<SpriteImage*>::iterator iter;
	for (iter = _vSpriteImage.begin(); iter != _vSpriteImage.end();)
	{
		SAFE_DELETE((*iter));
		iter = _vSpriteImage.erase(iter);
	}

	_vSpriteImage.clear();
}

SpriteImage* Image::createSprite(int frameCol, int frameRow, int frameX, int frameY)
{
	SpriteImage* sprite = new SpriteImage();

	sprite->initialize(this, frameCol, frameRow, frameX, frameY);

	//_vSpriteImage.push_back(sprite);

	return sprite;
}

SpriteImage* Image::createSprite(float centerX, float centerY, int frameCol, int frameRow, int frameX, int frameY)
{
	SpriteImage* sprite = new SpriteImage();

	sprite->initialize(this, centerX, centerY, frameCol, frameRow, frameX, frameY);

	//_vSpriteImage.push_back(sprite);

	return sprite;
}

AnimationImage* Image::createAnimate(int frameCol, int frameRow)
{
	AnimationImage* animation = new AnimationImage;
	animation->initialize(this, frameCol, frameRow);

	return animation;
}
AnimationImage* Image::createAnimate(float centerX, float centerY, int frameCol, int frameRow)
{
	AnimationImage* animation = new AnimationImage;
	animation->initialize(this, centerX, centerY, frameCol, frameRow);

	return animation;
}

void Image::removeSpriteImage(SpriteImage* sprite)
{
	return;
	std::vector<SpriteImage*>::iterator iter;
	for (iter = _vSpriteImage.begin(); iter != _vSpriteImage.end(); iter++)
	{
		//주소값 비교?
		if (sprite == *iter)
		{
			SAFE_DELETE((*iter));
			_vSpriteImage.erase(iter);
			break;
		}
	}
}

//투명키 값 설정
void Image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

/// 일반 렌더링
void Image::render(HDC hdc, BYTE alpha)
{
	render(hdc, _centerX - _width / 2, _centerY - _height / 2, 0, 0, _width, _height, alpha);
}
/// 일반 렌더링 : 원본이미지의 상단 좌측 좌표 x, y, 잘라낼 폭, 잘라낼 높이
void Image::render(HDC hdc, int sourX, int sourY, int width, int height, BYTE alpha)
{
	render(hdc, _centerX - width / 2, _centerY - height / 2, sourX, sourY, width, height, alpha);
}

/// 이미지 객체의 중심 좌표를 무시하고 원하는 좌표에 그릴 수 있다.
/// 위치 렌더링 : 화면에 그릴 위치 x, y
void Image::render(HDC hdc, int destX, int destY, BYTE alpha)
{
	render(hdc, destX, destY, 0, 0, _width, _height, alpha);
}
/// 위치 렌더링 : 화면에 그릴 위치 x, y, 원본이미지의 상단 좌측 좌표 x, y, 잘라낼 폭, 잘라낼 높이
void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int width, int height, BYTE alpha)
{
	BITMAP hdcBitmap;
	GetObject(GetCurrentObject(hdc, OBJ_BITMAP), sizeof(BITMAP), &hdcBitmap);

	//DC범위 밖이면 그릴 필요 없음
	//if (destX > _option.width() || destY > _option.windowHeight || destX + width < 0 || destY + height < 0) return;

	//알파블렌더에 문제가 있는듯. 화면 밖을 복사 하려면 안나옴.
	if (destX + width > hdcBitmap.bmWidth) width = hdcBitmap.bmWidth - destX;
	if (destY + height > hdcBitmap.bmHeight) height = hdcBitmap.bmHeight - destY;
	if (destX < 0)
	{
		sourX -= destX;
		width += destX;
		destX = 0;
	}
	if (destY < 0)
	{
		sourY -= destY;
		height += destY;
		destY = 0;
	}

	//투명도가 있으면
	if (alpha != 255)
	{
		alphaRender(hdc, destX, destY, width, height, sourX, sourY, width, height, alpha);
		return;
	}

	//투명도가 없으면
	if (_trans)
	{
		GdiTransparentBlt(hdc, destX, destY, width, height, _imageInfo->hMemDC, sourX, sourY, width, height, _transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY, width, height, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}

}

void Image::render(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	BITMAP hdcBitmap;
	GetObject(GetCurrentObject(hdc, OBJ_BITMAP), sizeof(BITMAP), &hdcBitmap);

	//DC범위 밖이면 그릴 필요 없음
	//if (destX > _option.windowWidth || destY > _option.windowHeight || destX + destWidth < 0 || destY + destHeight < 0) return;

	//알파블렌더에 문제가 있는듯. 화면 밖을 복사 하려면 안나옴.
	if (destX + destWidth > hdcBitmap.bmWidth) destWidth = hdcBitmap.bmWidth - destX;
	if (destY + destHeight > hdcBitmap.bmHeight) destHeight = hdcBitmap.bmHeight - destY;
	if (destX < 0)
	{
		sourX -= destX;
		destWidth += destX;
		destX = 0;
	}
	if (destY < 0)
	{
		sourY -= destY;
		destHeight += destY;
		destY = 0;
	}
	
	//투명도가 있으면
	if (alpha != 255)
	{
		alphaRender(hdc, destX, destY, destWidth, destHeight, sourX, sourY, sourWidth, sourHeight, alpha);
		return;
	}

	//투명도가 없으면
	if (_trans)
	{
		GdiTransparentBlt(hdc, destX, destY, destWidth, destHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);
	}
	else
	{
		StretchBlt(hdc, destX, destY, destWidth, destHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, SRCCOPY);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	//투명처리를 할 경우
	if (_trans)
	{
		//이미지 위치와 크기만큼 배경 DC의 그림을 가져와 blendImage에 복사.
		BitBlt(_blendImage->hMemDC, destX, destY, destWidth, destHeight, hdc, destX, destY, SRCCOPY);

		//blendImage에 이미지를 복사
		GdiTransparentBlt(_blendImage->hMemDC, destX, destY, destWidth, destHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		//투명도를 지정하여 배경DC에 이미지를 범위만큼 복사.
		AlphaBlend(hdc, destX, destY, destWidth, destHeight, _blendImage->hMemDC, destX, destY, sourWidth, sourHeight, _blendFunc);

	}
	//하지 않을 경우
	else
	{
		BitBlt(_blendImage->hMemDC, destX, destY, destWidth, destHeight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
		AlphaBlend(hdc, destX, destY, destWidth, destHeight, _blendImage->hMemDC, destX, destY, sourWidth, sourHeight, _blendFunc);
	}
}

void Image::sizeRender(HDC hdc, int destX, int destY, int width, int height, BYTE alpha)
{
	render(hdc, destX, destY, width, height, destX, destY, getWidth(), getHeight(), alpha);
}

void Image::sizeRender(HDC hdc, double ratio, BYTE alpha)
{
	float width = _width * ratio;
	float height = _height * ratio;
	render(hdc, _centerX - width / 2, _centerY - height / 2, width, height, 0, 0, _width, _height, alpha);
}

void Image::rotateRender(HDC hdc, float angle)
{
	int width = max(_width * 1.42, _height * 1.42);
	int height = max(_width * 1.42, _height * 1.42);

	BitBlt(_angleImage->hMemDC, 0, 0, width, height, hdc, _centerX - width / 2, _centerY - height / 2, SRCCOPY);

	POINT pt[3];
	pt[0] = myUtil::getRotatePoint(width / 2, height / 2, -_width / 2, -_height / 2, angle);
	pt[1] = myUtil::getRotatePoint(width / 2, height / 2, _width / 2, -_height / 2, angle);
	pt[2] = myUtil::getRotatePoint(width / 2, height / 2, -_width / 2, _height / 2, angle);

	PlgBlt(_angleImage->hMemDC, pt, getMemDC(), 0, 0, getWidth(), getHeight(), NULL, 0, 0);

	GdiTransparentBlt(hdc, _centerX - width / 2, _centerY - height / 2, width, height, _angleImage->hMemDC, 0, 0, width, height, _transColor);
}


void Image::rotateRender(HDC hdc, float x, float y, float angle)
{
	int width = max(_width * 1.2, _height * 1.2);
	int height = max(_width * 1.2, _height * 1.2);

	if (false && abs(_prevAngle - angle) < M_PI / 32)
	{
		BitBlt(hdc, x - width / 2, y - height / 2, width, height, _angleImage->hMemDC, 0, 0, SRCCOPY);
		_prevAngle = angle;
		return;
	}
	_prevAngle = angle;

	BitBlt(_angleImage->hMemDC, 0, 0, width, height, hdc, x - width / 2, y - height / 2, SRCCOPY);

	POINT pt[3];
	pt[0] = myUtil::getRotatePoint(width / 2, height / 2, -_width / 2, -_height / 2, angle);
	pt[1] = myUtil::getRotatePoint(width / 2, height / 2, _width / 2, -_height / 2, angle);
	pt[2] = myUtil::getRotatePoint(width / 2, height / 2, -_width / 2, _height / 2, angle);

	PlgBlt(_angleImage->hMemDC, pt, getMemDC(), 0, 0, getWidth(), getHeight(), NULL, 0, 0);

	GdiTransparentBlt(hdc, x - width / 2, y - height / 2, width, height, _angleImage->hMemDC, 0, 0, width, height, _transColor);
}

void Image::sizeRotateRender(HDC hdc, double ratio, float angle)
{
	int width = max(_width * 1.42, _height * 1.42);
	int height = max(_width * 1.42, _height * 1.42);

	BitBlt(_angleImage->hMemDC, 0, 0, width, height, hdc, _centerX - width / 2, _centerY - height / 2, SRCCOPY);

	POINT pt[3];
	pt[0] = myUtil::getRotatePoint(width / 2, height / 2, -_width * ratio / 2, -_height * ratio / 2, angle);
	pt[1] = myUtil::getRotatePoint(width / 2, height / 2, _width * ratio / 2, -_height * ratio / 2, angle);
	pt[2] = myUtil::getRotatePoint(width / 2, height / 2, -_width * ratio / 2, _height * ratio / 2, angle);

	PlgBlt(_angleImage->hMemDC, pt, getMemDC(), 0, 0, getWidth(), getHeight(), NULL, 0, 0);

	GdiTransparentBlt(hdc, _centerX - width / 2, _centerY - height / 2, width, height, _angleImage->hMemDC, 0, 0, width, height, _transColor);
}

//루프 렌더링
void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//옵셋값이 음수인 경우에는 보정..
	if (offsetX < 0) offsetX = _width + (offsetX % _width);
	if (offsetY < 0) offsetY = _height + (offsetY % _height);

	//그려지는 소스 영역~~
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 dc 영역~~
	RECT rcDest;

	//그려야할 전체 영역~~
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역 높이 계산한다
		rcSour.top = (y + offsetY) % _height;
		rcSour.bottom = _height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리기화면을 넘어갔으면..
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역~~~
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역 가로 계산한다
			rcSour.left = (x + offsetX) % _width;
			rcSour.right = _width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리기화면을 넘어갔으면..
			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역~~~
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그린당
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}

}

//루프 렌더링
void Image::loopXRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//옵셋값이 음수인 경우에는 보정..
	if (offsetX < 0) offsetX = _width + (offsetX % _width);
	//if (offsetY < 0) offsetY = _height + (offsetY % _height);

	//그려지는 소스 영역~~
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 dc 영역~~
	RECT rcDest;

	//그려야할 전체 영역~~
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	
	//소스 영역 높이 계산한다
	rcSour.top = 0;
	rcSour.bottom = _height;

	//그려지는 영역~~~
	rcDest.top = offsetY;
	rcDest.bottom = offsetY + _height;

	for (int x = 0; x < drawAreaW; x += sourWidth)
	{
		//소스 영역 가로 계산한다
		rcSour.left = (x + offsetX) % _width;
		rcSour.right = _width;
		sourWidth = rcSour.right - rcSour.left;

		//소스 영역이 그리기화면을 넘어갔으면..
		if (x + sourWidth > drawAreaW)
		{
			rcSour.right -= (x + sourWidth) - drawAreaW;
			sourWidth = rcSour.right - rcSour.left;
		}

		//그려지는 영역~~~
		rcDest.left = x + drawAreaX;
		rcDest.right = rcDest.left + sourWidth;

		//그린당
		render(hdc, rcDest.left, rcDest.top,
			rcSour.left, rcSour.top,
			rcSour.right - rcSour.left,
			rcSour.bottom - rcSour.top);
	}
	

}

void Image::aniRender(HDC hdc, int destX, int destY, Animate* animate, BYTE alpha)
{
	render(hdc, destX, destY, animate->getFramePos().x, animate->getFramePos().y, animate->getFrameWidth(), animate->getFrameHeight(), alpha);
}