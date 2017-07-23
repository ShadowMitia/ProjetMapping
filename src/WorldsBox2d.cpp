//
//  WorldsBox2d.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//

#include "WorldsBox2d.h"

void WorldsBox2d::initWordldsBox2d(){
    
    world.init();
    world.setGravity(0, 10);
    //world.createGround(0,0,1000, 600);
    world.createBounds(ofRectangle(0, 0, 1000, 600));
    world.setFPS(60.0);
    world.registerGrabbing();

    /////// Portal ///////
    portals.push_back( std::shared_ptr<Portal>(new Portal(Portal::Orientation::HORIZONTAL, 50, 525, 50, 75, world)) );
    portals.push_back( std::shared_ptr<Portal>(new Portal(Portal::Orientation::HORIZONTAL, 200, 525, 50, 75, world)) );
    
    portals[0]->linkTo(portals[1].get());
    ///// Portal /////////

}
void WorldsBox2d::creatCircle(float _x,float _y){
    float r = ofRandom(4, 20);
    circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
    circles.back().get()->setPhysics(0.0, 0.53, 0.1);
    circles.back().get()->setup(world.getWorld(), _x, _y, r);
}
void WorldsBox2d::drawCircles(){
    for(int i=0; i<circles.size(); i++) {
        ofFill();
        ofSetHexColor(0xf6c738);
        circles[i].get()->draw();
    }
    for (auto const &avatar : avatars) {
        avatar->draw();
    }
    for (auto const &portal : portals) {
        portal->draw();
    }
}
void WorldsBox2d::updateWorldsBox2d(){
    for (auto const &avatar : avatars) {
        avatar->update();
    }
    for (auto const &portal : portals) {
        portal->update(avatars);
    }
    world.update();
}

void WorldsBox2d::creatAvatar(){
    avatars.push_back(shared_ptr<class Avatar>(new class Avatar));
    avatars.back()->create(world.getWorld());
    avatars.back()->polygon.setPosition(ofGetMouseX(), ofGetMouseY());
}




