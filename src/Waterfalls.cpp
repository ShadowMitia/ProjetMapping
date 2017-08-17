//
//  waterfalls.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//

#include "Waterfalls.h"



Waterfalls::Waterfalls(ofxBox2d* _box2d):box2d(_box2d){
    
}

void Waterfalls::update(){
    
    
}


void Waterfalls::spawnWater(){

    
    ofVec2f point;
    point.x = ofRandom(spawn.x+3, spawn.x +spawn.width -3);
    point.y = ofRandom(spawn.y+3, spawn.y +spawn.width -3);
    ofVec2f position = ofVec2f(point);
    ofVec2f velocity = ofVec2f(ofRandom(-200, 200), ofRandom(-200, 200));
    waters.createParticle(position, velocity);
    timeDead  = ofGetSeconds();
    
}

void Waterfalls::despawnWater(){
    /*
    for (int i = 0; i  < waters.size(); i++) {
        if (timeDead + ofGetSeconds() > 20 ) {
            waters[i]->water.destroy();
            waters.erase(waters.begin() + i);
        }
    }*/
}