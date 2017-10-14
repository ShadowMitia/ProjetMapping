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
    ofBackground(200, 200, 0);
    renderPlatform();
    image.draw(0, 0);
    worldsBox2d->draw();
    ofPushMatrix();
    ofTranslate(worldsBox2d->avatars[0]->polygon.getPosition().x - (lightSize / 2), worldsBox2d->avatars[0]->polygon.getPosition().y - (lightSize / 2));
    lightRender.draw();
    ofPopMatrix();
}

void Scene1::renderObjects(){
    //image.draw(0, 0);
}

void Scene1::renderPlatform(){
  //ofBackground(0, 0, 0, 0);
    for (auto &platform : worldsBox2d->platforms)
    {
        ofSetHexColor(0xFF0000);
        platform->ground.draw();
    }
    ofSetColor(ofColor::white);
}

void Scene1::update(){

    lightRender.lights[0].vel.x = worldsBox2d->avatars[0]->polygon.getPosition().x;
    lightRender.lights[0].vel.y = worldsBox2d->avatars[0]->polygon.getPosition().y;
    lightRender.renderLights();

}





void Scene2::draw(){

    ofSetColor(ofColor::white);
    worldsBox2d->draw();
    //lightSystem2D->draw();
}
