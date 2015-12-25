#include <iostream>
#include "ioManager.h"
#include "aaline.h"

class ghud {
public:
static ghud& getInstance();
void drawghud(SDL_Surface*, int, int) const;
const int ghud_WIDTH;
const int ghud_HEIGHT;
const Vector2f ghud_POSITION;
private:
ghud();
ghud(const ghud&);
ghud& operator=(const ghud&);
};
