#ifndef Bee__H
#define Bee__H
#include <string>
#include <vector>
#include "twowayms.h"
class ExplodingSprite;
class Bee : public Twowayms {
public:
	Bee(const std::string&, const std::string&, const std::string&);
	Bee(const Bee&);
	//virtual ~Bee();
	
	virtual void draw() const;
	virtual void update(Uint32 ticks);
	
	//virtual const Frame* getFrame() const;
	//const std::vector<Frame *> getframesonveln() const;
	
protected:
       
	//std::vector<Frame *> frames;
	//const std::vector<Frame *> oneway;
	//const std::vector<Frame *> otherway;
	//int worldWidth;
	//int worldHeight;

	//unsigned cFrame;
	//unsigned numFrames;
	//unsigned frameInterval;
	//float timeSinceLastFrame;
	//int frameWidth;
	//int frameHeight;
	
	//void advanceFrame(Uint32 ticks);
};
#endif
