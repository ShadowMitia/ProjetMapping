#include "Teleportable.h"
/*

ofVec2f Teleportable::getCenter() const
  {
    return collisionRect.getCenter();
  }


  ofRectangle Teleportable::getCollisionRect() const
  {
    return collisionRect;
  }

  bool Teleportable::inside(ofVec2f pos) const
  {
    return collisionRect.inside(pos);
  }
  ofVec2f Teleportable::getPosition() const
  {
    return ofVec2f(collisionRect.x, collisionRect.y);
  }
*/

ofVec2f Teleportable::getPosition(){
    return polygon.getPosition();
    
}

void Teleportable::setPosition(ofVec2f p){
    polygon.setPosition(p);
};

