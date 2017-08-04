//
//  WorldsBox2d.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//

#include "WorldsBox2d.h"

void WorldsBox2d::setup(){
    
    world.init();
    world.setGravity(0, 10);
    //world.createGround(0,0,1000, 600);
    world.createBounds();
    world.setFPS(60.0);
    //world.registerGrabbing();


    /*/////// Portal ///////
    portals.emplace_back( Portal::Orientation::HORIZONTAL, 50, 525, 35, 75, world );
    portals.emplace_back( Portal::Orientation::HORIZONTAL, 200, 525, 35, 75, world );

	portals.emplace_back(Portal::Orientation::HORIZONTAL, 400, 525, 35, 75, world);
	portals.emplace_back(Portal::Orientation::HORIZONTAL, 400, 325, 35, 75, world);
    
    portals[0].linkTo(&portals[1]);
	portals[3].linkTo(&portals[2]);
    ///// Portal /////////*/

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

	for (int i = 0; i < circles.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		circles[i].get()->draw();
	}

    for (auto &avatar : avatars) {
        avatar.draw();
    }

    
    for (auto &platform : platforms) {
        platform->draw();
    }
  
}

void WorldsBox2d::update(){
    
	world.update();
    for (auto &avatar : avatars) {
        avatar.update();
    }
    for (auto &portal : portals) {
        portal->update(avatars);
    }

}

void WorldsBox2d::createAvatar(){
	avatars.emplace_back();
    avatars.back().create(world.getWorld());
    avatars.back().polygon.setData(new typeBox2d);
    typeBox2d *sd  = (typeBox2d*) avatars.back().polygon.getData();
    sd->type = typeBox2d::Type::AVATAR;
    avatars.back().polygon.setPosition(100, 100);
}

void WorldsBox2d::createPlatform(ofPolyline _polyline){
    
    Platform *edge = new Platform;
    edge->ground.addVertexes(_polyline);
    edge->ground.setPhysics(0.0, 0.1, 0.7);
    edge->ground.create(world.getWorld());
    platforms.push_back(edge);

}


