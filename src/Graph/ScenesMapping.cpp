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
    
    //ofClear(0);
    for (int i=0; i<nbLayer; ++i) {
        layer[i].begin();
        ofClear(0, 0, 0, 0);
        layer[i].end();
    }
    //transform.setFboIni(layer);
    
    //transform.update(sprites->at(0));
    //transform.update(sprites->at(1));
    
    //transform.fboSortie.draw(0, 0);
    //ofBackground(200, 200, 0);
    //renderPlatform();
    
    ////////
    
    fillMatrix(sprites->at(0));
    fboFace.begin();
    ofClear(0,0,0,0);
    sprites->at(0)->draw();
    fboFace.end();
    faceToLayer(sprites->at(0)->layer);
    fillMatrix(sprites->at(1));
    fboFace.begin();
    ofClear(0,0,0,0);
    sprites->at(1)->draw();
    fboFace.end();
    faceToLayer(sprites->at(1)->layer);
    
    ///////
    background.draw(0, 0);
    worldsBox2d->draw();
    ofSetColor(ofColor::white);
    
    for (int i=0; i<nbLayer; ++i) {
        layer[i].draw(0, 0);
    }
    
    //transform.fboTransform.draw(0, 0);
    
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

void Scene1::fillMatrix(SpriteObj *_sprite){
    matrix[0].set(_sprite->face->matrix[0][0]->rect.x, _sprite->face->matrix[0][3]->rect.x, _sprite->face->matrix[0][6]->rect.x,
                  _sprite->face->matrix[0][1]->rect.x, _sprite->face->matrix[0][4]->rect.x, _sprite->face->matrix[0][7]->rect.x,
                  _sprite->face->matrix[0][2]->rect.x, _sprite->face->matrix[0][5]->rect.x, _sprite->face->matrix[0][8]->rect.x);
    matrix[1].set(_sprite->face->matrix[0][0]->rect.y, _sprite->face->matrix[0][3]->rect.y, _sprite->face->matrix[0][6]->rect.y,
                 _sprite->face->matrix[0][1]->rect.y, _sprite->face->matrix[0][4]->rect.y, _sprite->face->matrix[0][7]->rect.y,
                 _sprite->face->matrix[0][2]->rect.y, _sprite->face->matrix[0][5]->rect.y, _sprite->face->matrix[0][8]->rect.y);
    matrix[2] = _sprite->face->matrixR[0];

}
void Scene1::faceToLayer(int _layer){
    layer[_layer].begin();
    ofSetColor(ofColor::white);
    transformInv.begin();
    transformInv.setUniformTexture("u_texture", fboFace.getTexture(), 0);
    transformInv.setUniformMatrix3f("matrixX", matrix[0]);
    transformInv.setUniformMatrix3f("matrixY", matrix[1]);
    transformInv.setUniformMatrix3f("matrixR", matrix[2]);
    ofDrawRectangle(ofPoint(0,0), layer[_layer].getWidth(), layer[_layer].getHeight());
    transformInv.end();
    layer[_layer].end();
}

void Scene2::draw()
{
    ofSetColor(ofColor::white);
    worldsBox2d->draw();
}