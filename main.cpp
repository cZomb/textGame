/* main file where the magic happens */

// files and libraries to include
#include "main.h"

// main thread of program
int main() 
{
	gameStart();	// initialize values
	getch(); // wait for player input

	// main game loop
	while(gameLoop)
	{
		handleKeys(); // handle keyboard input
		update(); // update value
		draw(); // draw the screen
	}

	endwin(); // close window and clear memory buffer

	return 0; // program completed properly, return 0;
}

// start of game; initialization
void gameStart() 
{
	use_env(false);

	initscr(); // initialize the screen
	cbreak();
	noecho();

	curs_set(0); // turn the cursor off

	refresh(); // refresh the window to apply changes

	itemCursor = 0; // set default inventory cursor position

	// test console color capability
	if(!has_colors())
	{
		endwin();
		printf("Your terminal does not support color");
		return;
	}

	// initialize colors
	start_color();

	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_BLACK,COLOR_GREEN);
	init_pair(3,COLOR_WHITE,COLOR_BLUE);
	init_pair(4,COLOR_YELLOW,COLOR_BLUE);
	
	init_pair(5,COLOR_BLACK,COLOR_YELLOW);
	init_pair(8,COLOR_YELLOW,COLOR_WHITE);

	init_pair(6,COLOR_BLACK,COLOR_WHITE);
	init_pair(7,COLOR_WHITE,COLOR_BLACK);

	// initialize player object
	player = new Player(SCR_MID_X, SCR_MID_Y);

	// initialize objects
	// setup the first building exterior
	for(int i = 1; i<15; i++)
	{
		for(int j = 1; j<7; j++)
		{
			// draw the door
			if(j==6 && (i==7 || i==8))
			{
				buildingOut.push_back(new Object(DOOR_CHAR, i, j, false));
			}
			else
			{
				buildingOut.push_back(new Object(WALL_CHAR, i, j, true));
			}
		}
	}

	// setup the first building interior
	for(int i = 1; i<15; i++)
	{
		for(int j = 1; j<7; j++)
		{
			// draw the door
			if(j==6 && (i==7 || i==8))
			{
				buildingIn.push_back(new Object(DOOR_CHAR, i, j, false));
			}
			// draw everything else
			else
			{
				if(j == 1 || j == 6)
				{
					buildingIn.push_back(new Object(WALL_CHAR, i, j, true));
				} else
				{
					if(i == 1 || i == 14)
					{
						buildingIn.push_back(new Object(WALL_CHAR, i, j, true));
					}
				}
			}
		}
	}

	// setup water tiles
	int waterX = 26;

	for(int i = 0; i<24; i++)
	{
		if(i==6) { waterX++; } else
			if(i==7) { waterX++; } else
				if(i==10) { waterX++; } else
					if(i==15) { waterX--; } else
						if(i==19) { waterX++; } else
							if(i>=21) 
							{ 
								waterX+=2;
								water.push_back(new Object(WATER_CHAR, waterX+4, i, true));
							} 

		if(i!=12 && i!=13)
		{
			water.push_back(new Object(WATER_CHAR, waterX, i, true));
			water.push_back(new Object(WATER_CHAR, waterX+1, i, true));
			water.push_back(new Object(WATER_CHAR, waterX+2, i, true));
			water.push_back(new Object(WATER_CHAR, waterX+3, i, true));
		} else
		{
			bridge.push_back(new Object(BRIDGE_CHAR, waterX, i, false));
			bridge.push_back(new Object(BRIDGE_CHAR, waterX+1, i, false));
			bridge.push_back(new Object(BRIDGE_CHAR, waterX+2, i, false));
			bridge.push_back(new Object(BRIDGE_CHAR, waterX+3, i, false));
		}
	}

	// setup farm objects
	for(int i = 1; i < 6; i+=2)
	{
		for(int j = 15; j < 21; j+=2)
		{
			farm.push_back(new Object(FARM_CHAR, i, j, false));
			farm.push_back(new Object(FARM_CHAR, i+9, j, false));
		}
	}

	// setup inventory menu stuff
	// add 5 bags of seeds to inventory at start
	for(int i = 0; i<5; i++)
	{
		inventory[i] = new InventoryItem(SEED, SEEDS, 120);
	}

	// setup decoration stuff
	decor.push_back(new Decoration('T', "Test0", 40, 5, false, 480));
	decor[0]->Object::setColor(COLOR_WALL);

	// print startup message and start the game
	attron(COLOR_PAIR(1));

	mvprintw(SCR_MID_Y, SCR_MID_X-(strlen(startMsg)/2), startMsg); // print start message 
	refresh(); // refresh window

	attron(COLOR_PAIR(2));
}

void gameEnd()
{
	// break the game loop 
	gameLoop = false;
}

void cycle()
{
	handleKeys(); // keyboard input
	update(); // update values
	draw(); // redraw screen
}

void handleKeys()
{
	// handle keyboard input
	if(nodelay(stdscr, 1)==ERR)
	{
		// do stuff when player isn't touching the keyboard
	}

	int command = getch(); // get player input

	// test normal player input/control
	if(player->getState()==NORMAL)
	{
		switch (command) 
		{
		case LEFT_KEY:
			player->move(LEFT);
			break;
		case RIGHT_KEY:
			player->move(RIGHT);
			break;
		case UP_KEY:
			// test door collisions with main house
			if(player->getLoc() == OUTSIDE)
			{
				for(Object* wall: buildingOut)
				{
					if(wall->getChar() == DOOR_CHAR)
					{
						if(player->collides(wall))
						{
							player->setLoc(HOUSE);
						}
					}
				}
			} 
			player->move(UP);
			break;
		case DOWN_KEY:
			if(player->getLoc() == HOUSE)
			{
				for(Object* wall: buildingIn)
				{
					if(wall->getChar() == DOOR_CHAR)
					{
						if(player->collides(wall))
						{
							player->setLoc(OUTSIDE);
						}
					}
				}
			}
			player->move(DOWN);
			break;
		case ITEM_KEY:
			// open item menu
			player->setState(ITEM_MENU);
			break;
		case ACTION_KEY:
			// 1 check if player is on a crop
			// 2 if so, check if it is in stage 4
			// 3 check if an inventory slot is free
			// 4 create inventory object
			// 5 delete crop
			// 6 reset farm tile
			
			for(int c = 0; c < crop.size(); c++)
			{
				if(player->collides(crop[c]))
				{
					if(crop[c]->getCurrentStage() >= 3)
					{
						for(int i = 0; i < MAX_ITEM_SIZE; i++)
						{
							if(inventory[i] == NULL)
							{
								//inventory[i] = new InventoryItem(SEED, SEEDS, 120);
								 inventory[i] = crop[c]->getInvItem();
								crop.erase(crop.begin()+c);

								for(int f = 0; f < farm.size(); f++)
								{
									if(player->collides(farm[f]))
									{
										farm[f]->setOccupied(false);
										break;
									}
								}
								break;
							}
						}
					}
					break;
				}
			}

			// check decorations
			// 1 did player collide with a decoration
			// 2 is inventory slot free
			// 3 create inventory object
			// 4 delete decoration
			// 5 reset tile

			for(int d = 0; d < decor.size(); d++)
			{
				if(player->collides(decor[d]))
				{
					for(int i = 0; i < MAX_ITEM_SIZE; i++)
					{
						if(inventory[i] == NULL)
						{
							inventory[i] = new InventoryItem(DECORATION, decor[d]->getItemName(), decor[d]->getBuyPrice());
							inventory[i]->setColor(decor[d]->Object::getColor());

							attron(COLOR_PAIR(COLOR_MENU));
							mvprintw(decor[d]->getYPos(), decor[d]->getXPos(), " ");

							decor.erase(decor.begin()+d);
							break;
						}
					}

					break;
				}
			}

			break;
		}
	} else
	if(player->getState()==ITEM_MENU)
	{
		// handle moving around the item menu
		switch (command)
		{
			case DOWN_KEY:
				if(itemCursor>=9)
				{
					itemCursor=0;
				} 
				else
				{
					itemCursor++;
				}
				break;
			case UP_KEY:
				if(itemCursor<=0)
				{
					itemCursor=9;
				}
				else
				{
					itemCursor--;
				}
				break;
			// action key pressed (default 'f')
			// handle inventory menu control
			case ACTION_KEY:
				if(inventory[itemCursor]!=NULL)
				{
					if(inventory[itemCursor]->getItemType()==SEED)
					{
						for(int i = 0; i<farm.size(); i++)
						{
							if(player->collides(farm[i]))
							{
								if(!farm[i]->getOccupied())
								{
									farm[i]->setOccupied(true);
									inventory[itemCursor]=NULL;

									Crop* temp = new Crop('1', player->getXPos(), player->getYPos(), false);
									temp->setColor(COLOR_FARM);

									crop.push_back(temp);

									break;
								}
							}
						}
					} else
					if(inventory[itemCursor]->getItemType()==DECORATION)
					{
						InventoryItem* d = inventory[itemCursor];
						decor.push_back(new Decoration(d->getSName().at(0), d->getSName(), player->getXPos(), player->getYPos(), false, d->getColor()));

						delete inventory[itemCursor];
						inventory[itemCursor] = NULL;
					}

					player->setState(NORMAL);
					clear();
				}
				break;
			case ITEM_KEY:
				player->setState(NORMAL);
				clear();
				break;
		}
	}
}

void update()
{
	// if player is inside building, dont draw roof
	// if player is outside building, draw the roof
	if(player->getLoc()==OUTSIDE)
	{

		for(Object* w: buildingOut)
		{
			if(w->getChar()!=DOOR_CHAR)
				player->collides(w);
		}
		for(Object* w: water)
		{
			player->collides(w);
		}
	}

	if(player->getLoc()==HOUSE)
	{
		for(Object* w: buildingIn)
		{
			if(w->getChar()!=DOOR_CHAR)
				player->collides(w);
		}
	}

	// update current time
	time_t now;
	time(&now);

	// update crop objects staging based on current time vs time planted
	for(Crop* c: crop)
	{
		if(c->getCurrentStage()==0)
		{
			if(difftime(now, c->getTime()) > c->getStageDelay())
			{
				c->nextStage();
			}
		} else
		if(c->getCurrentStage()==1)
		{
			if(difftime(now, c->getTime()) > (c->getStageDelay()*2))
			{
				c->nextStage();
			}
		} else
		if(c->getCurrentStage()==2)
		{
			if(difftime(now, c->getTime()) > (c->getStageDelay()*3))
			{
				c->nextStage();
			}
		} else
		if(c->getCurrentStage()==3)
		{
			if(difftime(now, c->getTime()) > (c->getStageDelay()*4))
			{
				c->nextStage();
			}
		} 
	}
}

void draw()
{
	// draw decorations
	for(Decoration* d: decor)
	{
		d->cDraw(stdscr, d->Object::getColor());
	}

	if(player->getLoc() == OUTSIDE)
	{
		// draw first house exterior
		attron(COLOR_PAIR(COLOR_WALL));
		for(Object* wall: buildingOut)
		{
			wall->draw(stdscr);
		}
	} 
	else
	if(player->getLoc() == HOUSE)
	{
		// draw inside of house
		attron(COLOR_PAIR(COLOR_WALL));
		for(Object* wall: buildingIn)
		{
			wall->draw(stdscr);
		}
	}

	// draw river
	attron(COLOR_PAIR(COLOR_WATER));
	for(Object* w: water)
	{
		w->draw(stdscr);
	}

	// draw bridge
	attron(COLOR_PAIR(COLOR_BRIDGE));
	for(Object* b: bridge)
	{
		b->draw(stdscr);
	}

	// draw farm tiles
	attron(COLOR_PAIR(COLOR_FARM));
	for(Object* f: farm)
	{
		f->draw(stdscr);
	}

	// draw crops if they exist
	for(Crop* c: crop)
	{
		c->cDraw(stdscr, COLOR_FARM_INV);
	}
	
	// draw player
	attron(COLOR_PAIR(COLOR_PLAYER));
	player->draw(stdscr);

	// if item menu is open, draw it
	if(player->getState()==ITEM_MENU)
	{
		// clear background of menu
		for(int i = SCR_MID_Y-(INV_MENU_HEIGHT/2); i<SCR_MID_Y+(INV_MENU_HEIGHT/2);i++)
		{
			if(itemCursor+SCR_MID_Y-(INV_MENU_HEIGHT/2)==i)
			{
				attron(COLOR_PAIR(COLOR_CURSOR));
			} else
			{
				attron(COLOR_PAIR(COLOR_MENU));
			}
			move(i, SCR_MID_X-(INV_MENU_WIDTH/2));
			whline(stdscr, ' ', INV_MENU_WIDTH);
		}

		attron(COLOR_PAIR(COLOR_MENU));
	
		// draw each edge of the menu
		move(SCR_MID_Y-(INV_MENU_HEIGHT/2)-1, SCR_MID_X-(INV_MENU_WIDTH/2)-1);
		whline(stdscr, '-', INV_MENU_WIDTH+2);

		move(SCR_MID_Y+(INV_MENU_HEIGHT/2), SCR_MID_X-(INV_MENU_WIDTH/2)-1);
		whline(stdscr, '-', INV_MENU_WIDTH+2);

		move(SCR_MID_Y-(INV_MENU_HEIGHT/2), SCR_MID_X-(INV_MENU_WIDTH/2)-1);
		wvline(stdscr, '|', INV_MENU_HEIGHT);

		move(SCR_MID_Y-(INV_MENU_HEIGHT/2), SCR_MID_X+(INV_MENU_WIDTH/2));
		wvline(stdscr, '|', INV_MENU_HEIGHT);

		// cycle through player inventory array[10]
		// if not null:
		// 1) move() to proper print location
		// 2) set appropriate color
		// 3) print items to the window
		for(int i = 0; i < MAX_ITEM_SIZE; i++)
		{
			if(inventory[i]!=NULL)
			{	
				if(itemCursor==i)
				{
					attron(COLOR_PAIR(COLOR_CURSOR));
				}
				else
				{
					attron(COLOR_PAIR(COLOR_MENU));
				}

				move(SCR_MID_Y-(INV_MENU_HEIGHT/2)+i,SCR_MID_X-(INV_MENU_WIDTH/2));
				printw("%s",inventory[i]->getSName().c_str());
			}
		}
	}

	refresh();
}
