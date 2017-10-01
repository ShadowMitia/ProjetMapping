//
//  PickUp.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 29/09/2017.
//
//

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Teleportable.h"
#include "../Constant.h"
#include "PhysicalizedElement.h"

class PickUp : public Teleportable {
    
public:
    
    
    PickUp(b2World* _box2d, ofPolyline _polyline);
    
    void update() override;
    void draw() override;
    
    void createClone(ofVec2f translateClone) override;
    void removeClone() override;
    void teleportToClone() override;
    bool hasClone() override;
    
    void contactStart(dataSprite* OtherSprite) override;
    void contactEnd(dataSprite* OtherSprite) override;
    void PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;
    
    ofVec2f getPosition()
    {
        return pickUp.getPosition();
    }
    
private:
    ofxBox2dPolygon pickUp;
    
    int width;
    int height;
    
    std::unique_ptr<PickUp> clone;
    
    b2World* box2d;
    
    ofVec2f cloneTranslation;
    

    
};
