//
//  WorldsBox2d.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//

#include "WorldsBox2d.h"


void WorldsBox2d::setup(ofx::LightSystem2D * _lightSystem2D){
        
  lightSystem2D = _lightSystem2D;
    
    world.init();
    world.setGravity(0, 10);
    //world.createGround(0,0,1000, 600);
    createBoundsModif(0, 0, WidthWorld2D, 600);
    world.setFPS(60.0);
    

    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL, 50, 525, 35, 75));
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL, 200, 525, 35, 75));


    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL, 400, 525, 35, 75));
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL, 400, 325, 35, 75));
    
    portals[0]->linkTo(portals[1]);
    portals[1]->linkTo(portals[0]);

    portals[2]->linkTo(portals[3]);
    portals[3]->linkTo(portals[2]);

    for (unsigned int i = 0; i < 1; i++)
      {
	createAvatar(800 + i * 50, 500);
      }

    //wiimotes.startThread();

    //createAvatar(100, 100);

    for (auto &avatar : avatars)
      teleportables.push_back(&avatar);

    blocks.emplace_back(&world, 600, 500, 100, 100);

    for (auto &block : blocks)
      teleportables.push_back(&block);




}

void WorldsBox2d::createCircle(float _x,float _y){
    float r = ofRandom(4, 20);
    circles.push_back(std::make_shared<ofxBox2dCircle>());
    circles.back().get()->setPhysics(0.0, 0.53, 0.1);
    circles.back().get()->setup(world.getWorld(), _x, _y, r);
}

void WorldsBox2d::draw(){
  for (auto &portal : portals) {
    portal->draw();
  }

  for (auto &platform : platforms) {
    ofSetHexColor(0xFF0000);
    if (platform->shape->bVisible) {
      platform->ground.draw();
    }
  }

  for (int i = 0; i < circles.size(); i++) {
    ofFill();
    ofSetHexColor(0xf6c738);
    circles[i].get()->draw();
  }


  for (auto &block : blocks)
    {
      ofSetHexColor(0xFFFFF);
      block.draw();
    }

    for (auto &avatar : avatars) {
    ofSetHexColor(0x00FF00);
    avatar.draw();
  }




  
}

void WorldsBox2d::createAvatar(int x, int y){
    avatars.emplace_back(&world, lightSystem2D);
    avatars.back().polygon.setData(new typeBox2d);
    typeBox2d *sd  = (typeBox2d*) avatars.back().polygon.getData();
    sd->type = typeBox2d::Type::AVATAR;
    avatars.back().setPosition(x, y);
}

void WorldsBox2d::update(){
  world.update();
  for (auto &avatar : avatars)
    {
      avatar.update();
    }

  for (auto &block : blocks)
    {
      block.update();
    }

  for (auto &portal : portals)
    {
      portal->update(teleportables);
    }


}

void WorldsBox2d::createPlatform(ofPolyline _polyline){
    
    Platform *edge = new Platform;
    edge->create(world.getWorld(), _polyline, lightSystem2D);
    platforms.push_back(edge);

}

void WorldsBox2d::createPortal(){
    
    Portal *plat = new Portal( Portal::Orientation::HORIZONTAL, 50, 525, 35, 75 );
    portals.push_back(plat);
    
}

void WorldsBox2d::createBoundsModif(float x, float y, float w, float h) {
    
    b2Body*	 ground;
    if(world.world == NULL) {
        ofLog(OF_LOG_WARNING, "ofxBox2d:: - Need a world, call init first! -");
        return;
    }
    //if(ground!=NULL) world.world->DestroyBody(ground);
    
    b2BodyDef bd;
    bd.position.Set(0, 0);
    ground = world.world->CreateBody(&bd);
    
    b2EdgeShape shape;
    
    ofRectangle rec(x/OFX_BOX2D_SCALE, y/OFX_BOX2D_SCALE, w/OFX_BOX2D_SCALE, h/OFX_BOX2D_SCALE);
    
    dataPlatform * data = new dataPlatform;
    data->setSprite(Sprite::PLATFORM);
    
    //right wall
    shape.Set(b2Vec2(rec.x+rec.width, rec.y), b2Vec2(rec.x+rec.width, rec.y+rec.height));
    ground->CreateFixture(&shape, 0.0f);
    ground->SetUserData(data);
    
    //left wall
    shape.Set(b2Vec2(rec.x, rec.y), b2Vec2(rec.x, rec.y+rec.height));
    ground->CreateFixture(&shape, 0.0f);
    ground->SetUserData(data);
    
    // top wall
    shape.Set(b2Vec2(rec.x, rec.y), b2Vec2(rec.x+rec.width, rec.y));
    ground->CreateFixture(&shape, 0.0f);
    ground->SetUserData(data);
    
    // bottom wall
    shape.Set(b2Vec2(rec.x, rec.y+rec.height), b2Vec2(rec.x+rec.width, rec.y+rec.height));
    ground->CreateFixture(&shape, 0.0f);
    ground->SetUserData(data);
    
}




