#pragma once


class GameNode
{
private:
	static Image* _backBuffer;
	HDC _hdc;
	bool _managerInit;

public:
	GameNode();
	virtual ~GameNode();

	virtual HRESULT initialize(bool = false);
	virtual void release(void);
	virtual void update(void);
	virtual void render();
	
	virtual LRESULT mainProc(HWND, UINT, WPARAM, LPARAM);

	static void setBackBuffer(int width, int height);
	static Image* getBackBuffer(void) { return _backBuffer; }
	static HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }
};

