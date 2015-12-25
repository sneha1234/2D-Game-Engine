#include <iostream>
#include <cmath>
#include "bullet.h"
#include "collisionStrategy.h"
#include "drawable.h"
extern int flag;

bool Bullet::collidedWith(const Sprite* obj) const {
  return Sprite::collidedWith(obj);
}


void Bullet::update(Uint32 ticks) { 

 Vector2f pos = getPosition();
  Sprite::update(ticks);

  float incr = getVelocity()[0] * static_cast<float>(ticks) * 0.001;
  


  if(dirflag==true && (X() + incr)<=(getWorldWidth()-frameWidth-10) &&(X() + incr)>=frameWidth)
{
 velocityX(abs(velocityX()));
   X(X() + incr);
  
}
  else if(dirflag==false && (X() + incr)>=frameWidth && (X() + incr)<=(getWorldWidth()-frameWidth)){
   velocityX(-(abs(velocityX()) ));
   X(X() + incr);
  
}

    distance += ( hypot(X()-pos[0], Y()-pos[1]) );
  if (distance > maxDistance ||(X()<=frameWidth)||(X()>=(getWorldWidth()-frameWidth))) 
{

tooFar = true;
}
} 
