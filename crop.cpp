#include "crop.h"

std::map<ITEM_NAME, int> ITEM_PRICE = {{TURNIP, 120},{STRAWBERRY, 180},{PUMPKIN, 240},{BROCCOLI, 210},{SEEDS, 60}};

Crop::Crop(char c, int x, int y, bool s)
{
	setCChar(c);
	setXPos(x);
	setYPos(y);
	setSolid(s);

	setStage('1', '2', '3', '4');

	time(&planted);
}

char Crop::getStage(int i)
{
	return stage[i];
}

int Crop::getCurrentStage()
{
	return currentStage;
}

time_t Crop::getTime()
{
	return planted;
}

int Crop::getStageDelay()
{
	return stageDelay;
}

void Crop::setStage(char c0, char c1, char c2, char c3)
{
	stage[0] = c0;
	stage[1] = c1;
	stage[2] = c2;
	stage[3] = c3;

	currentStage = 0;
	setCChar(stage[currentStage]);
}

void Crop::setStage(int i, char c)
{
	stage[i] = c;
}

void Crop::nextStage() 
{
	if(currentStage<3)
	{
		currentStage++;
		setCChar(stage[currentStage]);
	}
}

InventoryItem* Crop::getInvItem()
{
	InventoryItem* ii;
	ii = new InventoryItem((getItemType()==SEED) ? DECORATION : getItemType(), getItemName(), ITEM_PRICE[getItemName()]);
	return ii; 
}
