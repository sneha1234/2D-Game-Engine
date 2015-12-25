#include "vector2f.h"
#include "ioManager.h"
#include "aaline.h"

class Hbar {
public:
  Hbar();
  void draw() const;
  void update(Uint32);
  void reset() { clg = tlg; }
bool checkLength();
private:
  SDL_Surface* screen;
  Vector2f start;
  int tlg;
  int clg;
  int thickness;
  int inc;
  float interval;
  int dt;
  const Uint32 BLUE;
  const Uint32 BLACK;
  Hbar(const Hbar&);
  Hbar& operator=(const Hbar&);
 
};
