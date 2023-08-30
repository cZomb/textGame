#ifndef PLAYER_H
#define PLAYER_H

#include <ncurses.h>
#include "object.h"

enum DIR { LEFT, UP, RIGHT, DOWN }; // enum for handling character movement direction
enum LOC { HOUSE, OUTSIDE };
enum STATE { NORMAL, ITEM_MENU };

class Player 
{
	private:
		int xPos; // x position
		int yPos; // y position
		
		DIR dir;
		LOC loc;
		STATE state;

		const char* cChar = " "; // player character to draw to screen

	public:
		Player(); // default constructor
		Player(int, int); // constructor accepts a point (x, y)

		void draw(WINDOW*); // draw player to screen
		void move(DIR); // move player based on direction
		bool collides(Object*);
		
		// accessors
		int getXPos();
		int getYPos();

		const char* getChar();

		LOC getLoc();
		STATE getState();

		// mutators
		void setXPos(int);
		void setYPos(int);

		void setLoc(LOC);
		void setState(STATE);
};

#endif
