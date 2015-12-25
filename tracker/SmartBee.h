#ifndef SmartBee__H
#define SmartBee__H
#include <string>
#include <vector>
#include <iostream>
#include "twowayms.h"
#include "sprite.h"
#include "ioManager.h"
class ExplodingSprite;
class SmartBee : public Twowayms {
public:
	SmartBee(const std::string&, const std::string&, const std::string&);
	SmartBee(const SmartBee&);
	
        
	virtual void draw() const;
	virtual void update(Uint32 ticks);
	float distance(float x1, float y1, float x2, float y2);
	void goLeft();
  void goRight();
  void goUp();
  void goDown();
  
   void incrSafeDistance() {++safeDistance; }
   void decrSafeDistance() { --safeDistance; }
   float getSafeDistance() { return safeDistance; }
   
protected:
        enum MODE {NORMAL, EVADE};
	MODE currentMode;
        float safeDistance=40.0f;
	
};
#endif
