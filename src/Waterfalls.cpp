//
//  waterfalls.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//

#include "Waterfalls.h"



Waterfalls::Waterfalls(ofxBox2d* _box2d):box2d(_box2d){
    waters.setParticleFlag(b2ParticleFlag::b2_waterParticle);
    waters.setup(_box2d->getWorld() , 20000, 30.0, 2.0, 4.0, ofColor::red);
    spawnWater();
}

void Waterfalls::update(){
    
    if (ofGetFrameNum()% 15 == 0) {
        for (int i = 0 ; i<10; i++) {
            ofVec2f point;
            point.x = ofRandom(spawn.x+3, spawn.x +spawn.width -3);
            point.y = ofRandom(spawn.y+3, spawn.y +spawn.height -3);
            ofVec2f position = ofVec2f(point);
            //ofVec2f position = ofVec2f(spawn.x + i*10,spawn.y+spawn.height);
            //ofVec2f velocity = ofVec2f(ofRandom(-2, 2), ofRandom(-2, 2));
            ofVec2f velocity = ofVec2f(0,0);
            ofColor color;
            int hue = int(ofGetFrameNum() / 4.0) % 255;
            color.setHsb(hue, 180, 200);
            waters.setColor(color);
            waters.createParticle(position, velocity);
        }
    }
}


void Waterfalls::spawnWater(){
    spawn.set(50, 10, 50, 20);
    
}

void Waterfalls::draw(){
    ofSetColor(ofColor::aliceBlue);
    ofDrawRectangle(spawn);
    ofSetColor(ofColor::white);
    waters.draw();
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