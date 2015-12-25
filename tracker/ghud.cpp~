#include "gamedata.h"
#include "aaline.h"
#include "ghud.h"

ghud& ghud::getInstance()
{
	static ghud ghudInstance;
	return ghudInstance;
}
ghud::ghud():
ghud_WIDTH(Gamedata::getInstance().getXmlInt("ghud/width")),
ghud_HEIGHT(Gamedata::getInstance().getXmlInt("ghud/height")),
ghud_POSITION(Vector2f(Gamedata::getInstance().getXmlInt("ghud/loc/x"), Gamedata::getInstance().getXmlInt("ghud/loc/y")))
{ }

void ghud::drawghud(SDL_Surface* screen, int x, int y) const
{
	const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
	Draw_AALine(screen, x, y + ghud_HEIGHT / 2, x + ghud_WIDTH, y + ghud_HEIGHT / 2, ghud_HEIGHT, 0xff, 0xff, 0xff, 0xff / 2);
	
}
