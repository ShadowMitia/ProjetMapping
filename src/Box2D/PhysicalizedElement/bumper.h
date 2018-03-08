//
//  bumper.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 08/03/2018.
//
//

#pragma once
#include "ofxBox2d.h"
#include "Ladder.h"
#include "Avatar.h"
#include "ofMain.h"
#include "Constant.h"
#include "PhysicalizedElement.h"

class bumper: public PhysicalizedElement {
public:
    ofxBox2dCircle objet;
    bumper(b2World *b2dworld){
        objet.setup( b2dworld, 0, 0, 4);
    };
    
     void contactStart(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite) override;
     void contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
};