#include "stdafx.h"
#include "DroppedItem.h"
#include "DroppedItemManager.h"

namespace Terraria
{
	DroppedItem::DroppedItem()
	{

	}

	DroppedItem::~DroppedItem()
	{

	}

	HRESULT DroppedItem::initialize(string itemName, int amount)
	{
		_image = IMAGEMANAGER->findImage(ITEMMANAGER->getImageName(itemName));
		_maxAmount = ITEMMANAGER->getMaxAmount(itemName);

		_itemName = itemName;
		_amount = amount;

		if (_amount > _maxAmount) _amount = _maxAmount;

		setMaxSpeed(200);
		setSize(20, 20);

		return S_OK;
	}
	void DroppedItem::release()
	{
		_container->removeDroppedItem(this);
	}
	void DroppedItem::update()
	{
		if (abs(getSpeedX()) > 10)
		{
			setAccelX(METER_TO_PIXEL * 5 * -myUtil::sign(getSpeedX()));
		}
		else
		{
			setAccelX(0);
			setSpeedX(0);
		}

		setAccelY(METER_TO_PIXEL * 5);

		activate();
	}
	void DroppedItem::render(HDC hdc)
	{
		_image->render(hdc, _option.getRenderX(getX()) - _image->getWidth() / 2, _option.getRenderY(getY()) - _image->getHeight() / 2);
	}
}