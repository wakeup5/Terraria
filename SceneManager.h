#pragma once

#include <map>
#include <string>
#include "Singletonbase.h"
#include "GameNode.h"

//1503기 20150622 한울이 허니버터칩 줬음... 천원 줬는데 안받음..

class Scene
{
public:
	virtual HRESULT initialize(void) = 0;
	virtual void release(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;

	Image* getBackBuffer(void) { return GameNode::getBackBuffer(); }
	HDC getMemDC() { return GameNode::getMemDC(); }
};

class SceneManager : public SingletonBase < SceneManager >
{
public:
	typedef map<string, Scene*> mapSceneList;
	typedef map<string, Scene*>::iterator mapSceneIter;

private:
	static Scene* _currentScene;	//현재씬
	static Scene* _loadingScene;	//로딩씬
	static Scene* _readyScene;	//교체 대기중인 씬..

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

public:
	HRESULT initialize(void);
	void render(void);
	void update(void);
	void release(void);

	//씬 추가한다
	Scene* addScene(string sceneName, Scene* scene);

	//로딩씬 추가한다
	Scene* addLoadingScene(string loadingSceneName, Scene* scene);

	//씬체인지..
	HRESULT changeScene(string sceneName);

	//로딩 쓰레드 함수를 프렌드로 선언
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	SceneManager(void);
	~SceneManager(void);
};
