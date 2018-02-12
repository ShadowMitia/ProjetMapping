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

std::vector<ofPoint> loadPoints(const std::string& file)
{
    std::vector<ofPoint> pts;
    std::vector <std::string>  ptsStr = ofSplitString(ofBufferFromFile(file).getText(), ",");
    for (unsigned int i = 0; i < ptsStr.size(); i += 2) {
        float x = ofToFloat(ptsStr[i]);
        float y = ofToFloat(ptsStr[i+1]);
        pts.push_back(ofPoint(x, y));
    }
    return pts;
}