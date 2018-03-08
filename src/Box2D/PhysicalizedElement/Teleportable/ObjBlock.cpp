//
//  ObjBlock.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/02/2018.
//
//
#include "ObjBlock.h"
#include "WorldsBox2d.h"
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

ObjBlock::ObjBlock(ObjBlockDef* _objBlockDef){
    
    sprite = static_cast<SpriteObj*>(_objBlockDef);
    _objBlockDef->b = this;
    std::vector<ofPoint> pts = loadPoints("ObjBlock.dat");
    polygon.addVertices(pts);
    //polygon.triangulatePoly();
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    //polygon.create(box2d);
    polygon.create(_objBlockDef->world->world.getWorld(), false);
    polygon.body->SetFixedRotation(true);
    
    teleportableFilter.categoryBits = _objBlockDef->categoryBits ;
    setFilter(_objBlockDef->maskBits | Category::PLATFORM |Category::PLATFORM_1);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::BLOCK;
    data->physicalizedElement = this;
    
    polygon.body->SetGravityScale(1.0);
    
    rT = new resteTime(15000000000.0, this);
}

void ObjBlock::draw(){
    ofSetColor(ofColor::navajoWhite);
    polygon.draw();
    ofSetColor(ofColor::white);
}

void ObjBlock::contactStart(ofxBox2dContactArgs e, b2Fixture *_fixture, dataSprite *OtherSprite){
    if (OtherSprite->sprite == Sprite::AVATAR) {
        Avatar * a = dynamic_cast<Avatar*>(OtherSprite->physicalizedElement);
        //cout << "viewPoint: " << viewPoint <<  " a->viewPoint: " <<   a->viewPoint << endl;
        viewPoint = a->viewPoint; // attention  << ici
        cout << e.contact->GetManifold()->localNormal.y << endl;
        if (e.contact->GetManifold()->localNormal.y == -1) { // voici la code pour le Trampoline
            a->setVelocity(ofVec2f(a->getVelocity().x, -a->getVelocity().y));
            a->polygon.addForce(ofVec2f(0, -1), 200);
            
        }
        polygon.body->SetLinearVelocity(_fixture->GetBody()->GetLinearVelocity());
        
    }
    if (OtherSprite->sprite == Sprite::CLONE) {
        polygon.body->SetLinearVelocity(_fixture->GetBody()->GetLinearVelocity());
    }
    //rT->stopThread();
}
void ObjBlock::contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite){
    if (OtherSprite->sprite == Sprite::AVATAR) {
        polygon.body->SetLinearVelocity(b2Vec2(0, 0));
    }
    if (OtherSprite->sprite == Sprite::CLONE) {
        polygon.body->SetLinearVelocity(b2Vec2(0, 0));
    }
    //rT->startThread();
}

void resteTime::threadedFunction(){
    cout << "Debut " << endl;
    time.reset();
    time.waitNext();
    b->sprite->reset();
    cout << "Fin " << endl;

}