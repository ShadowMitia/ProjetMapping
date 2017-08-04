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

    std::cout << ptsStr.size() << " " << pts.size();

    return pts;
}


Avatar::Avatar(ofxBox2d& box2d, ofx::LightSystem2D& lightSystem) : lightSystemRef(lightSystem), box2dRef(box2d)
{
    std::vector<ofPoint> pts = loadPoints("avatar.dat");
    polygon.addVertices(pts);
    polygon.triangulatePoly();
    polygon.setPhysics(3.0, 0.53, 0.1);
    polygon.create(box2d.getWorld());
}

void Avatar::update()
{
  rect.set(polygon.getBoundingBox().getStandardized() + polygon.getPosition());

  if (clone)
    {
      clone->polygon.setVelocity(polygon.getVelocity());
      clone->polygon.setPosition(polygon.getPosition() + cloneTranslation);
    }

  //std::cout << "Position: " << rect.x << " " << rect.y << '\n';
};

void Avatar::draw() {
  polygon.draw();

  if (clone) {
    clone->draw();
  }
}

void Avatar::createClone(ofVec3f cloneTranslation) {
  if (clone) { return; }
  this->cloneTranslation = cloneTranslation;
  clone = std::make_unique<Avatar>(box2dRef, lightSystemRef);
  clone->polygon.setPhysics(polygon.density, polygon.bounce, polygon.friction);
  clone->polygon.addVertices(polygon.getVertices());
  clone->polygon.triangulatePoly();
  clone->polygon.create(box2dRef.getWorld());
  clone->polygon.setVelocity(polygon.getVelocity());
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

  jumping = true;
}


void Avatar::setPosition(int x, int y)
{
  polygon.setPosition(x, y);
  rect.setPosition(x, y);
  //light.setPosition(x, y);
}
