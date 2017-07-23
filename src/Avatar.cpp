//
//  Avatar.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//

#include "Avatar.h"
//////////////////////////////////////////// LoadPoints //////////////////////////////
vector <ofPoint> loadPoints(string file) {
    vector <ofPoint> pts;
    vector <string>  ptsStr = ofSplitString(ofBufferFromFile(file).getText(), ",");
    for (int i=0; i<ptsStr.size(); i+=2) {
        float x = ofToFloat(ptsStr[i]);
        float y = ofToFloat(ptsStr[i+1]);
        pts.push_back(ofPoint(x, y));
    }
    return pts;
}
/////////////////////////////////////////// LoadPoints FIN ////////////////////////////
void Avatar::setup(b2World* _b2World){
    vector <ofPoint> pts = loadPoints("Avatar.dat");
    polygon.addVertices(pts);
    polygon.triangulatePoly();
    polygon.setPhysics(3.0, 0.53, 0.1);
    polygon.create(_b2World);
}
void Avatar::update()
{
    rect.set(this->polygon.getPosition(),10,10); // modif ici + 10 10 a changer.

    if (clone) {
        clone->polygon.setVelocity(this->polygon.getVelocity());
        clone->polygon.setPosition(this->polygon.getPosition() + cloneTranslation);
    }
};

void Avatar::draw() {
    polygon.draw();
    if (clone) {
        ofSetColor(ofColor::red);
        clone->draw();
    }
}

void Avatar::createClone(ofVec3f cloneTranslation) {
    if (clone) { return; }
    this->cloneTranslation = cloneTranslation;
    clone = std::make_unique<Avatar>();
    clone->polygon.setPhysics(this->polygon.density, this->polygon.bounce, this->polygon.friction);
    clone->polygon.addVertices(polygon.getVertices());
    clone->polygon.triangulatePoly();
    clone->polygon.setPhysics(polygon.density, polygon.bounce, polygon.friction);
    clone->polygon.create(polygon.getWorld());
    clone->polygon.setVelocity(polygon.getVelocity());
}
void Avatar::removeClone() {
    clone = nullptr;
    cloneTranslation.zero();
}
void Avatar::teleportTo(ofVec2f destination) {
    polygon.setPosition(destination);
    
}
void Avatar::teleportToClone() {
    auto pos = clone->polygon.getPosition();
    polygon.setPosition(pos);
}
bool Avatar::hasClone() { return clone ? true : false; }

void Avatar::handleInputs(int _key){
    if (_key == OF_KEY_LEFT) {
        polygon.setVelocity(-3, 0);
    }
    else if (_key == OF_KEY_RIGHT) {
        polygon.setVelocity(3, 0);
    }

}
