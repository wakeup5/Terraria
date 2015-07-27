/**
@file	stdafx.h
@author	박진한(wakeup5, wlsgks5@naver.com)
@date	2015/05/08
@brief	헤더 포함 리스트
*/
#pragma once
#include "targetver.h"

//MFC가 아닌 응용프로그램의 경우에는 WIN32_LEAN_AND_MEAN를 정의해 빌드 시간을 단축시킨다.
#define WIN32_LEAN_AND_MEAN

//math.h헤더의 define 상수 사용
#define _USE_MATH_DEFINES

/* ========================================
*  ## 헤더파일 ##
* ======================================== */
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

//필요에 따라 기본 라이브러리 헤더 추가
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <time.h>
#include <iostream>
#include <functional>

//매크로 헤더
#include "commonMacroFunction.h"

//사용자 정의 헤더
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "txtDataManager.h"
#include "Database.h"

#include "EffectManager.h"

#include "Background.h"

#include "util.h"

//클래스
#include "GameObject.h"
#include "Timer.h"
#include "Image.h"
#include "SpriteImage.h"
#include "AnimationImage.h"

#include "GameInfo.h"
#include "Camera.h"

#include "TerrariaNode.h"

//게임 스터디
#include "GameStudy.h"


/* ========================================
*  ## 정의문 ##
* ======================================== */

//윈도우 이름
#define WIN_NAME		(LPTSTR)(TEXT("API Window"))

//윈도우 위치 사이즈
#define WIN_START_X		0		//x위치
#define WIN_START_Y		0		//y위치
#define WIN_SIZE_X		800		//폭
#define WIN_SIZE_Y		600		//높이

//윈도우 스타일
#define WIN_STYLE		WS_CAPTION | WS_SYSMENU

//안전 동적할당 해제 매크로
#define SAFE_DELETE(p)			{if (p) {delete(p); (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if (p) {delete[](p);}}
#define SAFE_RELEASE(p)			{if (p) {(p)->release(); delete(p); (p) = NULL;}}

//class RandomFunction
#define RANDOM RandomFunction::getSingleton()
//class KeyManager
#define KEYMANAGER KeyManager::getSingleton()
//class ImageManager
#define IMAGEMANAGER ImageManager::getSingleton()
//class TimeManager
#define TIMEMANAGER TimeManager::getSingleton()
//class EffectManager
#define EFFECTMANAGER EffectManager::getSingleton()
//class SceneManager
#define SCENEMANAGER SceneManager::getSingleton() 
//class TxtMAnager
#define TXTMANAGER txtDataManager::getSingleton()
//class Database
#define DATABASE Database::getSingleton()

//game info
#define MAX_GAME_FPS	60.0f

//round number
#define ROUNDING(x, dig)	( floor((x) * pow(float(10), dig) + 0.5f) / pow(float(10), dig) )

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

/* ========================================
*  ## 전역변수 ##
* ======================================== */
extern HINSTANCE _hInstance; // 프로그램 인스턴스
extern HWND _hWnd; // 윈도우 핸들

extern POINT _mousePt;
extern BOOL	_leftButtonDown;	//왼쪽 버튼

extern GameInfo _option;
extern Terraria::Camera _camera;