#pragma once

#include <map>
#include <string>
#include "Singletonbase.h"
#include "GameNode.h"

//1503�� 20150622 �ѿ��� ��Ϲ���Ĩ ����... õ�� ��µ� �ȹ���..

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
	static Scene* _currentScene;	//�����
	static Scene* _loadingScene;	//�ε���
	static Scene* _readyScene;	//��ü ������� ��..

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

public:
	HRESULT initialize(void);
	void render(void);
	void update(void);
	void release(void);

	//�� �߰��Ѵ�
	Scene* addScene(string sceneName, Scene* scene);

	//�ε��� �߰��Ѵ�
	Scene* addLoadingScene(string loadingSceneName, Scene* scene);

	//��ü����..
	HRESULT changeScene(string sceneName);

	//�ε� ������ �Լ��� ������� ����
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	SceneManager(void);
	~SceneManager(void);
};
