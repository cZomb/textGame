#ifndef MAIN_H
#define MAIN_H

// include main libraries
#include <ncurses.h> // -lncurses in terminal when compiling
#include <cstring>
#include <list>
#include <unistd.h>
#include <vector>
#include <time.h>

#include "object.h" // handles objects the player interacts with
#include "player.h" // stores values for player character
#include "crop.h"
#include "inventoryitem.h"
#include "decoration.h"

const int SCR_WIDTH = 80; // screen width
const int SCR_HEIGHT = 24; // screen height

const int SCR_MID_X = SCR_WIDTH / 2; // center x coord
const int SCR_MID_Y = SCR_HEIGHT / 2; // center y coord

const int INV_MENU_HEIGHT = 10; // menu holds 10 items by default
const int INV_MENU_WIDTH = 14; // item menu width

const int MAX_ITEM_SIZE = 10;

bool gameLoop = true;

time_t timer;

int itemCursor; // default item menu cursor postion

const char* startMsg = "Press the Arrow Keys to Move!"; // start message

Player* player; // player object

InventoryItem* inventory[MAX_ITEM_SIZE]; 

std::list<Object*> buildingOut;
std::list<Object*> buildingIn;
std::list<Object*> water;
std::list<Object*> bridge;
std::vector<Object*> farm;
std::vector<Crop*> crop;
std::vector<Decoration*> decor;

const int COLOR_WALL = 1;
const int COLOR_PLAYER = 2;
const int COLOR_WATER = 3;
const int COLOR_BRIDGE = 4;
const int COLOR_FARM = 5;
const int COLOR_FARM_INV = 8;

const int COLOR_MENU = 7;
const int COLOR_CURSOR = 6;

// define keyboard input constants for getch();
const int LEFT_KEY = 68;
const int RIGHT_KEY = 67;
const int UP_KEY = 65;
const int DOWN_KEY = 66;

const int ITEM_KEY = 105; // i key
const int ACTION_KEY = 102; // f key 

// character constants
const char WALL_CHAR = '#';
const char DOOR_CHAR = ' ';
const char WATER_CHAR = 'W';
const char FARM_CHAR = 'F';
const char BRIDGE_CHAR = 'B';

void gameStart();
void gameEnd();

void cycle();
void handleKeys();
void update();
void draw();

#endif
