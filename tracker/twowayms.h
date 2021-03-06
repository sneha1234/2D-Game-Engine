#ifndef Twowayms__H
#define Twowayms__H
#include <string>
#include <vector>
#include "drawable.h"

class Twowayms : public Drawable {
public:
	Twowayms(const std::string&, const std::string&, const std::string&);
	Twowayms(const std::string&, const std::string&, const std::string&,bool flag);
	Twowayms(const Twowayms&);
	//virtual ~Twowayms();

	virtual void draw() const;
	//virtual void reset(float xx,float yy);
	virtual void update(Uint32 ticks);
	virtual const Frame* getFrame() const;
	const std::vector<Frame *> getframesonveln() const;
        

	
protected:
	std::vector<Frame *> frames;
	const std::vector<Frame *> oneway;
	const std::vector<Frame *> otherway;
	int worldWidth;
	int worldHeight;

	unsigned cFrame;
	unsigned numFrames;
	unsigned frameInterval;
	float timeSinceLastFrame;
	int frameWidth;
	int frameHeight;
	void advanceFrame(Uint32 ticks);
};
#endif
