#include "Hbar.h"
#include "gamedata.h"
Hbar::Hbar() :
  screen(IOManager::getInstance().getScreen()),
  start(Vector2f(Gamedata::getInstance().getXmlInt("hbar/locX"), Gamedata::getInstance().getXmlInt("hbar/locY"))), 
  tlg(Gamedata::getInstance().getXmlInt("hbar/totalLength")), 
  clg(Gamedata::getInstance().getXmlInt("hbar/totalLength")), 
  thickness(Gamedata::getInstance().getXmlInt("hbar/thickness")), 
  inc(Gamedata::getInstance().getXmlInt("hbar/increments")),
  interval(Gamedata::getInstance().getXmlInt("hbar/interval")),
  dt(0),
  BLUE( SDL_MapRGB(screen->format, 0x00, 0xff, 0xff) ),
  BLACK( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) ) {
}

void Hbar::draw() const {
  Draw_AALine(screen, start[0], start[1], 
                      start[0]+tlg, start[1], 
                      thickness, BLACK);
  
  Draw_AALine(screen, start[0], start[1]-8, 
                      start[0]+tlg, start[1]-8, 
                      1.0, BLACK);
  Draw_AALine(screen, start[0], start[1]+8, 
                      start[0]+tlg, start[1]+8, 
                      1.0, BLACK);

  Draw_AALine(screen, start[0]-1, start[1]-8, 
                      start[0]-1, start[1]+8, 
                      2.0, BLACK);
  Draw_AALine(screen, start[0]+tlg+1, start[1]-8, 
                      start[0]+tlg+1, start[1]+8, 
                      2.0, BLACK);
 Draw_AALine(screen, start[0], start[1], 
                      start[0]+clg, start[1], 
                      thickness, BLUE);
}



void Hbar::update(Uint32 ticks) {
  dt += ticks;
  if ( clg > 0 && dt > interval ) {
    dt = 0;
    clg -= inc;
  }
}
bool Hbar::checkLength(){
 return clg<=0;
}
