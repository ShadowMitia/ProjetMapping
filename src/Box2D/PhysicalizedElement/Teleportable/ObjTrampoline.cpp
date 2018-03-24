//
//  ObjTrampoline.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 06/03/2018.
//
//

#include "ObjTrampoline.h"
#include "WorldsBox2d.h"

ObjTrampoline::ObjTrampoline(ObjTrampolineDef* _objTrampolineDef){
    
    sprite = static_cast<SpriteObj*>(_objTrampolineDef);
    _objTrampolineDef->t = this;
    std::vector<ofPoint> pts = loadPoints("Trampline.dat");
    polygon.addVertices(pts);
    //polygon.triangulatePoly();
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    //polygon.create(box2d);
    polygon.create(_objTrampolineDef->world->world.getWorld(), false);
    polygon.body->SetFixedRotation(true);
    
    teleportableFilter.categoryBits = _objTrampolineDef->categoryBits ;
    setFilter(_objTrampolineDef->maskBits | Category::PLATFORM |Category::PLATFORM_1);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::BLOCK;
    data->physicalizedElement = this;
    
    polygon.body->SetGravityScale(1.0);
    
   
}

void ObjTrampoline::draw(){
    ofSetColor(ofColor::navajoWhite);
    polygon.draw();
    ofSetColor(ofColor::white);
}

void ObjTrampoline::contactStart(ofxBox2dContactArgs e, b2Fixture *_fixture, dataSprite *OtherSprite){
    if (OtherSprite->sprite == Sprite::AVATAR) {
        Avatar * a = dynamic_cast<Avatar*>(OtherSprite->physicalizedElement);
        //cout << "viewPoint: " << viewPoint <<  " a->viewPoint: " <<   a->viewPoint << endl;
        viewPoint = a->viewPoint; // attention  << ici
        cout << e.contact->GetManifold()->localNormal.y << endl;
        if (e.contact->GetManifold()->localNormal.y == -1) { // voici la code pour le Trampoline
            a->setVelocity(ofVec2f(a->getVelocity().x, -a->getVelocity().y));
            a->polygon.addForce(ofVec2f(0, -1), 300);
            
        }
        polygon.body->SetLinearVelocity(_fixture->GetBody()->GetLinearVelocity());
        
    }
    if (OtherSprite->sprite == Sprite::CLONE) {
        polygon.body->SetLinearVelocity(_fixture->GetBody()->GetLinearVelocity());
    }
}
void ObjTrampoline::contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite){
    if (OtherSprite->sprite == Sprite::AVATAR) {
        polygon.body->SetLinearVelocity(b2Vec2(0, 0));
    }
    if (OtherSprite->sprite == Sprite::CLONE) {
        polygon.body->SetLinearVelocity(b2Vec2(0, 0));
    }
}
