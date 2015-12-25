#include "player.h"
#include "gamedata.h"
#include "explodingSprite.h"
mainPlayer& mainPlayer::getInstance()
{
	static mainPlayer mainplayer = mainPlayer("player", "playerRight", "playerLeft");
	return mainplayer;
}

mainPlayer::mainPlayer(const std::string& name, const std::string& name1, const std::string& name2)
	: Twowayms(name, name1, name2),
	istop(true),
        ct(0),
        spx(Gamedata::getInstance().getXmlInt(name + "/speedX")),
        spy(Gamedata::getInstance().getXmlInt(name + "/speedY")),
       bulletpl("bullet"),
       minSpeed(220),
       strategy( new MidPointCollisionStrategy ), explosion(NULL)
{

	Playerstop();
}

mainPlayer::mainPlayer(const mainPlayer& s)
	: Twowayms(s),
	istop(s.istop),
        ct(s.ct),
        spx(s.spx),
        spy(s.spy),
       bulletpl(s.bulletpl),
       minSpeed(s.minSpeed),
       strategy( s.strategy ),
 explosion(s.explosion)
{
	Playerstop();
}
int mainPlayer::bulletListCount(){
return bulletpl.bulletCount();}
int mainPlayer::freeListCount(){
return bulletpl.freeCount();}
mainPlayer::~mainPlayer()
{
	//delete strategy;
}

void mainPlayer::draw() const
{ 
if (explosion) {
    explosion->draw();
    return;
  }
	Twowayms::draw();
	bulletpl.draw();
        

}

void mainPlayer::shoot() { 
  float x ;
  float y = Y()+frameHeight/2;
   if(getframesonveln()==oneway)
{
    x = X()+frameWidth;
 bulletpl.shoot( Vector2f(x, y), 
 Vector2f(minSpeed+velocityX(), 0));
}
   else{
    x = X()-frameWidth;
 bulletpl.shoot( Vector2f(x, y), 
 Vector2f(minSpeed+abs(velocityX()), 0));
}  

 
}


void mainPlayer::update(Uint32 ticks)
{ 

if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
  }
if(getframesonveln()==oneway)
    bulletpl.setFlagD(true);
 else if (getframesonveln()==otherway)
    bulletpl.setFlagD(false);

bulletpl.update(ticks);
Twowayms::advanceFrame(ticks);
	if (!istop)
	{

		
		float XIncrement = getVelocity()[0] * static_cast<float>(ticks)* 0.001;
 if (X()+ XIncrement > worldWidth - frameWidth){
      X(worldWidth - frameWidth);velocityX(-1);}
    else if (X()+ XIncrement < 0)
      {X(0);velocityX(1);//turn arround at window ends
}
    else
      X(X() + XIncrement);

 
frames=getframesonveln();

float YIncrement = getVelocity()[1] * static_cast<float>(ticks)* 0.001;
if (Y() + YIncrement > (worldHeight-(frameHeight+10))){
      Y(worldHeight-(frameHeight+10));
}
    else if (Y() + YIncrement < 0){
      Y(0);
}
    else{
      Y(Y() + YIncrement);
}

}

}
bool mainPlayer::collidedwithbees(const Drawable* obj) const {
  const Drawable* playerCollided = static_cast<Drawable*>(&mainPlayer::getInstance());
  return strategy->execute(*playerCollided,*obj);
   }
bool mainPlayer::bulletscollidedWith(const Drawable* obj) const{
return bulletpl.collidedWith(obj);
}
void mainPlayer::explode() { 
  if ( explosion ) return;
  explosion = new ExplodingSprite(static_cast<Twowayms*>(&mainPlayer::getInstance()));
  
}

void mainPlayer::Playerstop()
{
	istop = true;
	velocityX(0);
        velocityY(0);
   
}
void mainPlayer::Moveright()
{
	istop = false;
	if (X() < worldWidth - frameWidth)
	{
		velocityX(mVelocityX());
	}
       


}
void mainPlayer::Moveleft()
{
	istop = false;
	if (X() > 0)
	{
		velocityX(-mVelocityX());
	}




}
void mainPlayer::Moveup()
{istop = false;

	if (Y()<0){
	 velocityY(0);}
        else{
         velocityY(-mVelocityY());
}
	


	
}
void mainPlayer::Movedown()
{

	istop = false;
  if (Y() > worldHeight - (frameHeight+10)){
    velocityY(worldHeight - (frameHeight+10));
}

  else{
    velocityY(mVelocityY());
}


}
void mainPlayer::MoveOnlyright()
{
	istop = false;
	if (X() < worldWidth - frameWidth)
	{
		velocityX(mVelocityX());
	}
       else if (X() == worldWidth - frameWidth)
         velocityX(-1);

velocityY(0);

}
void mainPlayer::MoveOnlyleft()
{
	istop = false;
	if (X() > 0)
	{
		velocityX(-mVelocityX());
	}
else if (X() == 0)
velocityX(1);

velocityY(0);

}
void mainPlayer::MoveOnlyup()
{istop = false;

	if (Y()<0){
	 velocityY(0);}
        else{
         velocityY(-mVelocityY());
}
velocityX(0);	


	
}
void mainPlayer::MoveOnlydown()
{

	istop = false;
  if (Y() > worldHeight - (frameHeight+10)){
    velocityY(worldHeight - (frameHeight+10));
}

  else{
    velocityY(mVelocityY());
}

velocityX(0);
}
