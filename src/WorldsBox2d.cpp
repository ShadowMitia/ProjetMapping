//
//  WorldsBox2d.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//

#include "WorldsBox2d.h"

void WorldsBox2d::initWordldsBox2d(){
    
    world_1.init();
    world_1.setFPS(60);
    world_1.setGravity(0, 10);
    world_1.createBounds(bounds_1);
    world_1.registerGrabbing();
    
}
void WorldsBox2d::creatCircle(float _x,float _y){
    float r = ofRandom(4, 20);
    circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
    circles.back().get()->setPhysics(3.0, 0.53, 0.1);
    circles.back().get()->setup(world_1.getWorld(), _x, _y, r);
}

void WorldsBox2d::drawCircles(){
    for(int i=0; i<circles.size(); i++) {
        ofFill();
        ofSetHexColor(0xf6c738);
        circles[i].get()->draw();
    }
}
void WorldsBox2d::updateWorldsBox2d(){
    world_1.update();
    cout << "ici"<< endl;
    //world_2.update();

}



