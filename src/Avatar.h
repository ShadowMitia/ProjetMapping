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
#include "Constant.h"



class Avatar {
public:

  Avatar(ofxBox2d* box2d, ofx::LightSystem2D* lightSystem);
    ofxBox2dPolygon polygon;
    ofxBox2dRect    foot;
    ofx::Light2D::SharedPtr   light;
    ofRectangle rect;
    bool jumping = false;
    
private:
    std::unique_ptr<Avatar> clone = nullptr;
    ofVec2f cloneTranslation;
    ofx::LightSystem2D* lightSystemRef;
    ofxBox2d* box2dRef;
    bool top =false;
    
    int countAirControl;

public:


  void update();
  void draw();
  void handleInputs(int key);
  void createClone(ofVec3f cloneTranslation);
  void removeClone();
  void teleportToClone();
  bool hasClone();


    void setPosition(int x, int y);
    void goingLeft(bool isPressed);
    void goingRight(bool isPressed);
    void jump();
    void move(Direction _direction);
    void airControl(Direction _direction);

};

class dataAvatar: public dataSprite {
public:
    dataAvatar(){
        setSprite(Sprite::AVATRA);
    }
    
};
class dataFoot: public dataSprite {
public:
    dataFoot(){
        setSprite(Sprite::FOOT);
    }
    bool jumping = false;
    Avatar* avatarPtr;
};
