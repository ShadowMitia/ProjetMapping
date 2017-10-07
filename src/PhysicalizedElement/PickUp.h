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

  void setPosition(float x, float y)
  {
    pickUp.setPosition(x, y);
  }

    ofVec2f getPosition()
    {
        return pickUp.getPosition();
    }

  void setCollected()
  {
    collected = true;
  }

  bool isCollected() const
  {
    return collected;
  }
    
    ofxBox2dPolygon pickUp;

private:
    std::unique_ptr<PickUp> clone;
    
    b2World* box2d;
    
    ofVec2f cloneTranslation;

  bool collected = false;
};
