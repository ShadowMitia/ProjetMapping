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



class dataAvatar: public dataSprite {
public:
    dataAvatar(){
        setSprite(Sprite::AVATRA);
    }
    bool jumping = false;
};

class Avatar {
public:

  Avatar(ofxBox2d* box2d, ofx::LightSystem2D* lightSystem);
    ofxBox2dPolygon polygon;
    ofxBox2dRect    foot;
    ofx::Light2D::SharedPtr   light;
    ofRectangle rect;
    
private:
    std::unique_ptr<Avatar> clone = nullptr;
    ofVec2f cloneTranslation;
    ofx::LightSystem2D* lightSystemRef;
    ofxBox2d* box2dRef;
    bool top =false;
    bool jumping = false;
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
