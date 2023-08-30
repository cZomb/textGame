/* CPP file for handling Player class */

#include "player.h"

// basic constructor
Player::Player()
{
	xPos = 0;
	yPos = 0;

	dir = DOWN;
	loc = OUTSIDE;
}

// position-based constructor
Player::Player(int x, int y) 
{
	xPos = x;
	yPos = y;

	dir = DOWN;
	loc = OUTSIDE;
}

// draw to screen
void Player::draw(WINDOW* win)
{
	mvwprintw(win, yPos, xPos, cChar);
}

// move the player
void Player::move(DIR d) 
{
	dir = d;

	switch (d)
	{
		case LEFT:
			xPos--;
			break;
		case RIGHT:
			xPos++;
			break;
		case UP:
			yPos--;
			break;
		case DOWN:
			yPos++;
			break;
	}

	clear();
}

bool Player::collides(Object* o)
{
	bool b = false;

	if(xPos == o->getXPos() &&
	   yPos == o->getYPos())
	{
		b = true;

		if(o->getSolid())
		{
			switch(dir)
			{
				case LEFT:
					xPos++;
					break;
				case RIGHT:
					xPos--;
					break;
				case UP:
					yPos++;
					break;
				case DOWN:
					yPos--;
					break;
			}
		}
	}

	return b;
}

// accessors
int Player::getXPos() 
{
	return xPos;
}

int Player::getYPos()
{
	return yPos;
}

const char* Player::getChar() 
{
	return cChar;
}

LOC Player::getLoc()
{
	return loc;
}

STATE Player::getState()
{
	return state;
}

// mutators
void Player::setXPos(int x)
{
	xPos = x;
}

void Player::setYPos(int y)
{
	yPos = y;
}

void Player::setLoc(LOC l)
{
	loc = l;
}

void Player::setState(STATE s)
{
	state = s;
}
