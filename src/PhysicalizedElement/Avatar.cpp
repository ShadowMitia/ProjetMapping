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
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, VarConst::frictionAvatar);
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
	jumping = false;
	ClicJump = false;

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
    
    modeDeplace = Deplacement::PLATFORM;
    
}

void Avatar::presUpdate(){
    foot.setPosition(polygon.getPosition()+ofVec2f(0,4));
    collisionRect.set(polygon.getBoundingBox().getStandardized() + polygon.getPosition());
}

void Avatar::update()
{
    
    if (modeDeplace == Deplacement::PLATFORM ) {
        polygon.body->SetGravityScale(1.0);
        move(moveInputX);
    }
    else{
        polygon.body->SetGravityScale(0.0);
        move(moveInputX, moveInputY);
    }
    
    if (!jumping)
	{
        //this->polygon.setRotation(0);
        
    }
    else{
        this->polygon.setVelocity(this->polygon.getVelocity().x - (VarConst::coefFrotementAir * this->polygon.getVelocity().x/VarConst::speedAvatarMax), this->polygon.getVelocity().y);
    }
    
	if (light)
	{
		light->setPosition(polygon.getPosition());
	}

  if (clone)
    {
      clone->polygon.setVelocity(polygon.getVelocity());
      clone->setPosition(polygon.getPosition() + cloneTranslation);
    }


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

    return clone ? true : false;
    //return (clone == nullptr);
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
void Avatar::move(float inputX)
{
	float speed = VarConst::speedAvatar;
	float speedMax = VarConst::speedAvatarMax;
	if (jumping)
	{

		speed = VarConst::speedAvatarAirControl;
		speedMax = VarConst::speedAvatarAirControlMax;
	}
	b2Vec2 impulse = speed * inputX * b2Vec2(1.0f, 0.0f);

	impulse *= (1 - std::min(std::abs(polygon.getVelocity().x), speedMax) / speedMax);
	polygon.body->ApplyLinearImpulse(impulse, polygon.body->GetLocalCenter(), true);
}
void Avatar::move(float inputX,float inputY)
{

    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    b2Vec2 impulse ;
    impulse.x = speed * inputX * 1.0f;
    impulse.y = speed * inputY * 1.0f;
    impulse *= (1 - std::min(polygon.getVelocity().length(), speedMax) / speedMax);
    polygon.body->ApplyLinearImpulse(impulse, polygon.body->GetLocalCenter(), true);
    
}
void Avatar::jump()
{
	if (!jumping)
	{
		jumping = true;
		// allez zou, on vire l'inertie du joueur pour ne pas avoir d'elan
		//polygon.setVelocity(0, 0);
		// impulsion droite
		b2Vec2 impulseH = VarConst::impulseJumpAvatar * b2Vec2(0.0f, -1.0f);
        // impulsion latterale
		b2Vec2 impulseL = VarConst::impulseLateralJumpAvatar * moveInputX * b2Vec2(1.0f, 0.0f);
		//calcul de la direction et intensité du saut
		b2Vec2 impulse = impulseH + impulseL;
		impulse *= impulseH.Length() / impulse.Length();

		//si on ne saute pas droit, on attenue le saut pour ne pas avoir l'impression que le joueur accelere en sautant
        /*
		if (abs(moveInputX) > 0)
		{
			impulse *= VarConst::attenuationImpulseJump;
		}*/
        impulse = impulseH * (1 - polygon.getVelocity().x/VarConst::speedAvatarMax);
        
		polygon.body->ApplyLinearImpulse(impulseH, polygon.body->GetLocalCenter(), true);
	}
}
void Avatar::keyPressed(int key)
{
	if (key == OF_KEY_LEFT || key == 'q')
	{
		moveInputX = -1.0f;
	}
	if (key == OF_KEY_RIGHT || key == 'd')
	{
		moveInputX = 1.0f;
	}
	if (key == OF_KEY_UP || key == 'z') 
	{
		moveInputY = -1.0f;
	}
	if (key == OF_KEY_DOWN || key == 's') 
	{
		moveInputY = 1.0f;
	}
	if (key == OF_KEY_LEFT_CONTROL)
	{
		viewpoint = Viewpoint::MODE_PERSPECTIVE;
	}
	if (key == ' ' && !ClicJump)
	{
		ClicJump = true;
		jump();
	}

}
void Avatar::keyReleased(int key)
{

	if (key == OF_KEY_LEFT || key == 'q')
	{
		moveInputX = 0.0f;
        
        if (!jumping || modeDeplace != Deplacement::PLATFORM) {
            polygon.setVelocity(0, polygon.getVelocity().y);
        }
        
	}
	if (key == OF_KEY_RIGHT || key == 'd')
	{
		moveInputX = 0.0f;
        if (!jumping || modeDeplace != Deplacement::PLATFORM) {
            polygon.setVelocity(0, polygon.getVelocity().y);
        }
        
	}
    if (key ==  OF_KEY_UP || key == 'z')
    {
        moveInputY = 0.0f;
        if (!jumping || modeDeplace != Deplacement::PLATFORM) {
            polygon.setVelocity(polygon.getVelocity().x,0);
        }
        
    }
    if (key == OF_KEY_DOWN || key =='s')
    {
        moveInputY = 0.0f;
        if (!jumping|| modeDeplace != Deplacement::PLATFORM) {
            polygon.setVelocity(polygon.getVelocity().x,0) ;
        }
        
    }
	if (key == OF_KEY_LEFT_CONTROL)
	{
		viewpoint = Viewpoint::MODE_ANGLE;
	}
	if (key == ' ')
	{
		ClicJump = false;
	}
}
void Avatar::contactStart(dataSprite* OtherSprite)
{
	PhysicalizedElement::contactStart(OtherSprite);

	if (OtherSprite->getSprite() == Sprite::PLATFORM) 
	{
		jumping = false;
		if (!(abs(moveInputX) > 0))
		{
			polygon.setVelocity(0, polygon.getVelocity().y);
		}
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
void Avatar::PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse)
{
	PhysicalizedElement::PostSolve(OtherSprite, impulse);

	if (OtherSprite->getSprite() == Sprite::PLATFORM)
	{
		//cout << "normalImpulses [0] : " << impulse->normalImpulses[0] << "normalImpulses [1] : " << impulse->normalImpulses[1] << endl;
		//cout << "tangentImpulses [0] : " << impulse->tangentImpulses[0] << "tangentImpulses [1] : " << impulse->tangentImpulses[1] << endl;

		jumping = false;
		if (!(abs(moveInputX) > 0))
		{

			polygon.setVelocity(0, polygon.getVelocity().y);
		}
	}
}
