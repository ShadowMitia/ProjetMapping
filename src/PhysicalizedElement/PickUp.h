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
    
    
    PickUp(b2World* box2d, ofPolyline polyline);
    
    void update(ofRectangle gravityWell) override;
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
    pickUp.setPosition(x + width / 2, y + height / 2);
  }

    ofVec2f getPosition()
    {
      ofVec2f pos = pickUp.getPosition();
      pos += ofVec2f(width / 2, height / 2);
      return pos;
    }

  void setCollected()
  {
    collected = true;
  }

  bool isCollected() const
  {
    return collected;
  }

  void gravityCheck(ofRectangle gravityWell) override
  {
    if (gravityWell.inside(pickUp.getPosition()))
      {
	pickUp.body->SetGravityScale(0.0);
      }
    else
      {
	pickUp.body->SetGravityScale(1.0);
      }
  }
    
  ofxBox2dPolygon pickUp;

private:
  std::unique_ptr<PickUp> clone;
    
  ofVec2f cloneTranslation;

  bool collected = false;

  int width = 0;
  int height = 0;
};
