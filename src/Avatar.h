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
#include "LightSystem2D.h"

#include "Teleportable.h"

#include "Constant.h"



class dataAvatar: public dataSprite {
public:
    dataAvatar(){
        setSprite(Sprite::AVATAR);
    }
    bool jumping = false;
};

class Avatar : public Teleportable {
public:

  Avatar(ofxBox2d* box2d, ofx::LightSystem2D* lightSystem);

    ofxBox2dPolygon polygon;
    ofxBox2dRect    foot;
  //ofx::Light2D::SharedPtr   light;
    
private:
    std::unique_ptr<Avatar> clone = nullptr;
    ofVec2f cloneTranslation;
    ofx::LightSystem2D* lightSystemRef;
    ofxBox2d* box2dRef;
    bool top =false;
    bool jumping = false;
    int countAirControl;

public:


  void update() override;
  void draw() override;
  void handleInputs(int key);
  void createClone(ofVec2f cloneTranslation) override;
  void removeClone() override;
  void teleportToClone() override;
  bool hasClone() override;



  void setPosition(ofVec2f vec);
  void setPosition(int x, int y);
  void goingLeft(bool isPressed);
  void goingRight(bool isPressed);
  void jump();
  void move(Direction _direction);
  void airControl(Direction _direction);


};
