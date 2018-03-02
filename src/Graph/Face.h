//
//  Header.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 03/02/2018.
//
//
#pragma once

#include "ofMain.h"
#include "Constant.h"
#include "Sprite.h"

struct Face{
    int idFace;
    ofRectangle rect;
    Face * matrix[2][9];
    ofMatrix3x3 matrixR[2];

};

class FaceFunction{
public:
    ofMatrix3x3 matrix[3];
    ofShader ShaderLayerToFace;
    ofShader ShaderFaceToLayer;

    ofFbo fboFace;
    
    FaceFunction(){
        fboFace.allocate(160*3, 160*3);
        if(!ShaderLayerToFace.load("passTransform.vert", "layerToFace.frag")) {
            printf("transform.frag\n");
        }
        //fboSortie.allocate(VarConst::WidthWorld2D, VarConst::HeightWorld2D);
        if(!ShaderFaceToLayer.load("passTransform.vert", "faceToLayer.frag")) {
            printf("transformInv.frag\n");
        }
    }
    
    void faceToLayer(ofFbo *layer, int mode){
        layer->begin();
        //ofSetColor(ofColor::white);
        ShaderFaceToLayer.begin();
        ShaderFaceToLayer.setUniform1i("mode", mode);
        ShaderFaceToLayer.setUniformTexture("u_texture", fboFace.getTexture(), 0);
        ShaderFaceToLayer.setUniformTexture("u_texture_src", layer->getTexture(), 1);
        ShaderFaceToLayer.setUniformMatrix3f("matrixX", matrix[0]);
        ShaderFaceToLayer.setUniformMatrix3f("matrixY", matrix[1]);
        ShaderFaceToLayer.setUniformMatrix3f("matrixR", matrix[2]);
        ofDrawRectangle(ofPoint(0,0), layer->getWidth(), layer->getHeight());
        ShaderFaceToLayer.end();
        layer->end();
    }
    void layerToFace(ofTexture texture){
        fboFace.begin();
        ofClear(0,0,0,0);  //Attantion c est pas remis ˆ 0
        ShaderLayerToFace.begin();
        ShaderLayerToFace.setUniformTexture("u_texture", texture, 0);
        ShaderLayerToFace.setUniformMatrix3f("matrixX", matrix[0]);
        ShaderLayerToFace.setUniformMatrix3f("matrixY", matrix[1]);
        ShaderLayerToFace.setUniformMatrix3f("matrixR", matrix[2]);
        ofSetColor(ofColor::white, 0);
        ofDrawRectangle(ofPoint(0,0), 3*160, 3*160);
        ShaderLayerToFace.end();
        fboFace.end();
    }
    void fillMatrix(SpriteObj* _sprite){
        bool i = _sprite->getViewPoint();
        matrix[0].set(_sprite->face->matrix[i][0]->rect.x, _sprite->face->matrix[i][3]->rect.x, _sprite->face->matrix[i][6]->rect.x,
                      _sprite->face->matrix[i][1]->rect.x, _sprite->face->matrix[i][4]->rect.x, _sprite->face->matrix[i][7]->rect.x,
                      _sprite->face->matrix[i][2]->rect.x, _sprite->face->matrix[i][5]->rect.x, _sprite->face->matrix[i][8]->rect.x);
        matrix[1].set(_sprite->face->matrix[i][0]->rect.y, _sprite->face->matrix[i][3]->rect.y, _sprite->face->matrix[i][6]->rect.y,
                      _sprite->face->matrix[i][1]->rect.y, _sprite->face->matrix[i][4]->rect.y, _sprite->face->matrix[i][7]->rect.y,
                      _sprite->face->matrix[i][2]->rect.y, _sprite->face->matrix[i][5]->rect.y, _sprite->face->matrix[i][8]->rect.y);
        matrix[2] = _sprite->face->matrixR[i];
    };
    void fillMatrix(Face* face, int i){
        
        matrix[0].set(face->matrix[i][0]->rect.x, face->matrix[i][3]->rect.x, face->matrix[i][6]->rect.x,
                      face->matrix[i][1]->rect.x, face->matrix[i][4]->rect.x, face->matrix[i][7]->rect.x,
                      face->matrix[i][2]->rect.x, face->matrix[i][5]->rect.x, face->matrix[i][8]->rect.x);
        matrix[1].set(face->matrix[i][0]->rect.y, face->matrix[i][3]->rect.y, face->matrix[i][6]->rect.y,
                      face->matrix[i][1]->rect.y, face->matrix[i][4]->rect.y, face->matrix[i][7]->rect.y,
                      face->matrix[i][2]->rect.y, face->matrix[i][5]->rect.y, face->matrix[i][8]->rect.y);
        matrix[2] =   face->matrixR[i];
    }
};