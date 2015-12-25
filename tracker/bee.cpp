#include "bee.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "explodingSprite.h"

Bee::Bee(const std::string& name, const std::string& name1, const std::string& name2)
:Twowayms(name,name1,name2,true)
{}
Bee::Bee(const Bee& s)
	:Twowayms(s)//,strategy(s.strategy)
{

}


void Bee::draw() const {
	Uint32 x = static_cast<Uint32>(X());
	Uint32 y = static_cast<Uint32>(Y());
	getframesonveln()[cFrame]->draw(x, y);
}

void Bee::update(Uint32 ticks) {
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

