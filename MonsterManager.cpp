#include "stdafx.h"
#include "MonsterManager.h"
#include "Player.h"

namespace Terraria
{
	MonsterManager::MonsterManager()
	{
	}

	MonsterManager::~MonsterManager()
	{
	}

	HRESULT MonsterManager::initialize(Player* player)
	{
		_vMonster.clear();

		_player = player;

		return S_OK;
	}

	void MonsterManager::release()
	{
		/*
		viUnit iter = _vMonster.begin();
		for (; iter != _vMonster.end(); iter++)
		{
			SAFE_RELEASE(*iter);
		}
		*/
		for (int i = 0; i < _vMonster.size(); i++)
		{
			SAFE_RELEASE(_vMonster[i]);
		}

		_vMonster.clear();
	}

	void MonsterManager::update()
	{
		/*
		viUnit iter = _vMonster.begin();
		for (; iter != _vMonster.end();)
		{
			(*iter)->update();

			if (_player->getX() < (*iter)->getX())
			{
				if ((*iter)->getDirect() == RIGHT) (*iter)->move(LEFT);
			}
			else
			{
				if ((*iter)->getDirect() == LEFT) (*iter)->move(RIGHT);
			}

			printf("%d\n", (*iter)->getHp());
			if ((*iter)->getHp() <= 0)
			{
				SAFE_RELEASE(*iter);
				iter = _vMonster.erase(iter);
			}
			else
			{
				iter++;
			}
		}
		*/
		for (int i = 0; i < _vMonster.size(); i++)
		{
			_vMonster[i]->update();

			if (_player->getX() < _vMonster[i]->getX())
			{
				if (_vMonster[i]->getDirect() == RIGHT) _vMonster[i]->move(LEFT);
			}
			else
			{
				if (_vMonster[i]->getDirect() == LEFT) _vMonster[i]->move(RIGHT);
			}

			if (_vMonster[i]->getHp() <= 0)
			{
				SAFE_RELEASE(_vMonster[i]);
				_vMonster.erase(_vMonster.begin() + i);
				i--;
			}

		}

		if (ANIMATEMANAGER->findAnimation("zombie move left") != NULL) 
			ANIMATEMANAGER->findAnimation("zombie move left")->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (ANIMATEMANAGER->findAnimation("zombie move right") != NULL)
			ANIMATEMANAGER->findAnimation("zombie move right")->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (ANIMATEMANAGER->findAnimation("zombie jump left") != NULL)
			ANIMATEMANAGER->findAnimation("zombie jump left")->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (ANIMATEMANAGER->findAnimation("zombie jump right") != NULL)
			ANIMATEMANAGER->findAnimation("zombie jump right")->frameUpdate(TIMEMANAGER->getElapsedTime());
	}

	void MonsterManager::render(HDC hdc)
	{
		/*
		viUnit iter = _vMonster.begin();
		for (; iter != _vMonster.end(); iter++)
		{
			(*iter)->render(hdc);
		}
		*/
		for (int i = 0; i < _vMonster.size(); i++)
		{
			_vMonster[i]->render(hdc);
		}
	}

	void MonsterManager::createZombie(float x, float y)
	{
		if (_vMonster.size() > 10) return;

		Unit* monster = new Zombie;
		monster->initialize();
		monster->setCenter(x, y);

		_vMonster.push_back(monster);
	}
}