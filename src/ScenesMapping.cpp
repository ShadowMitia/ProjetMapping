//
//  ScenesMapping.c
//  ProjetMapping
//
//  Created by FatDazz_mac on 04/08/2017.
//
//

#include "ScenesMapping.h"


void Scene1::draw(){

    ofClear(0);
    ofBackgroundGradient(ofColor(10), ofColor(0));
    
    ofBackground(200, 0, 0, 255);
    //ofDrawBitmapString("1", 50, 50);
    ofSetColor(ofColor::white);
    ofSetLineWidth(1);
    for (int i=0; i<=WidthWord2D; i+=UNIT) {
        ofDrawLine(i, 0, i, HeightWord2D);
    }
    for (int i=0; i<=HeightWord2D; i+=UNIT) {
        ofDrawLine(0, i, WidthWord2D, i);
    }
    //worldsBox2d->draw();
    ofSetColor(ofColor::white);
    for (auto &platforms: worldsBox2d->platforms) {
        if (platforms->shape->bVisible) {
            platforms->ground.draw();
        }
    }
    lightSystem2D->draw();
}

void Scene1::update(){
    
    
}