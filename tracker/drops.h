#ifndef drops__H
#define drops__H
#include <string>
#include "drawable.h"


class drops : public Drawable {
public:
  drops(const std::string& );
  drops(const drops& s);
  virtual ~drops() { } 
  drops& operator=(const drops&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;

  virtual void update(Uint32 ticks);
int getWorldWidth()const;
float getScale() const { return scale; }

  Vector2f getCenter() const { 
    return Vector2f( X()+frame->getWidth()/2, Y()+frame->getHeight()/2 );
  }
void randomize();
private:
 double scale;
  const Frame * frame;
  
  int getDistance(const drops*) const;

protected:
int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;


};
#endif
