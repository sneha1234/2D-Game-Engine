#include <iostream>
#include <cmath>
#include "ioManager.h"
#include "bulletpool.h"

bulletpool::~bulletpool() {
  delete strategy;
}

bulletpool::bulletpool(const std::string& n) :
  name(n),
  strategy( new MidPointCollisionStrategy ),
  frameInterval(Gamedata::getInstance().getXmlInt(name+"/bulletInterval")),
  timeSinceLastFrame( 0 ),
  bulletList(),
  freeList(),dflag(true)
{ }

bulletpool::bulletpool(const bulletpool& b) :
  name(b.name),
  strategy(b.strategy),
  frameInterval(b.frameInterval),
  timeSinceLastFrame( b.timeSinceLastFrame ),
  bulletList(b.bulletList), 
  freeList(b.freeList),dflag(b.dflag)
{ }

bool bulletpool::collidedWith(const Drawable* obj) const {
  std::list<Bullet>::iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
    if ( strategy->execute(*ptr, *obj) ) {
      freeList.push_back(*ptr);
      ptr = bulletList.erase(ptr);
      return true;
    }
    ++ptr;
  }
  return false;
}

void bulletpool::shoot(const Vector2f& position, const Vector2f& velocity) {
	if (timeSinceLastFrame > frameInterval) {
    if ( freeList.empty() ) {
      Bullet b(position, velocity,name);
      b.setFlag(dflag);
      bulletList.push_back( b );
    }
    else {
      Bullet b = freeList.front();
      freeList.pop_front();
      b.reset();
      b.setVelocity(velocity);
      b.setPosition(position);
      b.setFlag(dflag);
      bulletList.push_back( b );
    }
		timeSinceLastFrame = 0;
	}
}

void bulletpool::draw() const { 

  std::list<Bullet>::const_iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
    ptr->draw();
    ++ptr;
  }
}

void bulletpool::update(Uint32 ticks) { 
       
	timeSinceLastFrame += ticks;
  std::list<Bullet>::iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
    ptr->update(ticks);
    if (ptr->goneTooFar()) { 
      freeList.push_back(*ptr);
      ptr = bulletList.erase(ptr);
      
    }   
    else ++ptr;
  }
}
