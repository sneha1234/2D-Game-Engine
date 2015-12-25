#include <cmath>
#include "drops.h"
#include "gamedata.h"
#include "frameFactory.h"

drops::drops(const string& n):
  Drawable(n, Vector2f(Gamedata::getInstance().getXmlInt(n+"/loc/x"), Gamedata::getInstance().getXmlInt(n+"/loc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(n+"/speed/x"),
                    Gamedata::getInstance().getXmlInt(n+"/speed/y"))
                   
  ),
 scale(Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlFloat(n+"/scale/min"),
                     Gamedata::getInstance().getXmlFloat(n+"/scale/max"))
  ),
  frame( FrameFactory::getInstance().getScaledFrame(n,scale)),
  frameWidth(Gamedata::getInstance().getXmlInt(n+"/width")),
  frameHeight(Gamedata::getInstance().getXmlInt(n+"/height")),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

drops::drops(const drops& s) :
  Drawable(s),
  scale(s.scale),
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

drops& drops::operator=(const drops& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

void drops::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

int drops::getDistance(const drops *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

int drops::getWorldWidth()const{
return worldWidth;
}
void drops::randomize(){
  static int seedctr = 15;
  srand(++seedctr);
  X(rand() % worldWidth);
  Y(rand() % worldHeight);

}

void drops::update(Uint32 ticks) { 
 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  if(Y()==0||Y()>0 || Y()<worldHeight-frameHeight)
	Y(Y()+incr[1]);
  if(Y()>=worldHeight-frameHeight)
	Y(0);

  
 
}   
 
