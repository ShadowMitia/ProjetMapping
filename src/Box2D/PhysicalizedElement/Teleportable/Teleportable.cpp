#include "Teleportable.h"

ofVec2f Teleportable::getPosition(){
    return polygon.getPosition();
}

ofVec2f Teleportable::getVelocity(){
    return polygon.getVelocity();
}
void Teleportable::setPosition(ofVec2f p){
    polygon.setPosition(p);
}
void Teleportable::SetGravityScale(float32 scale){
    polygon.body->SetGravityScale(scale);
}

void Teleportable::setVelocity(ofVec2f v){
    polygon.setVelocity(v);
}