//
//  ScenesMapping.c
//  ProjetMapping
//
//  Created by FatDazz_mac on 04/08/2017.
//
//

#include "ScenesMapping.h"

void Scene1::draw()
{
    ofClear(0);
    
    drawMap.begin();
    //ofClear(0, 0, 0, 0);
    ofBackground(200, 200, 0);
    background.draw(0, 0);
    drawMap.end();
    
    transform.setFboIni(&drawMap);
    
    transform.update(sprites->at(0));


    
    

    //transform.fboSortie.draw(0, 0);
    //ofBackground(200, 200, 0);
    //renderPlatform();
    background.draw(0, 0);
    drawMap.draw(0, 0);
    transform.fboTransform.draw(0, 0);
    worldsBox2d->draw();
    // creation du mask pour les ombres
    /*mask.begin();
    ofBackground(0, 0, 0);
    for (std::size_t i = 0; i < worldsBox2d->avatars.size(); i++) {
        lightRender.lights[i].vel.x = worldsBox2d->avatars[i]->polygon.getPosition().x;
        lightRender.lights[i].vel.y = worldsBox2d->avatars[i]->polygon.getPosition().y;
        lightRender.radius = 50.0;
        lightRender.renderLights();
        ofPushMatrix();
        ofTranslate(worldsBox2d->avatars[i]->polygon.getPosition().x - (lightSize / 2), worldsBox2d->avatars[i]->polygon.getPosition().y - (lightSize / 2));
        lightRender.draw();
        ofPopMatrix();
    }
    mask.end();

    //mask.draw(0,0);*/
}

void Scene1::renderObjects()
{
    //image.draw(0, 0);
}

void Scene1::renderPlatform()
{
  //ofBackground(0, 0, 0, 0);
    
    for (auto &platform : worldsBox2d->platforms)
    {
        ofSetHexColor(0xFF0000);
        platform->ground.draw();
    }
    ofSetColor(ofColor::white);
}

void Scene1::update()
{

}

void Scene2::draw()
{
    ofSetColor(ofColor::white);
    worldsBox2d->draw();
}
