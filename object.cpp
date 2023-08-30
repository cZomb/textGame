/* CPP file for handling Object class */

#include "object.h"

Object::Object()
// code goes here
{
	xPos = 0;
	yPos = 0;
	cChar = '#';
	solid = false;
	occupied = false;
	color = 1;
}

Object::Object(char c, int x, int y, bool b)
{
	xPos = x;
	yPos = y;
	cChar = c;
	solid = b;
	occupied = false;
	color = 1;
}

void Object::draw(WINDOW* w)
{
	mvwprintw(w, yPos, xPos, "%c", cChar);
}

void Object::cDraw(WINDOW* w, int c)
{
	frameCount++;

	if(frameCount>=MAX_FRAME)
	{
		frameCount=0;

		if(invertColor)
			invertColor = false;
		else
			invertColor = true;
	}

	if(!invertColor)
		attron(COLOR_PAIR(color));
	else
		attron(COLOR_PAIR(c));

	mvwprintw(w, yPos, xPos, "%c", cChar);
}

ITEM_NAME Object::getItemName()
{
	return itemName;
}

ITEM_TYPE Object::getItemType()
{
	return itemType;
}

int Object::getXPos()
{
	return xPos;
}

int Object::getYPos()
{
	return yPos;
}

bool Object::getSolid()
{
	return solid;
}

char Object::getChar()
{
	return cChar;
}

bool Object::getOccupied()
{
	return occupied;
}

int Object::getColor()
{
	return color;
}

void Object::setXPos(int x)
{
	xPos = x;
}

void Object::setYPos(int y)
{
	yPos = y;
}

void Object::setPos(int x, int y)
{
	xPos = x;
	yPos = y;
}

void Object::setSolid(bool s)
{
	solid = s;
}

void Object::setCChar(char c)
{
	cChar = c;
}

void Object::setOccupied(bool o)
{
	occupied = o;
}

void Object::setColor(int c)
{
	color = c;
}

void Object::setItemType(ITEM_TYPE it)
{
	itemType = it;
}

void Object::setItemName(ITEM_NAME in)
{
	itemName = in;
}
