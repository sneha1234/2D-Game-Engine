#include "twowayms.h"
#include "gamedata.h"
#include "frameFactory.h"

void Twowayms::advanceFrame(Uint32 ticks)
{
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval)
	{
		cFrame = (cFrame + 1) % numFrames;
		timeSinceLastFrame = 0;
	}
}

const Frame* Twowayms::getFrame() const
{
	return getframesonveln()[cFrame];
}

const std::vector<Frame *> Twowayms::getframesonveln() const
{
	if (velocityX() > 0)
		return oneway;
	else if (velocityX() < 0)
		return otherway;
	else
		return frames;
}

Twowayms::Twowayms(const std::string& name, const std::string& name1, const std::string& name2)
	:Drawable(name, Vector2f(Gamedata::getInstance().getXmlInt(name + "/startLoc/x"), Gamedata::getInstance().getXmlInt(name + "/startLoc/y")), Vector2f(Gamedata::getInstance().getXmlInt(name + "/speedX"), Gamedata::getInstance().getXmlInt(name + "/speedY"))),
	frames(),
	oneway(FrameFactory::getInstance().getFrames(name1)),
	otherway(FrameFactory::getInstance().getFrames(name2)),
	worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
	worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
	cFrame(0),
	numFrames(Gamedata::getInstance().getXmlInt(name + "/frames")),
	frameInterval(Gamedata::getInstance().getXmlInt(name + "/frameInterval")),
	timeSinceLastFrame(0),
	frameWidth(oneway[0]->getWidth()),
	frameHeight(oneway[0]->getHeight())
	
{
	frames = oneway;
}
Twowayms::Twowayms(const std::string& name, const std::string& name1, const std::string& name2,bool flag)
	:Drawable(name, Vector2f(Gamedata::getInstance().getXmlInt(name + "/startLoc/x"), Gamedata::getInstance().getXmlInt(name + "/startLoc/y")+(rand()%2?1:-1)*Gamedata::getInstance().getRandInRange(
                    0,Gamedata::getInstance().getXmlInt(name+"/startLoc/y"))), Vector2f(Gamedata::getInstance().getXmlInt(name + "/speedX")+(rand()%2?1:-1)*Gamedata::getInstance().getRandInRange(
                    0,Gamedata::getInstance().getXmlInt(name+"/speedX")), Gamedata::getInstance().getXmlInt(name + "/speedY")+(rand()%2?1:-1)*Gamedata::getInstance().getRandInRange(
                    0,Gamedata::getInstance().getXmlInt(name+"/speedY")) ) ),
	frames(),
	oneway(FrameFactory::getInstance().getFrames(name1)),
	otherway(FrameFactory::getInstance().getFrames(name2)),
	worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
	worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
	cFrame(0),
	numFrames(Gamedata::getInstance().getXmlInt(name + "/frames")),
	frameInterval(Gamedata::getInstance().getXmlInt(name + "/frameInterval")),
	timeSinceLastFrame(0),
	frameWidth(oneway[0]->getWidth()),
	frameHeight(oneway[0]->getHeight())
	
{
	frames = oneway;
}


Twowayms::Twowayms(const Twowayms& s)
	:Drawable(s),
	frames(s.frames),
	oneway(s.oneway),
	otherway(s.otherway),
	worldWidth(s.worldWidth),
	worldHeight(s.worldHeight),
	cFrame(s.cFrame),
	numFrames(s.numFrames),
	frameInterval(s.frameInterval),
	timeSinceLastFrame(s.timeSinceLastFrame),
	frameWidth(s.frameWidth),
	frameHeight(s.frameHeight)
	
{

}

void Twowayms::draw() const {
	Uint32 x = static_cast<Uint32>(X());
	Uint32 y = static_cast<Uint32>(Y());
	getframesonveln()[cFrame]->draw(x, y);
}

void Twowayms::update(Uint32 ticks) {
	advanceFrame(ticks);

	Vector2f incr = getVelocity() * static_cast<float>(ticks)* 0.001;
	setPosition(getPosition() + incr);

	if (Y() < 0) {
		velocityY(abs(velocityY()));
	}
	if (Y() > worldHeight - frameHeight) {
		velocityY(-abs(velocityY()));
	}

	if (X() < 0) {
		velocityX(abs(velocityX()));
	}
	if (X() > worldWidth - frameWidth) {
		velocityX(-abs(velocityX()));
	}

}

