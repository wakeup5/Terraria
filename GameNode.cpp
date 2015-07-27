#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{

}


GameNode::~GameNode()
{

}
Image* GameNode::_backBuffer;

//�ʱ�ȭ
HRESULT GameNode::initialize(bool managerInit)
{
	_managerInit = managerInit;
	_hdc = GetDC(_hWnd);
	
	if (managerInit)
	{
		_backBuffer = NULL;
		setBackBuffer(_option.width(), _option.height());

		KEYMANAGER->initialize();					//Ű�Ŵ��� ����
		IMAGEMANAGER->initialize();				//�̹��� �Ŵ��� ����
		

		TIMEMANAGER->initialize();

		EFFECTMANAGER->initialize();
		SCENEMANAGER->initialize();

		Terraria::Background::getSingleton()->initailize();

	}

	return S_OK;
}

void GameNode::setBackBuffer(int width, int height)
{
	if (_backBuffer != NULL) SAFE_RELEASE(_backBuffer);

	_backBuffer = new Image;
	_backBuffer->initialize(width, height);
}

//����
void GameNode::release(void)
{
	//_backBuffer->release();
	//SAFE_DELETE(_backBuffer);

	//KillTimer(_hWnd, 0);

	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();

	EFFECTMANAGER->release();
	EFFECTMANAGER->releaseSingleton();

	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();

	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();

	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();

	Terraria::Background::getSingleton()->releaseSingleton();

	ReleaseDC(_hWnd, _hdc);
}

//ȭ�鰻��
void GameNode::update(void)
{
	//ȭ�� ����
	//InvalidateRect(_hWnd, NULL, false);
	KEYMANAGER->update();
}

//ȭ�����
void GameNode::render()
{
	
	_backBuffer->render(getHDC());
}

LRESULT GameNode::mainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		_leftButtonDown = true;
		break;
	case WM_LBUTTONUP:
		_leftButtonDown = false;
		break;
	case WM_CREATE:
		_mousePt = makePoint(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		_option.setMousePoint(_mousePt);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		_mousePt = makeMousePoint(lParam);
		_option.setMousePoint(_mousePt);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break; 
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
