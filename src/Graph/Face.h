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

#define nbFace  13

struct Face{
    int idFace;
    ofRectangle rect;
    Face * matrix[2][9];
    ofMatrix3x3 matrixR[2];

};

class FaceFunctionZ{
public:
    
    ofMatrix3x3 matrix[3];
    ofFbo fboFace;
    float size;
    FaceFunctionZ(){
        size = 320;
        fboFace.allocate(3*size,3*size);
    }
    
    void fillMatrix(SpriteObj* _sprite){
        bool i = _sprite->ViewPoint; //_sprite->getViewPoint();
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
    void fillMatrixTo160(SpriteObj* _sprite){
        bool i = _sprite->ViewPoint; //_sprite->getViewPoint();
        matrix[0].set(_sprite->face->matrix[i][0]->rect.x/2, _sprite->face->matrix[i][3]->rect.x/2, _sprite->face->matrix[i][6]->rect.x/2,
                      _sprite->face->matrix[i][1]->rect.x/2, _sprite->face->matrix[i][4]->rect.x/2, _sprite->face->matrix[i][7]->rect.x/2,
                      _sprite->face->matrix[i][2]->rect.x/2, _sprite->face->matrix[i][5]->rect.x/2, _sprite->face->matrix[i][8]->rect.x/2);
        matrix[1].set(_sprite->face->matrix[i][0]->rect.y/2, _sprite->face->matrix[i][3]->rect.y/2, _sprite->face->matrix[i][6]->rect.y/2,
                      _sprite->face->matrix[i][1]->rect.y/2, _sprite->face->matrix[i][4]->rect.y/2, _sprite->face->matrix[i][7]->rect.y/2,
                      _sprite->face->matrix[i][2]->rect.y/2, _sprite->face->matrix[i][5]->rect.y/2, _sprite->face->matrix[i][8]->rect.y/2);
        matrix[2] = _sprite->face->matrixR[i];
    };
    void fillMatrixTo160(Face* face, int i){
        
        matrix[0].set(face->matrix[i][0]->rect.x/2, face->matrix[i][3]->rect.x/2, face->matrix[i][6]->rect.x/2,
                      face->matrix[i][1]->rect.x/2, face->matrix[i][4]->rect.x/2, face->matrix[i][7]->rect.x/2,
                      face->matrix[i][2]->rect.x/2, face->matrix[i][5]->rect.x/2, face->matrix[i][8]->rect.x/2);
        matrix[1].set(face->matrix[i][0]->rect.y/2, face->matrix[i][3]->rect.y/2, face->matrix[i][6]->rect.y/2,
                      face->matrix[i][1]->rect.y/2, face->matrix[i][4]->rect.y/2, face->matrix[i][7]->rect.y/2,
                      face->matrix[i][2]->rect.y/2, face->matrix[i][5]->rect.y/2, face->matrix[i][8]->rect.y/2);
        matrix[2] =   face->matrixR[i];
    };


};
class FaceFunction :public FaceFunctionZ{
public:
    
    ofShader ShaderLayerToFace;
    ofShader ShaderFaceToLayer;
    ofShader ShaderFaceToLayer2;

    
    void setup(float _size){
        size = _size;
        fboFace.clear();
        fboFace.allocate(size*3, size*3);
        if(!ShaderLayerToFace.load("passTransform.vert", "layerToFaceTO160.frag")) {
            printf("transform.frag\n");
        }
        //fboSortie.allocate(VarConst::WidthWorld2D, VarConst::HeightWorld2D);
        if(!ShaderFaceToLayer2.load("passFaceToLayerTO160.vert", "faceToLayerTO160.frag")) {
            printf("transformInv.frag\n");
        }

    }
    
    FaceFunction(){
        
        if(!ShaderLayerToFace.load("passTransform.vert", "layerToFace.frag")) {
            printf("transform.frag\n");
        }
        //fboSortie.allocate(VarConst::WidthWorld2D, VarConst::HeightWorld2D);
        if(!ShaderFaceToLayer2.load("passFaceToLayer.vert", "faceToLayer2.frag")) {
            printf("transformInv.frag\n");
        }
    }
    

    void faceToLayer(ofFbo *layer, int mode){
        ofVec3f posAng;
        layer->begin();
        for (int i=0; i<9; ++i) {
            posAng = ofVec3f(matrix[0][i], matrix[1][i], matrix[2][i]);
            ShaderFaceToLayer2.begin();
            ShaderFaceToLayer2.setUniform1i("mode", mode);
            ShaderFaceToLayer2.setUniform1i("X",  (int) i/3);
            ShaderFaceToLayer2.setUniform1f("Y", (i/3.0 - i/3)*3);
            ShaderFaceToLayer2.setUniformTexture("u_texture", fboFace.getTexture(), 0);
            ShaderFaceToLayer2.setUniformTexture("u_texture_src", layer->getTexture(), 1);
            ShaderFaceToLayer2.setUniform3f("posAng", posAng);
            ofDrawRectangle(ofPoint(0,0), size, size);
            ShaderFaceToLayer2.end();
        }
        layer->end();

    }
    
    void layerToFace(ofTexture texture){
        fboFace.begin();
        ofClear(0,0,0,0);  //Attantion c est pas remis ˆ 0
        //ofBackground(ofColor::blue);
        ShaderLayerToFace.begin();
        ShaderLayerToFace.setUniformTexture("u_texture", texture, 0);
        ShaderLayerToFace.setUniformMatrix3f("matrixX", matrix[0]);
        ShaderLayerToFace.setUniformMatrix3f("matrixY", matrix[1]);
        ShaderLayerToFace.setUniformMatrix3f("matrixR", matrix[2]);
        //ofSetColor(ofColor::white, 0);
        ofDrawRectangle(ofPoint(0,0), 3*size, 3*size);
        ShaderLayerToFace.end();
        //texture.draw(0,0, 3*320, 3*320);
        fboFace.end();
    }
    
    void layerToFace(ofFbo texture){
        fboFace.begin();
        ofClear(0,0,0,0);  //Attantion c est pas remis ˆ 0
        //ofBackground(ofColor::blue);
        ShaderLayerToFace.begin();
        ShaderLayerToFace.setUniformMatrix3f("matrixX", matrix[0]);
        ShaderLayerToFace.setUniformMatrix3f("matrixY", matrix[1]);
        ShaderLayerToFace.setUniformMatrix3f("matrixR", matrix[2]);
        ShaderLayerToFace.setUniformTexture("u_texture", texture.getTexture(), 0);

        //ofSetColor(ofColor::white, 0);
        ofDrawRectangle(ofPoint(0,0), 3*size, 3*size);
        ShaderLayerToFace.end();
        //texture.draw(0,0, 3*320, 3*320);
        fboFace.end();
    }
    

};
class FaceFunction1D: public FaceFunctionZ{
public:
    
    ofMatrix3x3 matrixId;
    ofMatrix3x3 matrixR;
    ofShader ShaderLayerToFace1D;
    ofShader ShaderFaceToLayer1D;

    
    FaceFunction1D(){
        fboFace.allocate(320*nbFace, 320);
    }
    
    
    void layerToFace1D(ofTexture texture){
        fboFace.begin();
        ofClear(0,0,0,0);  //Attantion c est pas remis ˆ 0
        ShaderLayerToFace1D.begin();
        ShaderLayerToFace1D.setUniformMatrix3f("matrixX", matrixId);
        ShaderLayerToFace1D.setUniformMatrix3f("matrixR",  matrixR);
        ShaderLayerToFace1D.setUniformTexture("u_texture", texture, 0);
        ofDrawRectangle(ofPoint(0,0), 3*size, 3*size);
        ShaderLayerToFace1D.end();
        fboFace.end();
    }
    
    void layerToFace(ofFbo texture){
        fboFace.begin();
        ofClear(0,0,0,0);  //Attantion c est pas remis ˆ 0
        ShaderLayerToFace1D.begin();
        ShaderLayerToFace1D.setUniformMatrix3f("matrixX", matrixId);
        ShaderLayerToFace1D.setUniformMatrix3f("matrixR",  matrixR);
        ShaderLayerToFace1D.setUniformTexture("u_texture", texture.getTexture(), 0);
        ofDrawRectangle(ofPoint(0,0), 3*size, 3*size);
        ShaderLayerToFace1D.end();
        fboFace.end();
    }
    
    void faceToLayer(ofFbo *layer, int mode){
        ofVec3f posAng;
        layer->begin();
        for (int i=0; i<9; ++i) {
            posAng = ofVec3f(matrixId[i], 0.0, matrixR[i]);
            ShaderFaceToLayer1D.begin();
            ShaderFaceToLayer1D.setUniform1i("mode", mode);
            ShaderFaceToLayer1D.setUniform1i("X",  (int) i/3);
            ShaderFaceToLayer1D.setUniform1f("Y", (i/3.0 - i/3)*3);
            ShaderFaceToLayer1D.setUniformTexture("u_texture", fboFace.getTexture(), 0);
            ShaderFaceToLayer1D.setUniformTexture("u_texture_src", layer->getTexture(), 1);
            ShaderFaceToLayer1D.setUniform3f("posAng", posAng);
            ofDrawRectangle(ofPoint(0,0), size, size);
            ShaderFaceToLayer1D.end();
        }
        layer->end();
    
    }
    
    void fillMatrix1D(SpriteObj* _sprite){
        bool i = _sprite->ViewPoint;
        matrixId.set(_sprite->face->matrix[i][0]->idFace, _sprite->face->matrix[i][3]->idFace, _sprite->face->matrix[i][6]->idFace,
                     _sprite->face->matrix[i][1]->idFace, _sprite->face->matrix[i][4]->idFace, _sprite->face->matrix[i][7]->idFace,
                     _sprite->face->matrix[i][2]->idFace, _sprite->face->matrix[i][5]->idFace, _sprite->face->matrix[i][8]->idFace);
        matrixR =_sprite->face->matrixR[i];
    }
    
    
};