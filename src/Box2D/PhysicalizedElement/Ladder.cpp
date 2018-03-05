//
//  Ladder.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 21/08/2017.
//
//

#include "Ladder.h"
#include "Avatar.h"


/*
 Category bits:
 PLATFORM       : 0x0001
 PLATFORM-1     : 0x0002
 PLATFORM-2     : 0x0004
 PORTAL         : 0x0008
 LADDER         : 0x0010
 AVATAR         : 0x0020
 AVATAR-top     : 0x0040
 OBJ            : 0x0080
 OBJ-top        : 0x0100
 MUSHROOM-top   : 0x0200
 */


void Ladder::create(b2World *_b2World, ofPolyline _groundLine){
    
    //ground.clear();
    polygon.addVertexes(_groundLine);
    polygon.setPhysics(0, 0, 0.5f); // (0.0, 0.1, 0.7)
    polygon.create(_b2World);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::LADDER;
    data->physicalizedElement = this;
    
    b2Filter tempFilter;
    tempFilter.categoryBits = Category::LADDER;
    tempFilter.maskBits = Category::AVATAR;
    polygon.setFilterData(tempFilter);
    
}
void Ladder::contactStart(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite){
    if (OtherSprite->sprite==Sprite::AVATAR) {
        Avatar *objSource = static_cast<Avatar*>(OtherSprite->physicalizedElement);
        b2Fixture* f = polygon.body->GetFixtureList();
        if (_fixture == f) {
            cout << "Start Ladder " << endl;
            objSource->lockLadder.ladder = true;
            if (objSource->lockLadder.ladderTop) {
                objSource->setMove(Deplacement::DOWN);
            }
        }
        f = f->GetNext();
        if (_fixture == f) {
            cout << "Start LadderDown " << endl;
            objSource->lockLadder.ladderDown = true;
            objSource->SetGravityScale(.0f);
            objSource->setMove(Deplacement::DOWN);
            //objSource->setJumping(true);
        }
        f = f->GetNext();
        if (_fixture == f) {
            cout << "Start LadderTop " << endl;
            objSource->lockLadder.ladderTop = true;
            objSource->SetGravityScale(.0f);
            objSource->polygon.body->SetLinearVelocity(b2Vec2(0.f, 0.f));
            objSource->setJumping(false);
            objSource->setMove(Deplacement::LADDER);
        }
    }
    
    // pour les Clone voir dans contactStart du clone ( Avatar )
    
}
void Ladder::contactEnd(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite){
    if (OtherSprite->sprite==Sprite::AVATAR) {
        Avatar *objSource = static_cast<Avatar*>(OtherSprite->physicalizedElement);
        
        b2Fixture* f = polygon.body->GetFixtureList();
        if (_fixture == f) {
            objSource->lockLadder.ladder = false;
            cout << "End Ladder " << endl;
            if (!objSource->lockLadder.ladderTop) {
                objSource->SetGravityScale(1.0f);
                objSource->setMove(Deplacement::PLATFORM);
            }
        }
        f = f->GetNext();
        if (_fixture == f) {
            cout << "End LadderDown " << endl;
            objSource->lockLadder.ladderDown = false;
        }
        f = f->GetNext();
        if (_fixture == f) {
            cout << "End LadderTop " << endl;
            if (!objSource->lockLadder.ladder && objSource->lockLadder.ladderTop) {
                objSource->SetGravityScale(1.0f);// ici problem
                objSource->setMove(Deplacement::PLATFORM); /// regardŽ la
            }
            objSource->lockLadder.ladderTop = false;
            
        }
    }
    
    // pour les Clone voir dans contactStart du clone ( Avatar )
}

// Code ObjectLadder //
void ObjectLadder::create(b2World * b2dworld){
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
    
    ofxBox2dPolygon::makeConvexPoly();
    vector<ofPoint> pts = ofPolyline::getVertices();
    
    
    {
        b2FixtureDef fixtureSide;
        b2PolygonShape shape;
        fixtureSide.density		= 0;
        fixtureSide.restitution = 0;
        fixtureSide.friction	= 0;
        fixtureSide.isSensor    = true;
        //UP, DOWN, LEFT, RIGHT};
        
        //RIGHT = 4, place END
        //fixtureSide.id = 4;
        b2Vec2 rect = screenPtToWorldPt(getBoundingBox().getMax()- getBoundingBox().getCenter());
        b2Vec2 vec2 = screenPtToWorldPt(getBoundingBox().getCenter()
                                        + ofVec2f(0,getBoundingBox().getCenter().y
                                                  - getBoundingBox().getMax().y));
        //vec2 = b2Vec2(0.f, 0.f);
        shape.SetAsBox(rect.x,1/30.f,vec2,0.f);
        fixtureSide.shape		= &shape;
        body->CreateFixture(&fixtureSide);
        //LEFT = 3, place END - 1
        //fixtureSide.id = 3;
        vec2 = screenPtToWorldPt(getBoundingBox().getCenter()
                                 + ofVec2f(0,getBoundingBox().getCenter().y
                                           - getBoundingBox().getMin().y-2));
        
        shape.SetAsBox(rect.x, 2/30.f, vec2, 0.f); // le 2/30 et pour evitŽ que le clone contactEnd avant la teleportation
        fixtureSide.shape		= &shape;
        body->CreateFixture(&fixtureSide);
        
        
        vec2 = screenPtToWorldPt(getBoundingBox().getCenter()
                                 + ofVec2f(0,4));
        
        shape.SetAsBox(rect.x,rect.y - 4/30.f , vec2, 0.f);
        fixtureSide.shape		= &shape;
        body->CreateFixture(&fixtureSide);
        
    }
}

void ObjectPlatformLadder::create(b2World * b2dworld){
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
    
    ofxBox2dPolygon::makeConvexPoly();
    vector<ofPoint> pts = ofPolyline::getVertices();
    
    
    b2FixtureDef fixtureSide;
    b2PolygonShape shape;
    fixtureSide.density		= 0;
    fixtureSide.restitution = 0;
    fixtureSide.friction	= 0;
    fixtureSide.isSensor    = true;
    //UP, DOWN, LEFT, RIGHT};
    
    b2Vec2 rect = screenPtToWorldPt(getBoundingBox().getMax()- getBoundingBox().getCenter());
    b2Vec2 vec2 = screenPtToWorldPt(getBoundingBox().getCenter()+ofVec2f(0,getBoundingBox().getCenter().y - getBoundingBox().getMax().y));
    shape.SetAsBox(rect.x,4/30,vec2,0.f);
    fixtureSide.shape		= &shape;
    body->CreateFixture(&fixtureSide);
    
    
    
    vector<b2Vec2>verts;
    for (int i=0; i<MIN((int)pts.size(), b2_maxPolygonVertices); i++) {
        verts.push_back(screenPtToWorldPt(pts[i]));
    }
    b2PolygonShape shap;
    shap.Set(&verts[0], verts.size()-1);
    fixture.shape		= &shap;
    fixture.density		= density;
    fixture.restitution = bounce;
    fixture.friction	= friction;
    fixture.isSensor    = true;
    body->CreateFixture(&fixture);
    
    
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
