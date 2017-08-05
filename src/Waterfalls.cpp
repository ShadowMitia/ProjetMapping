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
    class Water* water = new class Water;
    water->water.addVertexes(polyWater);
    water->water.setPhysics(3.0, 0.53, 0.1);
    ofVec2f point;
    point.x = ofRandom(spawn.x+3, spawn.x +spawn.width -3);
    point.y = ofRandom(spawn.y+3, spawn.y +spawn.width -3);
    water->water.setPosition(point);
    water->water.create(box2d->getWorld());
    timeDead  = ofGetSeconds();
    
}

void Waterfalls::despawnWater(){
    
    for (int i = 0; i  < waters.size(); i++) {
        if (timeDead + ofGetSeconds() > 20 ) {
            waters[i]->water.destroy();
            waters.erase(waters.begin() + i);
        }
    }
}