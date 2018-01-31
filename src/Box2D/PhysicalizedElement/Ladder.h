//
//  Ladder.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 21/08/2017.
//
//

#pragma once
#include "ofMain.h"
#include "Constant.h"
#include "Avatar.h"

class ObjectPlatformLadder: public ofxBox2dPolygon{
public:
    void create(b2World * b2dworld);
};

class ObjectLadder:public ofxBox2dPolygon{
public:
    void create(b2World * b2dworld);
};


class Ladder: public PhysicalizedElement{
public:
    ObjectLadder polygon;
    void create(b2World* _b2World, ofPolyline _groundLine);
    void draw(){
        b2Fixture *f = polygon.body->GetFixtureList()->GetNext();
        b2PolygonShape* shape = static_cast<b2PolygonShape*>(f->GetShape());
        ofSetColor(ofColor::mediumVioletRed);
        ofDrawCircle(shape->m_vertices[0].x*30, shape->m_vertices[0].y*30 , 2);
        ofDrawCircle(shape->m_vertices[1].x*30, shape->m_vertices[1].y*30 , 2);
        ofDrawCircle(shape->m_vertices[2].x*30, shape->m_vertices[2].y*30 , 2);
        ofDrawCircle(shape->m_vertices[3].x*30, shape->m_vertices[3].y*30 , 2);
    };
    void contactStart(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactEnd(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite);
};
