//
//  Ladder.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 21/08/2017.
//
//

#include "Ladder.h"

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
    tempFilter.categoryBits = 0x0128;
    tempFilter.maskBits = 0x0001;
    polygon.setFilterData(tempFilter);
    
    //polygon.body->GetFixtureList()->SetSensor(true);
}
void Ladder::contactStart(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite){
    Avatar *objSource = static_cast<Avatar*>(OtherSprite->physicalizedElement);
    
    b2Fixture* f = polygon.body->GetFixtureList();
    if (_fixture == f) {
        //cout << "Start Ladder " << endl;
        objSource->lockLadderDown =true;
        //objSource->setMove(Deplacement::DOWN);
    }
    
    f = f->GetNext();
    if (_fixture == f) {
        //cout << "Start LadderDown " << endl;
        objSource->SetGravityScale(.0f);
        objSource->setMove(Deplacement::PLATFORMLADDER);
        //objSource->setJumping(true);
    }
    
    f = f->GetNext();
    if (_fixture == f) {
        //cout << "Start LadderTop " << endl;
        objSource->lockLadderTop=true;
        objSource->SetGravityScale(.0f);
        objSource->polygon.body->SetLinearVelocity(b2Vec2(0.f, 0.f));
        objSource->setJumping(false);
        objSource->setMove(Deplacement::PLATFORMLADDER);
    }
}
void Ladder::contactEnd(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite){
    Avatar *objSource = static_cast<Avatar*>(OtherSprite->physicalizedElement);
    
    b2Fixture* f = polygon.body->GetFixtureList();
    
    if (_fixture == f) {
        if (!objSource->lockLadderTop && !objSource->lockLadderDown) {
            //cout << "End Ladder " << endl;
            objSource->SetGravityScale(1.0f);
            objSource->setMove(Deplacement::PLATFORM);
        }
    }
    f = f->GetNext();
    if (_fixture == f) {
        //cout << "End LadderDown " << endl;
        objSource->lockLadderDown = false;
        objSource->SetGravityScale(0.0f);// ici problem
        
    }
    
    f = f->GetNext();
    if (_fixture == f) {
        //cout << "End LadderTop " << endl;
        objSource->lockLadderTop=false;
        objSource->SetGravityScale(1.0f);// ici problem
        objSource->setMove(Deplacement::PLATFORM);
    }
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
                                                  - getBoundingBox().getMax().y-3));
        //vec2 = b2Vec2(0.f, 0.f);
        shape.SetAsBox(rect.x,3/30.f,vec2,0.f);
        fixtureSide.shape		= &shape;
        body->CreateFixture(&fixtureSide);
        //LEFT = 3, place END - 1
        //fixtureSide.id = 3;
        vec2 = screenPtToWorldPt(getBoundingBox().getCenter()
                                 + ofVec2f(0,getBoundingBox().getCenter().y
                                           - getBoundingBox().getMin().y-3));
        
        shape.SetAsBox(rect.x, 3/30.f, vec2, 0.f);
        fixtureSide.shape		= &shape;
        body->CreateFixture(&fixtureSide);
        
        /*//DOWN = 2,
         //fixtureSide.id = 2;
         vec2 = b2Vec2(0.f, 4.89/30.f);
         shape.SetAsBox(rect.x -2/30.f, 2/30.f, vec2, 0.f);
         fixtureSide.shape		= &shape;
         body->CreateFixture(&fixtureSide);
         //UP = 1,
         //fixtureSide.id = 1;
         vec2 = b2Vec2(0.f, -2.8/30.f);
         shape.SetAsBox(rect.x-3/30.f, 2/30.f, vec2, 0.f);
         fixtureSide.shape = &shape;
         body->CreateFixture(&fixtureSide);*/
    }
    
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
        b2Vec2 vec2 = screenPtToWorldPt(getBoundingBox().getCenter()+ofVec2f(0,getBoundingBox().getCenter().y - getBoundingBox().getMax().y));
        //vec2 = b2Vec2(0.f, 0.f);
        shape.SetAsBox(rect.x,4/30,vec2,0.f);
        fixtureSide.shape		= &shape;
        body->CreateFixture(&fixtureSide);
        /*//LEFT = 3, place END - 1
         //fixtureSide.id = 3;
         vec2 = b2Vec2(-4.89/30.f,0.f);
         shape.SetAsBox(2/30.f, rect.y, vec2, 0.f);
         fixtureSide.shape		= &shape;
         body->CreateFixture(&fixtureSide);
         //DOWN = 2,
         //fixtureSide.id = 2;
         vec2 = b2Vec2(0.f, 4.89/30.f);
         shape.SetAsBox(rect.x -2/30.f, 2/30.f, vec2, 0.f);
         fixtureSide.shape		= &shape;
         body->CreateFixture(&fixtureSide);
         //UP = 1,
         //fixtureSide.id = 1;
         vec2 = b2Vec2(0.f, -2.8/30.f);
         shape.SetAsBox(rect.x-3/30.f, 2/30.f, vec2, 0.f);
         fixtureSide.shape = &shape;
         body->CreateFixture(&fixtureSide);*/
    }
    
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
