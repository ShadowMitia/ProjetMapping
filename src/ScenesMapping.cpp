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
    /*
    ofBackground(200, 0, 0, 255);
    //ofDrawBitmapString("1", 50, 50);
    ofSetColor(ofColor::white);
    ofSetLineWidth(1);
    for (int i=0; i<=2000; i+=200) {
        ofDrawLine(i, 0, i, 600);
    }
    for (int i=0; i<=600; i+=200) {
        ofDrawLine(0, i, 2000, i);
    }*/
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