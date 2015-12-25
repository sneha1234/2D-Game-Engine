#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  
  ticks(0),
frames(0),
  lasTticks(0),
  totalTicks(0),
  started(false), 
  paused(false), 
  sloMo(false), 
  HUDsh(true),
  HUDnohide(false),
  isReset(false),
  resetTicks(0),
  sumOfTicks(SDL_GetTicks()),
  pos( Gamedata::getInstance().getXmlInt("clock/locX"),
       Gamedata::getInstance().getXmlInt("clock/locY"))
  {
  start();
}

void Clock::draw() const { 
if(HUDsh){
  IOManager::getInstance().
    printMessageValueAt("Seconds: ", getSeconds(), pos[0]+3, pos[1]+22);
  IOManager::getInstance().
    printMessageValueAt("fps: ", getFps(), pos[0]+3, pos[1]+42);
}
}

void Clock::update() { 
if ( paused ) return;
++frames;

unsigned int delay=0;
unsigned int frameCap=Gamedata::getInstance().getXmlInt("frameCap");
bool isCap=Gamedata::getInstance().getXmlBool("framesAreCapped");
  totalTicks = SDL_GetTicks()-resetTicks;
  ticks = totalTicks - lasTticks;

if(isCap && ticks<(unsigned int)(1000.0/frameCap))
{
delay=(1000.0/frameCap)- ticks;
SDL_Delay(delay);
totalTicks = SDL_GetTicks()-resetTicks;
}
ticks+=delay;
sumOfTicks+= totalTicks-lasTticks;
lasTticks=totalTicks;
if (getSeconds() < Gamedata::getInstance().getXmlInt("hud/time") && HUDnohide)
HUDsh = false;
	
if(getSeconds() > Gamedata::getInstance().getXmlInt("hud/time") && !HUDnohide)
HUDsh = false;
}
unsigned int Clock::getTicksSinceLastFrame() const {
  return ticks;
}

void Clock::toggleSloMo() {
  sloMo = ! sloMo;
}

int Clock::getFps() const { 
if(sloMo)return 1;
  if (getSeconds() > 0 )
{
 return frames/getSeconds();
}
	return 0;


}

void Clock::start() { 
  started = true; 
  paused = false; 
}
void Clock::reset(){
isReset=true;
  resetTicks+=sumOfTicks;
ticks=0;

frames=0,
  lasTticks=0;
  totalTicks=0;
  started=false; 
  paused=false;
  sloMo=false; 
  HUDsh=true;
  HUDnohide=false;
  sumOfTicks=0;
std::cout<<"clock reset ticks="<<ticks<<" getSeconds()"<<getSeconds()<<std::endl;
}
void Clock::pause() { 
  
}

void Clock::unpause() { 
  
}

