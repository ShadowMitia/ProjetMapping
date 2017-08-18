//
//  Avatar.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//
#include "Avatar.h"
#include "Platform.h"

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
    polygon.setPhysics(10.0, 0.03, 4.0);
    polygon.create(box2d->getWorld());

	polygon.body->SetType(b2BodyType::b2_dynamicBody);
	polygon.body->SetFixedRotation(true);


    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0001;
    tempFilter.maskBits = 0xFFFF;
    polygon.setFilterData(tempFilter);
    /////////////// FOOT ///////////////
    ofRectangle temp = polygon.getBoundingBox();
    temp.height = 5;
    temp.width = temp.width-2;
    foot.setPhysics(3.0, 0.53, 0.1);
    foot.setup(box2d->getWorld(), temp);
    foot.body->SetGravityScale(0);
    tempFilter.categoryBits = 0x0002;
    tempFilter.maskBits =  0x0004;
    foot.setFilterData(tempFilter);
	moveInputX = 0.0f;
	
/////////////////////////  Data /////////////////
    dataAvatar* dataAv = new dataAvatar;
    dataAv->setSprite(Sprite::AVATAR);
    polygon.setData(dataAv);
    dataFoot* dataFo = new dataFoot;
    dataFo->setSprite(Sprite::FOOT);
    dataFo->Element = this;
    foot.setData(dataFo);
    
    light = std::make_shared<ofx::Light2D>();
    light->setRadius(700);
    lightSystem->add(light);
     
    
}

void Avatar::update()
{
	move(moveInputX);

    foot.setPosition(polygon.getPosition()+ofVec2f(0,21));
    
    if (!jumping)
	{
        this->polygon.setRotation(0);
    }
	if (light)
	{
		light->setPosition(polygon.getPosition());
	}
    collisionRect.set(polygon.getBoundingBox().getStandardized() + polygon.getPosition());


  if (clone)
    {
      clone->polygon.setVelocity(polygon.getVelocity());
      clone->setPosition(polygon.getPosition() + cloneTranslation);
    }

  //std::cout << "Position: " << rect.x << " " << rect.y << '\n';

}

void Avatar::draw() {

    ofSetColor(ofColor::blue);
    polygon.draw();
    ofSetColor(ofColor::violet);
    foot.draw();
    ofSetColor(ofColor::white);
    //ofSetColor(ofColor::orange);
    //ofDrawRectangle(collisionRect);
    
  if (clone) {
    clone->draw();
  }
}

void Avatar::createClone(ofVec2f cloneTranslation) {
    if (clone) { return; }

    this->cloneTranslation = cloneTranslation;

    clone = std::make_unique<Avatar>(box2dRef, lightSystemRef);
    clone->setPosition(cloneTranslation);
    clone->polygon.setVelocity(polygon.getVelocity());
    clone->polygon.create(polygon.getWorld());

}

void Avatar::removeClone() {
  //lightSystemRef->remove(clone->light);
  clone = nullptr;
  cloneTranslation.zero();

}

void Avatar::teleportToClone() {
  //lightSystemRef->remove(clone->light);

  auto vel = polygon.getVelocity();
  polygon.setPosition(clone->polygon.getPosition());
  polygon.setVelocity(vel);
  cloneTranslation.zero();
}

bool Avatar::hasClone() 
{ 
	return (clone == nullptr); 
}

void Avatar::setPosition(ofVec2f vec)
{
	setPosition(vec.x, vec.y);
}
void Avatar::setPosition(int x, int y)
{
  polygon.setPosition(x, y);
  collisionRect.setPosition(x, y);
  //light->setPosition(ofVec2f(x, y));
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
    else
	{
        switch (_direction) 
		{
            case Direction::LEFT:
                polygon.setVelocity(-10, polygon.getVelocity().y);
                break;
            case Direction::RIGHT:
                polygon.setVelocity(10, polygon.getVelocity().y);
                break;
            case Direction::JUMP:
                polygon.setVelocity(polygon.getVelocity().x, -10);
			default:
			  break;
        }
    }
}

void Avatar::move(float inputX)
{
	b2Vec2 impulse = VarConst::speedAvatar * inputX * b2Vec2(1.0f, 0.0f);

	impulse *= (1 - polygon.getVelocity().length() / VarConst::speedAvatarMax);

	polygon.body->ApplyLinearImpulse(impulse, polygon.body->GetLocalCenter(), true);
}

void Avatar::jump()
{
	b2Vec2 impulse = VarConst::impulseJumpAvatar * b2Vec2(0.0f, -1.0f);

	if (!jumping)
	{
		polygon.body->ApplyLinearImpulse(impulse, polygon.body->GetLocalCenter(), true);
	}
}

void Avatar::keyPressed(int key)
{
	if (key == OF_KEY_LEFT || key == 'q')
	{
		moveInputX  = -1.0f;
	}
	if (key == OF_KEY_RIGHT || key == 'd')
	{
		moveInputX = 1.0f;
	}

	if (key == ' ')
	{
		jump();
	}
}
void Avatar::keyReleased(int key)
{
	if (key == OF_KEY_LEFT || key == 'q')
	{
		moveInputX = 0.0f;
	}
	if (key == OF_KEY_RIGHT || key == 'd')
	{
		moveInputX = 0.0f;
	}
}

void Avatar::contactStart(dataSprite* OtherSprite)
{
	PhysicalizedElement::contactStart(OtherSprite);

	if (OtherSprite->getSprite() == Sprite::PLATFORM) 
	{
		jumping = false;
	}
}

void Avatar::contactEnd(dataSprite* OtherSprite)
{
	PhysicalizedElement::contactEnd(OtherSprite);

	if (OtherSprite->getSprite() == Sprite::PLATFORM) 
	{
		jumping = true;
	}
}