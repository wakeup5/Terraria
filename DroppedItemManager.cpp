#include "stdafx.h"
#include "DroppedItemManager.h"
#include "PlayerManager.h"
#include "TileMap.h"

namespace Terraria
{
	DroppedItemManager::DroppedItemManager()
	{
	}

	DroppedItemManager::~DroppedItemManager()
	{
	}

	HRESULT DroppedItemManager::initialize(TileMap* tileMap)
	{
		_tileMap = tileMap;
		return S_OK;
	}
	void DroppedItemManager::release()
	{
		DroppedItem* item;
		for (_siItem = _sItem.begin(); _siItem != _sItem.end();)
		{
			item = *_siItem;
			SAFE_DELETE(item);
			_siItem = _sItem.erase(_siItem);
		}

		_sItem.clear();
	}
	void DroppedItemManager::update()
	{
		for (_siItem = _sItem.begin(); _siItem != _sItem.end(); _siItem++)
		{
			(*_siItem)->update();
			Collision::tileCollision((*_siItem), _tileMap);
		}
		//eathOtherCollision();
	}
	void DroppedItemManager::render(HDC hdc)
	{
		for (_siItem = _sItem.begin(); _siItem != _sItem.end(); _siItem++)
		{
			(*_siItem)->render(hdc);
		}
	}

	DroppedItem* DroppedItemManager::createDroppedItem(std::string itemName, int amount, float x, float y, float speedX)
	{
		DroppedItem* item = new DroppedItem;
		item->initialize(itemName, amount);
		item->setManager(this);
		item->setCenter(x, y);
		item->setSpeedX(speedX);

		_sItem.insert(item);

		return item;
	}


	void DroppedItemManager::eathOtherCollision()
	{
		set<DroppedItem*>::iterator d1;
		set<DroppedItem*>::iterator d2;
		RECT r;

		for (d1 = _sItem.begin(); d1 != _sItem.end(); d1++)
		{
			for (d2 = _sItem.begin(); d2 != _sItem.end(); d2++)
			{
				if (*d1 == *d2) continue;

				if (IntersectRect(&r, &(*d1)->getRect(), &(*d2)->getRect()) &&
					(*d1)->getName() == (*d2)->getName())
				{
					if (!(*d1)->isFull())
					{
						(*d1)->addAmount((*d2)->getAmount());
						(*d2)->release();
					}
					else if (!(*d2)->isFull())
					{
						(*d2)->addAmount((*d1)->getAmount());
						(*d1)->release();
					}
				}
			}
		}
	}


	bool DroppedItemManager::playerCollision(PlayerManager* pm)
	{
		set<DroppedItem*>::iterator iter;
		RECT r;
		for (iter = _sItem.begin(); iter != _sItem.end();)
		{
			if (IntersectRect(&r, &pm->getPlayer()->getRect(), &(*iter)->getRect()))
			{
				Item* item = pm->getInventory()->findItem((*iter)->getName());
				if ((item == NULL || item->isMaxAmount()) && !pm->getInventory()->isFull())
				{
					pm->getInventory()->setItem(pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem((*iter)->getName()));
					delete (*iter);
					iter = _sItem.erase(iter);
				}
				else if (!item->isMaxAmount())
				{
					item->addAmount((*iter)->getAmount());
					delete (*iter);
					iter = _sItem.erase(iter);
				}
				else
				{
					iter++;
				}
			}
			else
			{
				iter++;
			}
		}

		return false;
	}


	void DroppedItemManager::removeDroppedItem(DroppedItem* item)
	{
		set<DroppedItem*>::iterator iter = _sItem.find(item);
		if (iter != _sItem.end())
		{
			delete *iter;
			_sItem.erase(iter);
		}
	}
}