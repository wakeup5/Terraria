#include "StdAfx.h"
#include "KeyManager.h"

KeyManager::KeyManager(void)
{
}

KeyManager::~KeyManager(void)
{
}

HRESULT KeyManager::initialize(void)
{
	//초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		this->setKeyUp(i, false);
		this->setKeyDown(i, false);
		this->setKeyOnceDown(i, false);
	}

	return S_OK;
}

void KeyManager::release(void)
{
}

void KeyManager::update(void)
{
	_keyOnceDown.reset();
}
//키가 한번만 눌렸을때..
bool KeyManager::isOnceKeyDown(int key)
{
	if (this->_keyOnceDown[key] == TRUE) return true;

	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			this->setKeyOnceDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);

	return false;
}

//키를 한번만 눌렀다 떼었을때...
bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}
	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetAsyncKeyState(key) & 0x0001) return true;
	return false;
}
