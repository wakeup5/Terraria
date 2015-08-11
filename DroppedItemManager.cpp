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
		eathOtherCollision();
	}
	void DroppedItemManager::render(HDC hdc)
	{
		for (_siItem = _sItem.begin(); _siItem != _sItem.end(); _siItem++)
		{
			(*_siItem)->render(hdc);
		}
	}

	DroppedItem* DroppedItemManager::createDroppedItem(std::string itemName, int amount, float x, float y, float speedX, float angle)
	{
		if (_sItem.size() > 20) return NULL;
		
		DroppedItem* item = new DroppedItem;
		item->initialize(itemName, amount);
		item->setManager(this);
		item->setCenter(x, y);
		item->setAngleR(angle);
		item->setSpeedX(speedX);

		_sItem.insert(item);

		return item;
	}


	void DroppedItemManager::eathOtherCollision()
	{
		set<DroppedItem*>::iterator d1;
		set<DroppedItem*>::iterator d2;
		RECT r;
		int i, j;
		DroppedItem* item1;
		DroppedItem* item2;
		for (d1 = _sItem.begin(), i = 0; d1 != _sItem.end(); d1++, i++)
		{
			item1 = *d1;
			for (d2 = _sItem.begin(), j = 0; d2 != _sItem.end(); d2++, j++)
			{
				if (i == j) continue;
				item2 = *d2;

				if (IntersectRect(&r, &item1->getRect(), &item2->getRect()) &&
					item1->getName() == item2->getName())
				{
					if (!item1->isFull())
					{
						item1->addAmount(item2->getAmount());
						item2->release();
					}
					else if (!item2->isFull())
					{
						item1->addAmount(item2->getAmount());
						item2->release();
					}
					break;
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
					pm->getInventory()->setItem(pm->getInventory()->getEmptyNum(), ITEMMANAGER->createItem((*iter)->getName(), (*iter)->getAmount()));
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