//
//  ObjSignageSign.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 29/03/2018.
//
//


#pragma once
#include "ofMain.h"
#include "Constant.h"
#include "PhysicalizedElement.h"
#include "Sprite.h"

class ObjSignageSign: public PhysicalizedElement{
public:
    ObjectGame polygon;
    ObjSignageSign *linkedSign[2];
    
    ObjSignageSign(b2World* _b2World, ofVec2f v, ofVec2f p){
        std::vector<ofPoint> pts = loadPoints("Trampline.dat");
        polygon.addVertices(pts);
        //polygon.triangulatePoly();
        polygon.setPhysics(0, 0, 0);
        //polygon.create(box2d);
        polygon.create(_b2World, false);
        polygon.setPosition(p);
        polygon.body->SetFixedRotation(true);
        
        
        b2Filter filter;

        filter.categoryBits = Category::SignageSign;
        filter.maskBits = Category::AVATAR;
        polygon.body->GetFixtureList()->SetFilterData(filter);
        polygon.setData(new dataSprite());
        
        dataSprite* data = (dataSprite*)polygon.getData();
        data->sprite = Sprite::SignageSign;
        data->physicalizedElement = this;
        
        polygon.body->SetGravityScale(0.0);
        vitesse = v;
    }
    ofVec2f vitesse;
    void setLinkedSign( ObjSignageSign * SignageSign_1, ObjSignageSign * SignageSign_2){
    };
    
    virtual void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;

};