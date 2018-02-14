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

/* fonction groupir
 fboTransform.begin();
 ofClear(0,0,0,0);
 transform.begin();
 transform.setUniformTexture("u_texture", fboIni->getTexture(), 0);
 transform.setUniformMatrix3f("matrixX", matrixX);
 transform.setUniformMatrix3f("matrixY", matrixY);
 ofSetColor(ofColor::white, 0);
 //ofDrawRectangle(ofPoint(0,0), 3*160, 3*160);
 transform.end();
 // placement asset
 _sprites->draw();
 fboTransform.end();
*/
