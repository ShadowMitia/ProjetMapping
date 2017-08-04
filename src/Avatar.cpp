//
//  Avatar.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//
#include "Avatar.h"


//////////////////////////////////////////// LoadPoints //////////////////////////////
std::vector <ofPoint> loadPoints(std::string file) {
    std::vector <ofPoint> pts;
	std::vector <std::string>  ptsStr = ofSplitString(ofBufferFromFile(file).getText(), ",");

    for (unsigned int i = 0; i < ptsStr.size(); i += 2) {
        float x = ofToFloat(ptsStr[i]);
        float y = ofToFloat(ptsStr[i+1]);
        pts.push_back(ofPoint(x, y));
    }

    return pts;
}
/////////////////////////////////////////// LoadPoints FIN ////////////////////////////
void Avatar::create(b2World* _b2World, ofx::LightSystem2D * _lightSystem2D){
    lightSystem2D = _lightSystem2D;
    std::vector <ofPoint> pts = loadPoints("Avatar.dat");
    polygon.addVertices(pts);
    polygon.triangulatePoly();
    polygon.setPhysics(3.0, 0.53, 0.1);
    //polygon.ofxBox2dBaseShape::body->SetGravityScale((Float32) 0.0); je ne comprend pas pourquoi cela ne marche pas 
    polygon.create(_b2World);
    ////  Light2D ////////
    light = std::make_shared<ofx::Light2D>();
    //light->setViewAngle(ofDegToRad(121));
    //light->setColor(ofColor::azure);
    light->setRadius(700);
    //light->setBleed(0.1);
    lightSystem2D->add(light);
}

void Avatar::update()
{
    light->setPosition(polygon.getPosition());
    
    
    rect.set(polygon.getBoundingBox().getStandardized() + polygon.getPosition());

    if (clone) {
        clone->polygon.setVelocity(polygon.getVelocity());
        clone->polygon.setPosition(polygon.getPosition() + cloneTranslation);
    }
    if (polygon.getVelocity() == ofVec2f()) /// <<  c est moche, je ne cromprend pas;
    {
        jumping = false;
    }
    jumping = false; // saut tout le temp
};

void Avatar::draw() {
    polygon.draw();

	/*
		ofPushStyle();
		ofSetColor(ofColor::cyan, 50);
		auto diff = ofVec2f(rect.width / 2, rect.height / 2);
		ofDrawRectangle(polygon.getPosition() - diff, polygon.getBoundingBox().width, polygon.getBoundingBox().height);
		ofPopStyle();
	*/

    if (clone) {
        clone->draw();
    }
}

void Avatar::createClone(ofVec3f cloneTranslation) {
    if (clone) { return; }
    this->cloneTranslation = cloneTranslation;
    clone = std::make_unique<Avatar>();
    //clone->polygon.setPhysics(polygon.density, polygon.bounce, polygon.friction);
    clone->polygon.addVertices(polygon.getVertices());
    //clone->polygon.triangulatePoly();
    clone->polygon.setPhysics(polygon.density, polygon.bounce, polygon.friction);
    clone->polygon.setVelocity(polygon.getVelocity());
    clone->polygon.create(polygon.getWorld());
    clone->polygon.setPosition(100, 100);

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
        if (!jumping){
        polygon.setVelocity(-10, polygon.body->GetLinearVelocity().y);
        }
        else{
            polygon.addForce({-200,0}, 1);
        }

    }
    else if (_key == OF_KEY_RIGHT) {
        if (!jumping){
            polygon.setVelocity(10, polygon.body->GetLinearVelocity().y);
        }
        else{
            polygon.addForce({200,0}, 1);
        }
    }
    else if (_key == ' ')
    {
        if (!jumping)
        {
            //float impulse = polygon.body->GetMass() * 500;
            polygon.addForce({ 0, -2000 }, 1.0);
        }
        jumping = true;
    }

}
