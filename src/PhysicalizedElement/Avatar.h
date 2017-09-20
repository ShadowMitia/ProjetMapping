//
//  Avatar.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//
#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "../LightSystem2D.h"
#include "Teleportable.h"
#include "ofxGLFWJoystick.h"
#include "ObjetBlock.h"


class Avatar : public Teleportable {

public:

	Avatar(ofxBox2d* box2d, ofx::LightSystem2D* lightSystem);

    ofxBox2dPolygon polygon;
    ofxBox2dRect    foot;

    ofx::Light2D::SharedPtr   light;
    ofRectangle rect;
    bool jumping;
	bool ClicJump;
    Deplacement modeDeplace;

    
private:
    std::unique_ptr<Avatar> clone = nullptr;
    ofVec2f cloneTranslation;
    ofx::LightSystem2D* lightSystemRef;
    ofxBox2d* box2dRef;
    bool top =false;
    
    int countAirControl;
	float moveInputX;
    float moveInputY;

public:

  void presUpdate();
  void update() override;
  void draw() override;
  void createClone(ofVec2f cloneTranslation) override;
  void removeClone() override;
  void teleportToClone() override;
  bool hasClone() override;

    
  void setPosition(ofVec2f vec);
  void setPosition(int x, int y);
  void jump();
  void move(Direction _direction);
  void move(float inputX);
  void move(float inputX, float inputY);

  void keyPressed(int key);
  void keyReleased(int key);

  virtual void contactStart(dataSprite* OtherSprite) override;
  virtual void contactEnd(dataSprite* OtherSprite) override;
  virtual void PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;

};
class dataAvatar: public dataSprite {
public:
    dataAvatar(){
        setSprite(Sprite::AVATAR);
    }
};
class dataFoot: public dataSprite {
public:
    dataFoot(){
        setSprite(Sprite::FOOT);
    }
};
