#ifndef OBJECT_H
#define OBJECT_H

#include <ncurses.h>
#include <map>

enum ITEM_TYPE { SEED, TOOL, DECORATION };
enum ITEM_NAME { TURNIP, STRAWBERRY, PUMPKIN, BROCCOLI, SEEDS };

class Object
{
	private:
		char cChar; // character to draw

		ITEM_TYPE itemType;
		ITEM_NAME itemName;

		bool solid;
		bool occupied = false;

		int xPos; // x position
		int yPos; // y position
	
		int color;

		int price;

		const int MAX_FRAME = 50000;
		int frameCount = 0;
		bool invertColor = false;

	public:

		Object(); // default constructor
		Object(char, int, int, bool); // main constructor

		void draw(WINDOW*); // draw to screen
		void cDraw(WINDOW*,int);

		// accessors
		int getXPos();
		int getYPos();

		bool getSolid();
		bool getOccupied();

		char getChar();

		int getColor();

		ITEM_NAME getItemName();
		ITEM_TYPE getItemType();

		// mutators
		void setXPos(int);
		void setYPos(int);

		void setPos(int, int);

		void setSolid(bool);
		void setCChar(char);

		void setOccupied(bool);

		void setColor(int);

		void setItemType(ITEM_TYPE);
		void setItemName(ITEM_NAME);
};

#endif
