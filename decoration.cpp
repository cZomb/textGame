#include "decoration.h"

Decoration::Decoration(char c, std::string s, int x, int y, bool b, int p)
{
	setCChar(c);
	setSName(s);
	setXPos(x);
	setYPos(y);
	setSolid(b);
	setPrice(p);
}

