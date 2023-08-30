#ifndef CROP_H
#define CROP_H

#include <ncurses.h>
#include <time.h>

#include "inventoryitem.h"

class Crop: virtual public Object
{
	private:
		char stage[4];
		int currentStage = 0;
		int stageDelay = 5;	

		time_t planted;

	public:
		Crop(char, int, int, bool);

		char getStage(int); // get stage char based on index entered	
		time_t getTime();

		int getCurrentStage();
		int getStageDelay();

		void setStage(char, char, char, char); // set all stage char
		void setStage(int, char); // int index, char to set
					
		void nextStage();

		InventoryItem* getInvItem();
};

#endif
