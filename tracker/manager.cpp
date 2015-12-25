#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "vector2f.h"
#include "multisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "extractSurface.h"
#include "twowayms.h"
#include "player.h"
#include "bee.h"
#include "sound.h"
#include "SmartBee.h"
#include <cmath>
#include <algorithm>
class dropSpriteCompare {
public:
  bool operator()(const drops* lhs, const drops* rhs) {

    return lhs->getScale() < rhs->getScale();
  }
};
void Manager::deletExp(){
std::vector<Twowayms*>::iterator ptr = explodingSprites.begin();
  while ( ptr != explodingSprites.end() ) {
std::cout<<"deleted exp"<<std::endl;
    delete (*ptr);
    ++ptr;
  }


}
Manager::~Manager() { 
  std::vector<Twowayms*>::iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    delete (*ptr);
    ++ptr;
  }
 deletExp();
for (unsigned i = 0; i < drps.size(); ++i) {
    delete drps[i];
  }
  drps.clear();

}

Manager::Manager() :
isReset(false),
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),bcount(0),
  screen( io.getScreen() ),
  world1("back1", Gamedata::getInstance().getXmlInt("back1/factor") ),
 world2("back2", Gamedata::getInstance().getXmlInt("back2/factor") ),
 world3("back3", Gamedata::getInstance().getXmlInt("back3/factor") ),
  viewport( Viewport::getInstance() ),
 
  sprites(),
  killedBees(),
  explodingSprites(),
  currentSprite(),
  drps(),
  healthbar(),
  makeVideo( false ),
  frameCount( 0 ),
  hd(hud::getInstance()),
ghd(ghud::getInstance()),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
gameover(false),
godmode(false)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
unsigned numbt = Gamedata::getInstance().getXmlInt("numbutterflies");
for(int j=0;j<numbt;j++)
  sprites.push_back( new Bee("butterfly","butterfly1","butterfly2"));
unsigned numbees = Gamedata::getInstance().getXmlInt("numbees");
for (unsigned i = 0; i < numbees; ++i) {
  sprites.push_back( 
    new SmartBee("bee","bee1","bee2")
    
  );

}
   
  currentSprite = sprites.begin();

 viewport.setObjectToTrack(&mainPlayer::getInstance());
  makedrops();
 
}

void Manager::makedrops() {
  unsigned numdrops = Gamedata::getInstance().getXmlInt("numdrops");
  drps.reserve( numdrops );
 
  for (unsigned i = 0; i < numdrops; ++i) {

    drps.push_back( new drops("drops") );

  }
  sort(drps.begin(), drps.end(), dropSpriteCompare());
}


void Manager::draw() 
{

world1.draw();

for (unsigned i = 0; i < drps.size()/2; ++i) {
    drps[i]->draw();
  }
world2.draw();

for (unsigned i = drps.size()/2; i < (drps.size()/2+drps.size()/3); ++i) {
    drps[i]->draw();
  }
world3.draw();

for (unsigned i = (drps.size()/2+drps.size()/3); i < drps.size(); ++i) {
    drps[i]->draw();
  }
  clock.draw();

if(!isReset){
mainPlayer::getInstance().draw();}
else{
isReset=false;

}
int i=0;
  std::vector<Twowayms*>::iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
if(!(std::find(killedBees.begin(), killedBees.end(), *ptr) != killedBees.end())){
    (*ptr)->draw();

}
    ++ptr;

  }
i=0;
 ptr = explodingSprites.begin();
  while ( ptr != explodingSprites.end() ) {
if(!(std::find(killedBees.begin(), killedBees.end(), *ptr) != killedBees.end())){
    (*ptr)->draw();

}
    ++ptr;

  }
if (clock.HUDsh)
	{
		std::stringstream ss;
		hd.drawHUD(screen, hd.HUD_POSITION[0], hd.HUD_POSITION[1]);
		io.printMessageAt("Bee Hunting", hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 5);
		io.printMessageAt("Press a - Left", hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 60);
		io.printMessageAt("Press d - Right", hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 75);
		io.printMessageAt("Press w - Up", hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 90);
		io.printMessageAt("Press s - Down", hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 105);
		io.printMessageAt("Press a + Press d - Stop", hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 120);
		io.printMessageAt("Press r - Restart", hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 135);
		io.printMessageAt("Press h - Shoot", hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 150);		
		io.printMessageAt("Press F1 - Toggle HUD", hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 165);
		ss<<mainPlayer::getInstance().bulletListCount();
		io.printMessageAt("BulletList:"+ss.str(), hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 180);
		ss.str("");ss<<mainPlayer::getInstance().freeListCount();
		io.printMessageAt("FreeList:"+ss.str(), hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 195);
		ss.str("");ss<<killedBees.size();
		io.printMessageAt("Bees Killed:"+ss.str(), hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 210);
		ss.str("");ss<<sprites.size()-killedBees.size();
		io.printMessageAt("Bees Remaining:"+ss.str(), hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 225);
		if(godmode)
		io.printMessageAt("GodMode", hd.HUD_POSITION[0] + 5, hd.HUD_POSITION[1] + 240);
		
clock.draw();
	}
if(gameover){
const int HUDX=Gamedata::getInstance().getXmlInt("ghud/loc/x");
const int HUDY=Gamedata::getInstance().getXmlInt("ghud/loc/y");
ghd.drawghud(screen,HUDX ,HUDY);
io.printMessageAt("Game Over", 375, 230);
if(sprites.size()!=killedBees.size()&&clock.getSeconds()>=55)
io.printMessageAt("You Lose", 390, 245);
else if(sprites.size()==killedBees.size())
io.printMessageAt("You Win", 390, 245);
}
healthbar.draw();
viewport.draw();
SDL_Flip(screen);
}


void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  ++currentSprite;
  if ( currentSprite == sprites.end() ) {
    currentSprite = sprites.begin();
  }
  viewport.setObjectToTrack(*currentSprite);
}

void Manager::update() {
clock.update();
Uint32 ticks = clock.getTicksSinceLastFrame();

mainPlayer::getInstance().update(ticks);

std::vector<Twowayms*>::iterator ptr = explodingSprites.begin();
  while ( ptr != explodingSprites.end() ) {
    if(!(std::find(killedBees.begin(), killedBees.end(), *ptr) != killedBees.end()))
    (*ptr)->update(ticks);
    ++ptr;
  }
if(sprites.size()!=killedBees.size()&&clock.getSeconds()<55){

for (unsigned i = 0; i < drps.size(); ++i) {
    drps[i]->update(ticks);
  }

   ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    if(!(std::find(killedBees.begin(), killedBees.end(), *ptr) != killedBees.end()))
    (*ptr)->update(ticks);
    ++ptr;
  }
ptr = explodingSprites.begin();
  while ( ptr != explodingSprites.end() ) {
    if(!(std::find(killedBees.begin(), killedBees.end(), *ptr) != killedBees.end()))
    (*ptr)->update(ticks);
    ++ptr;
  }
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
mainPlayer::getInstance().update(ticks);

ptr = sprites.begin();
while ( ptr != sprites.end() ) {
if(*ptr !=&mainPlayer::getInstance()&& !(std::find(killedBees.begin(), killedBees.end(), *ptr) != killedBees.end())&&!(std::find(explodingSprites.begin(), explodingSprites.end(), *ptr) != explodingSprites.end()))
{
	if ( mainPlayer::getInstance().collidedwithbees(*ptr)&& godmode==false) {
    	  healthbar.update(ticks);
     	
    	}
	if ( mainPlayer::getInstance().bulletscollidedWith(*ptr))
	{
	explodingSprites.push_back(new ExplodingSprite(*ptr));
       killedBees.push_back(*ptr);
	
	}

}
ptr++;
}

if(healthbar.checkLength()){
 mainPlayer::getInstance().explode();
 healthbar.reset();
}
  world1.update();
  world2.update();
  world3.update();
  viewport.update(); // always update viewport last
}
else{

gameover=true;
mainPlayer::getInstance().Playerstop();

viewport.update();
}
}
void Manager::restart() {
healthbar.reset();
killedBees.clear();
deletExp();
explodingSprites.clear();
isReset=true;
mainPlayer::getInstance().setPosition(Vector2f(Gamedata::getInstance().getXmlInt("player/startLoc/x"),Gamedata::getInstance().getXmlInt("player/startLoc/y")));
mainPlayer::getInstance().velocityX(0);
draw();

}
void Manager::play() {
  SDLSound sound;
  SDL_Event event;
  bool done = false;
  clock.start();
  for (unsigned i = 0; i < drps.size(); ++i) {
    drps[i]->randomize();
  }
  while ( not done ) {
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN ||event.type == SDL_PRESSED) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
        if ( keystate[SDLK_t] ) {
          switchSprite();
        }
        if ( keystate[SDLK_g] ) {
          godmode=!godmode;
        }
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDLK_m]) {
          clock.toggleSloMo();
        }
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
       if (keystate[SDLK_F1]){
					clock.HUDsh = !clock.HUDsh;
                                        clock.HUDnohide= !clock.HUDnohide;}

				     if (keystate[SDLK_h]){    
					mainPlayer::getInstance().shoot();sound[0];}
                                     if (keystate[SDLK_x])     
					mainPlayer::getInstance().explode();
                                        if (keystate[SDLK_r])     
					restart();
                                     if (keystate[SDLK_a])     
					mainPlayer::getInstance().Moveleft();
                                        

				
				 if (keystate[SDLK_s])
					mainPlayer::getInstance().Movedown();
                                       
				  if (keystate[SDLK_d])
					mainPlayer::getInstance().Moveright();
                                       
				 if (keystate[SDLK_w]){
                                        mainPlayer::getInstance().Moveup();
					}
                                       
				if (keystate[SDLK_a] && keystate[SDLK_w])
                                {mainPlayer::getInstance().Moveup();
                                        mainPlayer::getInstance().Moveleft();
                                        
                                  }
                                if (keystate[SDLK_a] && keystate[SDLK_s])
                                {       mainPlayer::getInstance().Movedown();
                                        mainPlayer::getInstance().Moveleft();
                                        
                                  }
 if (keystate[SDLK_a] && keystate[SDLK_d])
                                {       mainPlayer::getInstance().Playerstop();
                                        
                                        
                                  }
 if (keystate[SDLK_d] && keystate[SDLK_s])
                                {mainPlayer::getInstance().Movedown();
                                        mainPlayer::getInstance().Moveright();
                                        
                                  }
 if (keystate[SDLK_d] && keystate[SDLK_w])
                                {mainPlayer::getInstance().Moveup();
                                        mainPlayer::getInstance().Moveright();
                                        
                                  }
 if (keystate[SDLK_s] && keystate[SDLK_w])
                                { mainPlayer::getInstance().Playerstop();
                                        
                                  }

                                   
   }
else if(event.type == SDL_KEYUP||event.type == SDL_PRESSED) {
                                     if (keystate[SDLK_a]) {    
					mainPlayer::getInstance().MoveOnlyleft();}
                                        

				
			else	 if (keystate[SDLK_s]){
					mainPlayer::getInstance().MoveOnlydown();}
                                       
			else	  if (keystate[SDLK_d]){
					mainPlayer::getInstance().MoveOnlyright();}
                                       
			else	 if (keystate[SDLK_w]){
                                        mainPlayer::getInstance().MoveOnlyup();}
else{

       mainPlayer::getInstance().Playerstop();}
                                       
				
}
                                 
 }
    draw();
    update();
  }
}

