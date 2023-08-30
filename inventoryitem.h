#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <ncurses.h>
#include <iostream>
#include "object.h"

class InventoryItem
{
	private:
		std::string sName;
	
		int sellPrice;
		int buyPrice;

		ITEM_TYPE itemType;
		ITEM_NAME itemName;

		int color = 1;

	public:

		InventoryItem();
		InventoryItem(ITEM_TYPE, ITEM_NAME, int); // itemtype, item name, buy price

		InventoryItem* newInvItem(ITEM_NAME); // return new object for specified item type

		// accessors
		int getSellPrice();
		int getBuyPrice();

		int getColor();

		std::string getSName();
		ITEM_TYPE getItemType();

		// mutators
		void setPrice(int); // set buy price; sell price is adjusted based on buy price
		void setSName(std::string);

		void setColor(int);
};

#endif
