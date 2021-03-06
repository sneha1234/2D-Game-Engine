#include "gamedata.h"
#include "aaline.h"
#include "hud.h"

hud& hud::getInstance()
{
	static hud hudInstance;
	return hudInstance;
}
hud::hud():
HUD_WIDTH(Gamedata::getInstance().getXmlInt("hud/width")),
HUD_HEIGHT(Gamedata::getInstance().getXmlInt("hud/height")),
HUD_POSITION(Vector2f(Gamedata::getInstance().getXmlInt("hud/loc/x"), Gamedata::getInstance().getXmlInt("hud/loc/y")))
{ }

void hud::drawHUD(SDL_Surface* screen, int x, int y) const
{
	const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
	Draw_AALine(screen, x, y + HUD_HEIGHT / 2, x + HUD_WIDTH, y + HUD_HEIGHT / 2, HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff / 2);
	
}
