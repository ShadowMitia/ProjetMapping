//
//  ScenesMapping.c
//  ProjetMapping
//
//  Created by FatDazz_mac on 04/08/2017.
//
//

enum  BLENDMODES{BlendNormal = 0, BlendDarkenf = 1};
#include "ScenesMapping.h"


void Scene1::draw()
{
    
    //ofClear(0);
    for (int i=0; i<nbLayer; ++i) {
        layer[i].begin();
        ofClear(0, 0, 0, 0);
        if (i==2) {
            plaforms.draw(0, 0);
        }
        if (i==1) {
        }
        layer[i].end();
    }

    // Affiche tout les sprites
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    for (int i = 0; i<sprites->size(); ++i) {
        if (sprites->at(i)->isActif()) {
            fillMatrix(sprites->at(i));
            fboFace.begin();
            ofClear(0,0,0,0);
            sprites->at(i)->draw();
            fboFace.end();
            faceToLayer(sprites->at(i)->layer,0);
        }

    }

    fillMatrix(sprites->at(0));
    fboFace.begin();
    ofClear(0,0,0,0);
    fboFace.end();
    layerToFace(2);
    
    Light* light = dynamic_cast<Light *>(sprites->at(0));
    lightRender.renderLights(&fboFaceShadow, light);
    
    fboFace.begin();
    ofClear(0,0,0,0);
    //ofBackground(ofColor::black);
    ofPushMatrix();
    ofTranslate(light->getPositionTranform().x - 256/2, light->getPositionTranform().y-256/2);
    fboFaceShadow.draw(0, 0);
    fboFace.end();
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
    faceToLayer(1,1);
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    if (sprites->at(2)->isActif()) {
        fillMatrix(sprites->at(2));
        fboFace.begin();
        ofClear(0,0,0,0);
        fboFace.end();

        layerToFace(2);
        
        Light* light = dynamic_cast<Light *>(sprites->at(2));
        lightRender.renderLights(&fboFaceShadow, light);
        fboFace.begin();
        ofClear(0,0,0,0);
        ofPushMatrix();
        ofTranslate(light->getPositionTranform().x - 256/2, light->getPositionTranform().y-256/2);
        fboFaceShadow.draw(0, 0);
        fboFace.end();
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ZERO);
        faceToLayer(1,1);
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    }
    



    background.draw(0, 0);
    
    ofSetColor(ofColor::white);
    
    for (int i=1; i<nbLayer; ++i) {
        //layer[i].draw(0, 0);
    }
    layer[1].draw(0, 0);

    //layer[2].draw(0, 0);
    
    //layer[3].draw(0,0);
     //worldsBox2d->draw();
    
    //fboFace.draw(0, 0);
    
    //layer[0].draw(0, 0);
    //fboFaceShadow.draw(0, 0);
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
    fboFace.draw(0,0);
}
void Scene1::update()
{
    
}
void Scene1::fillMatrix(SpriteObj *_sprite)
{
    bool i = _sprite->getViewPoint();
    matrix[0].set(_sprite->face->matrix[i][0]->rect.x, _sprite->face->matrix[i][3]->rect.x, _sprite->face->matrix[i][6]->rect.x,
                  _sprite->face->matrix[i][1]->rect.x, _sprite->face->matrix[i][4]->rect.x, _sprite->face->matrix[i][7]->rect.x,
                  _sprite->face->matrix[i][2]->rect.x, _sprite->face->matrix[i][5]->rect.x, _sprite->face->matrix[i][8]->rect.x);
    matrix[1].set(_sprite->face->matrix[i][0]->rect.y, _sprite->face->matrix[i][3]->rect.y, _sprite->face->matrix[i][6]->rect.y,
                 _sprite->face->matrix[i][1]->rect.y, _sprite->face->matrix[i][4]->rect.y, _sprite->face->matrix[i][7]->rect.y,
                 _sprite->face->matrix[i][2]->rect.y, _sprite->face->matrix[i][5]->rect.y, _sprite->face->matrix[i][8]->rect.y);
    matrix[2] = _sprite->face->matrixR[i];

}
void Scene1::faceToLayer(int _layer, int mode)
{
    int i = _layer;
    ofTexture tempTexture;
    if (_layer == 1) {
        tempTexture = layer[_layer].getTexture();
        //layer[_layer].begin();
        //ofClear(0, 0, 0, 0);
        //layer[_layer].end();
    }
    layer[i].begin();
    //ofSetColor(ofColor::white);
    ShaderFaceToLayer.begin();
    ShaderFaceToLayer.setUniform1i("mode", mode);
    ShaderFaceToLayer.setUniformTexture("u_texture", fboFace.getTexture(), 0);
    ShaderFaceToLayer.setUniformTexture("u_texture_src", tempTexture, 1);
    ShaderFaceToLayer.setUniformMatrix3f("matrixX", matrix[0]);
    ShaderFaceToLayer.setUniformMatrix3f("matrixY", matrix[1]);
    ShaderFaceToLayer.setUniformMatrix3f("matrixR", matrix[2]);
    ofDrawRectangle(ofPoint(0,0), layer[_layer].getWidth(), layer[_layer].getHeight());
    ShaderFaceToLayer.end();
    layer[i].end();
    
    if (_layer == 1) {
        
    }
}
void Scene1::layerToFace(int _layer)
{
    fboFace.begin();
    ofClear(0,0,0,0);  //Attantion c est pas remis ˆ 0
    ShaderLayerToFace.begin();
    ShaderLayerToFace.setUniformTexture("u_texture", layer[_layer].getTexture(), 0);
    ShaderLayerToFace.setUniformMatrix3f("matrixX", matrix[0]);
    ShaderLayerToFace.setUniformMatrix3f("matrixY", matrix[1]);
    ofSetColor(ofColor::white, 0);
    ofDrawRectangle(ofPoint(0,0), 3*160, 3*160);
    ShaderLayerToFace.end();
    fboFace.end();
}
void Scene2::draw()
{
    ofSetColor(ofColor::white);
    worldsBox2d->draw();
}