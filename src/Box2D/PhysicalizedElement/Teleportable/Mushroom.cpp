//
//  Mushroom.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 12/02/2018.
//
//

#include "Mushroom.h"
#include "WorldsBox2d.h"
#include "Clone.h"
/*
 Category bits:
 PLATFORM : 0x0001
 PORTAL   : 0x0002
 LADDER   : 0x0004
 CLONE    : 0x0008
 AVATAR   : 0x0010
 BLOCK    : 0x0020
 PICKUP   : 0x0040
 MUSHROOM : 0x0080
 */

void ObjectGame::createObjMushroom(b2World * b2dworld, bool _detectSide){
    if(size() <= 3) {
        ofLog(OF_LOG_NOTICE, "need at least 3 points: %i\n", (int)size());
        return;
    }
    
    if (body != NULL) {
        b2dworld->DestroyBody(body);
        body = NULL;
    }
    
    // create the body from the world (1)
    b2BodyDef		bd;
    bd.type			= density <= 0.0 ? b2_staticBody : b2_dynamicBody;
    body			= b2dworld->CreateBody(&bd);
    body->SetFixedRotation(true);
    
    
    if(ofxBox2dPolygon::bIsTriangulated) {
        
        b2PolygonShape	shape;
        b2FixtureDef	fixture;
        b2Vec2			verts[3];
        
        ofVec2f a, b, c;
        for (int i=0; i<triangles.size(); i++) {
            
            a = triangles[i].a;
            b = triangles[i].b;
            c = triangles[i].c;
            
            verts[0].Set(a.x/OFX_BOX2D_SCALE, a.y/OFX_BOX2D_SCALE);
            verts[1].Set(b.x/OFX_BOX2D_SCALE, b.y/OFX_BOX2D_SCALE);
            verts[2].Set(c.x/OFX_BOX2D_SCALE, c.y/OFX_BOX2D_SCALE);
            
            shape.Set(verts, 3);
            
            fixture.density		= density;
            fixture.restitution = bounce;
            fixture.friction	= friction;
            fixture.shape		= &shape;
            fixture.isSensor    = true;
            body->CreateFixture(&fixture);
        }
        
    }
    else {
        ofxBox2dPolygon::makeConvexPoly();
        vector<ofPoint> pts = ofPolyline::getVertices();
        vector<b2Vec2>verts;
        for (int i=0; i<MIN((int)pts.size(), b2_maxPolygonVertices); i++) {
            verts.push_back(screenPtToWorldPt(pts[i]));
        }
        b2PolygonShape shape;
        shape.Set(&verts[0], verts.size()-1);
        fixture.shape		= &shape;
        fixture.density		= density;
        fixture.restitution = bounce;
        fixture.friction	= friction;
        fixture.isSensor    = true;
        body->CreateFixture(&fixture);
    }
    
    setFilterDataObjet(FilterDataObjet);
    
    vector<ofPoint> pts = ofPolyline::getVertices();
    mesh.clear();
    ofPath path;
    ofPoint center = getCentroid2D();
    for (int i=0; i<pts.size(); i++) {
        ofPoint p(pts[i].x, pts[i].y);
        p -= center;
        path.lineTo(p);
    }
    mesh = path.getTessellation();
    mesh.setUsage(GL_STATIC_DRAW);
    
    flagHasChanged();
    alive = true;
}
ObjMushroom::ObjMushroom(ObjMushroomDef *_ObjMushroomDef){
    sprite = static_cast<SpriteObj*>(_ObjMushroomDef);
    _ObjMushroomDef->mroom = this;
    ////////// POLYGONE ///////////////////
    std::vector<ofPoint> pts = loadPoints("avatar.dat");
    for (int i= 0; i<pts.size(); ++i) {
        pts[i].scale(23);
    }
    
    polygon.addVertices(pts);
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    polygon.FilterDataObjet.categoryBits = 0x0080;
    polygon.FilterDataObjet.maskBits =  0x0010 | 0x0008 ;
    
    polygon.createObjMushroom(_ObjMushroomDef->world->world.getWorld(), false);
    
    polygon.body->SetFixedRotation(true);
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::MUSHROOM;
    data->physicalizedElement = this;
    polygon.body->SetGravityScale(0.0);
}
void ObjMushroom::draw(){
    ofSetColor(ofColor::violet);
    polygon.draw();
    ofSetColor(ofColor::white);
}
void ObjMushroom::contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite){
    if (OtherSprite->sprite == Sprite::CLONE) {
        CloneBox2d* clone = static_cast<CloneBox2d*>(OtherSprite->physicalizedElement);
        clone->layer = 2;
        Teleportable* telport = static_cast<Teleportable*>(clone->objSource);
        telport->sprite->layer = 2;

    }
    
}
void ObjMushroom::contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) {
    if (OtherSprite->sprite == Sprite::CLONE) {
        CloneBox2d* clone = static_cast<CloneBox2d*>(OtherSprite->physicalizedElement);
        clone->layer = 0;
    }
    else{
        Teleportable* telport = static_cast<Teleportable*>(OtherSprite->physicalizedElement);
        telport->sprite->layer = 0;
    }
}