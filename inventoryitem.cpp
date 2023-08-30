#include "inventoryitem.h"

InventoryItem::InventoryItem()
{
}

InventoryItem::InventoryItem(ITEM_TYPE it, ITEM_NAME in, int p)
{
	itemType = it;
	itemName = in;

	switch(in)
	{
		case TURNIP:
			sName = "Turnip";
			break;
		case STRAWBERRY:
			sName = "Strawberry";
			break;
		case PUMPKIN:
			sName = "Pumpkin";
			break;
		case BROCCOLI:
			sName = "Broccoli";
			break;
		case SEEDS:
			sName = "Seeds";
			break;
	}

	buyPrice = p;
	sellPrice = buyPrice/2;
}

int InventoryItem::getSellPrice()
{
	return sellPrice;
}

int InventoryItem::getBuyPrice()
{
	return buyPrice;
}

std::string InventoryItem::getSName()
{
	return sName;
}

ITEM_TYPE InventoryItem::getItemType()
{
	return itemType;
}

int InventoryItem::getColor()
{
	return color;
}

void InventoryItem::setPrice(int p)
{
	buyPrice = p;
	sellPrice = buyPrice/2;
}

void InventoryItem::setSName(std::string s)
{
	sName = s;
}

void InventoryItem::setColor(int c)
{
	color = c;
}
