//
//  Avatar.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//
#include "Avatar.h"

std::vector <ofPoint> loadPoints(std::string file) {
    std::vector <ofPoint> pts;
    std::vector <std::string>  ptsStr = ofSplitString(ofBufferFromFile(file).getText(), ",");

    for (unsigned int i = 0; i < ptsStr.size(); i += 2) {
        float x = ofToFloat(ptsStr[i]);
        float y = ofToFloat(ptsStr[i+1]);
        pts.push_back(ofPoint(x, y));
    }

    return pts;
}

Avatar::Avatar(ofxBox2d* box2d, ofx::LightSystem2D* lightSystem) : lightSystemRef(lightSystem), box2dRef(box2d)
{
////////// POLYGONE ///////////////////
    std::vector<ofPoint> pts = loadPoints("avatar.dat");
    polygon.addVertices(pts);
    //polygon.triangulatePoly();
    polygon.setPhysics(3.0, 0.53, 0.1);
    polygon.create(box2d->getWorld());
    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0001;
    tempFilter.maskBits = 0xFFFF;
    polygon.setFilterData(tempFilter);
    /////////////// FOOT ///////////////
    ofRectangle temp = polygon.getBoundingBox();
    temp.height = 5;
    foot.setPhysics(0.0, 0.0, 0.0);
    foot.setup(box2d->getWorld(), temp);
    foot.body->SetGravityScale(0);
    tempFilter.categoryBits = 0x0002;
    tempFilter.maskBits = 0x0000;
    foot.setFilterData(tempFilter);
/////////////////////////  Data /////////////////
    dataAvatar* data = new dataAvatar;
    data->setSprite(Sprite::AVATRA);
    polygon.setData(data);
    foot.setData(data);
    

    light = std::make_shared<ofx::Light2D>();
    light->setRadius(700);
    lightSystem->add(light);
}

void Avatar::update(){
    
    
    
    foot.setPosition(polygon.getPosition()+ofVec2f(0,20));
    
    if (!jumping) {
        this->polygon.setRotation(0);
    }
    light->setPosition(polygon.getPosition());
    rect.set(polygon.getBoundingBox().getStandardized() + polygon.getPosition());

  if (clone)
    {
      clone->polygon.setVelocity(polygon.getVelocity());
      clone->polygon.setPosition(polygon.getPosition() + cloneTranslation);
    }

    if (polygon.getVelocity() == ofVec2f())
    {
        jumping = false;
    }
  //std::cout << "Position: " << rect.x << " " << rect.y << '\n';

}

void Avatar::draw() {
    ofSetColor(ofColor::blue);
    polygon.draw();
    ofSetColor(ofColor::violet);
    foot.draw();
    ofSetColor(ofColor::white);
    
  if (clone) {
    clone->draw();
  }
}

void Avatar::createClone(ofVec3f cloneTranslation) {
    if (clone) { return; }
    this->cloneTranslation = cloneTranslation;
    clone = std::make_unique<Avatar>(box2dRef, lightSystemRef);
    //clone->polygon.setPhysics(polygon.density, polygon.bounce, polygon.friction);
    clone->polygon.addVertices(polygon.getVertices());
    //clone->polygon.triangulatePoly();
    clone->polygon.setPhysics(polygon.density, polygon.bounce, polygon.friction);
    clone->polygon.setVelocity(polygon.getVelocity());
    clone->polygon.create(polygon.getWorld());
    //clone->polygon.setPosition(100, 100);
}

void Avatar::removeClone() {
  clone = nullptr;
  cloneTranslation.zero();
}

void Avatar::teleportToClone() {
  auto vel = polygon.body->GetLinearVelocity();
  polygon.setPosition(clone->polygon.getPosition());
  polygon.body->SetLinearVelocity(vel);
}

bool Avatar::hasClone() { return clone ? true : false; }

void Avatar::handleInputs(int key){
  std::cout << "Key: " << key << " [" << (char)key <<"]\n";

  if (key == OF_KEY_LEFT)
    {
      goingLeft(true);
    }
  else
    {
      goingLeft(false);
    }

  if (key == OF_KEY_RIGHT)
    {
      goingRight(true);
    }
  else
    {
      goingRight(false);
    }

  if (key == ' ')
    {
      jump();
    }
}

void Avatar::goingLeft(bool isPressed) {
  if (isPressed) {
    polygon.setVelocity(-10, polygon.body->GetLinearVelocity().y);
  } else {
    polygon.setVelocity(0, polygon.body->GetLinearVelocity().y);
  }
}

void Avatar::goingRight(bool isPressed) {
  if (isPressed) {
    polygon.setVelocity(10, polygon.body->GetLinearVelocity().y);
  } else {
    polygon.setVelocity(0, polygon.body->GetLinearVelocity().y);
  }
}

void Avatar::jump() {
  if (!jumping)
    {
      float impulse = polygon.body->GetMass() * 500;
      ofVec2f size{ rect.getWidth() / 2, rect.getHeight() / 2 };
      polygon.addForce({ 0, -impulse }, 1.0);
    }

  jumping = false;
}

void Avatar::setPosition(int x, int y){
  polygon.setPosition(x, y);
  rect.setPosition(x, y);
  light->setPosition(ofVec2f(x, y));
}

void Avatar::move(Direction _direction){
    if (top) {
        switch (_direction) {
            case Direction::TOP:
                polygon.setVelocity(polygon.getVelocity().x, -10);
                break;
            case Direction::LEFT:
                polygon.setVelocity(-10, polygon.getVelocity().y);
                break;
            case Direction::RIGHT:
                polygon.setVelocity(10, polygon.getVelocity().y);
                break;
            case Direction::LOW:
                polygon.setVelocity(polygon.getVelocity().x, 10);
        }
    }
    else{
        switch (_direction) {
            case Direction::LEFT:
                polygon.setVelocity(-10, polygon.getVelocity().y);
                break;
            case Direction::RIGHT:
                polygon.setVelocity(10, polygon.getVelocity().y);
                break;
            case Direction::JUMP:
                polygon.setVelocity(polygon.getVelocity().x, -10);
        }
    }
}
void Avatar::airControl(Direction _direction){
    
    if (countAirControl>0) {
        switch (_direction) {
            case Direction::LEFT:
                polygon.addForce(ofVec2f(-10,0), 1);
                countAirControl --;
                break;
            case Direction::RIGHT:
                polygon.addForce(ofVec2f(10,0), 1);
                countAirControl --;
                break;
            default:
                break;
        }

    }
    
}
