#include "StdAfx.h"
#include "SceneManager.h"
#include "gameNode.h"

//로딩 쓰레드 함수를 프렌드로 선언
DWORD CALLBACK loadingThread(LPVOID prc)
{
	//교체될 init 함수를 실행한다
	SceneManager::_readyScene->initialize();

	//현재씬을 교체될 씬으로 바꾼다
	SceneManager::_currentScene = SceneManager::_readyScene;

	//로딩씬 해제...
	SceneManager::_loadingScene->release();
	SceneManager::_loadingScene = NULL;
	SceneManager::_readyScene = NULL;

	return 0;
}

Scene* SceneManager::_currentScene = NULL;
Scene* SceneManager::_loadingScene = NULL;
Scene* SceneManager::_readyScene = NULL;

SceneManager::SceneManager(void)
{
}

SceneManager::~SceneManager(void)
{
}

HRESULT SceneManager::initialize(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void SceneManager::release(void)
{
	if (_currentScene) _currentScene->release();
}

void SceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}

void SceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}


//씬 추가한다
Scene* SceneManager::addScene(string sceneName, Scene* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

//로딩씬 추가한다
Scene* SceneManager::addLoadingScene(string loadingSceneName, Scene* scene)
{
	if (!scene) return NULL;

	_mLoadingSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

//씬체인지..
HRESULT SceneManager::changeScene(string sceneName)
{
	//바꿀 씬을 찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	//못찾으면.. 실패 반환..
	if (find == _mSceneList.end()) return E_FAIL;

	//새롭게 변경되는 씬을 초기화 한다
	if (SUCCEEDED(find->second->initialize()))
	{
		//기존에 씬이 있으면 릴리즈..
		if (_currentScene) _currentScene->release();
		_currentScene = find->second;

		return S_OK;
	}
	return E_FAIL;
}

