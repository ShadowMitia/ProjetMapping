#include "PhysicalizedElement.h"

void PhysicalizedElement::contactStart(b2Fixture* _fixture, dataSprite* OtherSprite)
{
    
}

void PhysicalizedElement::contactEnd(b2Fixture* _fixture,dataSprite* OtherSprite)
{
    
}


void ObjectGame::create(b2World * b2dworld, bool _detectSide){
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
    
    if (_detectSide) {
        b2FixtureDef fixtureSide;
        b2PolygonShape shape;
        fixtureSide.density		= 0;
        fixtureSide.restitution = 0;
        fixtureSide.friction	= 0;
        fixtureSide.isSensor    = true;
        //UP, DOWN, LEFT, RIGHT};
        
        //RIGHT = 4, place END
        fixtureSide.id = 4;
        b2Vec2 rect = screenPtToWorldPt(getBoundingBox().getMax()-1);
        b2Vec2 vec2 = b2Vec2(2/30.f, 0.f);
        shape.SetAsBox(rect.x, rect.y, vec2, 0.f);
        fixtureSide.shape		= &shape;
        body->CreateFixture(&fixtureSide);
        //LEFT = 3, place END - 1
        fixtureSide.id = 3;
        vec2 = b2Vec2(-2/30.f,0.f);
        shape.SetAsBox(rect.x, rect.y, vec2, 0.f);
        fixtureSide.shape		= &shape;
        body->CreateFixture(&fixtureSide);
        //DOWN = 2,
        fixtureSide.id = 2;
        vec2 = b2Vec2(0.f, 2/30.f);
        shape.SetAsBox(rect.x, rect.y, vec2, 0.f);
        fixtureSide.shape		= &shape;
        body->CreateFixture(&fixtureSide);
        //UP = 1,
        fixtureSide.id = 1;
        vec2 = b2Vec2(0.f, -2/30.f);
        shape.SetAsBox(rect.x, rect.y, vec2, 0.f);
        fixtureSide.shape		= &shape;
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
    b2Fixture * f = body->GetFixtureList();
    f->SetFilterData(_filter);
}
void ObjectGame::setFilterDataSide(b2Filter _filter){
    if (body->GetNext() == nullptr) {
        int i = 0;
        for( b2Fixture * f = body->GetFixtureList(); f; f = f->GetNext() ){
            if (i!=0) {
                f->SetFilterData(_filter);
            }
            ++i;
        }
        
    }
}

