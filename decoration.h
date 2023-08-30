#ifndef DECORATION_H
#define DECORATION_H

#include <ncurses.h>
#include <iostream>

#include "inventoryitem.h"
#include "object.h"

class Decoration: virtual public Object, public InventoryItem
{
	public:

		Decoration(char, std::string, int, int, bool, int);
};

#endif

