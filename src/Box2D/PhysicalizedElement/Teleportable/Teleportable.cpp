#include "Teleportable.h"

ofVec2f Teleportable::getPosition(){
    return polygon.getPosition();
}
void Teleportable::setPosition(ofVec2f p){
    polygon.setPosition(p);
}
void Teleportable::SetGravityScale(float32 scale){
    polygon.body->SetGravityScale(scale);
}

