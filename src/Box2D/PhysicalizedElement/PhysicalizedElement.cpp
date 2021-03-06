#include "PhysicalizedElement.h"

std::vector<ofPoint> loadPoints(const std::string& file)
 {
 std::vector<ofPoint> pts;
 std::vector <std::string>  ptsStr = ofSplitString(ofBufferFromFile(file).getText(), ",");
 for (unsigned int i = 0; i < ptsStr.size(); i += 2) {
 float x = ofToFloat(ptsStr[i]);
 float y = ofToFloat(ptsStr[i+1]);
 pts.push_back(ofPoint(x, y));
 }
 return pts;
 }



void PhysicalizedElement::contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite){
    
}
void PhysicalizedElement::contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture,dataSprite* OtherSprite){
    
}

// code ObjetGame 
void ObjectGame::create(b2World * b2dworld, bool circleActiv){
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
    
    /*if (_detectSide) {
        b2FixtureDef fixtureSide;
        b2PolygonShape shape;
        fixtureSide.density		= 0;
        fixtureSide.restitution = 0;
        fixtureSide.friction	= 0;
        fixtureSide.isSensor    = true;
        //UP, DOWN, LEFT, RIGHT};
        
        //RIGHT = 4, place END
        //fixtureSide.id = 4;
        b2Vec2 rect = screenPtToWorldPt(getBoundingBox().getMax()-1.f);
        b2Vec2 vec2 = b2Vec2(4.89/30.f, 0.f);
        shape.SetAsBox(2/30.f,rect.y, vec2, 0.f);
        fixtureSide.shape		= &shape;
        body->CreateFixture(&fixtureSide);
        //LEFT = 3, place END - 1
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
        body->CreateFixture(&fixtureSide);        
    }*/
    if (circleActiv) {
        b2CircleShape shape;
        shape.m_radius		= 30 / OFX_BOX2D_SCALE;
        
        b2FixtureDef fixtureSide;
        fixtureSide.shape		= &shape;
        fixtureSide.density		= 0;
        fixtureSide.friction	= 0;
        fixtureSide.restitution	= 0;
        fixtureSide.isSensor    = true;
        body->CreateFixture(&fixtureSide);
    }
    
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
            fixture.isSensor    = false;
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
        cout << " friction " << friction << endl;
        fixture.isSensor    = false;
        body->CreateFixture(&fixture);
    }
    
    
    
    
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
void ObjectGame::setFilterDataObjet(b2Filter _filter){
    cout << "setFilterDataObjet" << endl;
    b2Fixture * f = body->GetFixtureList();
    f->SetFilterData(_filter);
}
void ObjectGame::setFilterDataSide(b2Filter _filter){
    cout << "setFilterDataSide" << endl;

        int i = 0;
        for( b2Fixture * f = body->GetFixtureList(); f; f = f->GetNext() ){
            if (i!=0) {
                f->SetFilterData(_filter);
            }
            ++i;
        }
}
