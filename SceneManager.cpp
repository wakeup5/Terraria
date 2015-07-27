#include "StdAfx.h"
#include "SceneManager.h"
#include "gameNode.h"

//�ε� ������ �Լ��� ������� ����
DWORD CALLBACK loadingThread(LPVOID prc)
{
	//��ü�� init �Լ��� �����Ѵ�
	SceneManager::_readyScene->initialize();

	//������� ��ü�� ������ �ٲ۴�
	SceneManager::_currentScene = SceneManager::_readyScene;

	//�ε��� ����...
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


//�� �߰��Ѵ�
Scene* SceneManager::addScene(string sceneName, Scene* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

//�ε��� �߰��Ѵ�
Scene* SceneManager::addLoadingScene(string loadingSceneName, Scene* scene)
{
	if (!scene) return NULL;

	_mLoadingSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

//��ü����..
HRESULT SceneManager::changeScene(string sceneName)
{
	//�ٲ� ���� ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	//��ã����.. ���� ��ȯ..
	if (find == _mSceneList.end()) return E_FAIL;

	//���Ӱ� ����Ǵ� ���� �ʱ�ȭ �Ѵ�
	if (SUCCEEDED(find->second->initialize()))
	{
		//������ ���� ������ ������..
		if (_currentScene) _currentScene->release();
		_currentScene = find->second;

		return S_OK;
	}
	return E_FAIL;
}

