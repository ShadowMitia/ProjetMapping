//
//  WorldsBox2d.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//

#include "WorldsBox2d.h"
void WorldsBox2d::setup(){
    
    noGravityWell = ofRectangle(2500, 0, 1000, 800);
    
    world.init();
    world.setGravity(0, VarConst::gravity);
    world.setFPS(60.0);
    
    //createBoundsModif(0, 0, 3520, 800); // modif monde ici
    
    importPortal();
    
    createAvatar(0, 0);
    //createAvatar(90, 140);
    //createAvatar(2600, 90);
    //createAvatar(680, 140);
    
    Portal *temp = new Portal(ofRectangle(43, 0, 2, 150), this,PortalDirection::rightDirection,ConditionOutput::VerticalRight);
    porportal.push_back(temp);
    temp = new Portal(ofRectangle(237, 0, 2, 150), this,PortalDirection::leftDirection,ConditionOutput::VerticalLeft);
    porportal.push_back(temp);
    porportal[0]->linke(porportal[1], nullptr);
    porportal[1]->linke(porportal[0], nullptr);
    for (auto &avatar : avatars)
    {
        teleportables.push_back(avatar);
    }
    
    warterfalls = new Waterfalls(&world);
    
}
void WorldsBox2d::draw(){
    
    
    
    //porportal[0]->draw();
    for (auto &portal : porportal)
    {
        portal->draw();
    }
    
    for (auto &platform : platforms)
    {
        ofSetHexColor(0xFF0000);
        //platform->ground.draw();
    }
    for (auto &avatar : avatars) {
        avatar->draw();
        //cout << avatar->polygon.getPosition() << endl;
    }
    for (auto &clone : clones) {
        clone->draw();
    }
    //warterfalls->draw();
    world.draw();
    
}
void WorldsBox2d::createAvatar(int x, int y){
    Avatar * avatar = new Avatar(world.getWorld());
    avatar->setPosition(x, y);
    avatars.push_back(avatar);
}
void WorldsBox2d::update(){
    // supprimes les pickups collect√©s et les enleves de box2d et de la liste des pickups
    
    //pickups.erase(std::remove_if(pickups.begin(), pickups.end(), [&](auto& p){ bool res = p->isCollected(); if (res) { std::remove(teleportables.begin(), teleportables.end(), p); world.getWorld()->DestroyBody(p->pickUp.body);} return res; }), pickups.end());
    

    
    world.update();
    
    // delect clone
    // ne pas touché
    
    
    for (int i = 0; i< clones.size(); ++i) {
        if (clones[i]->statut>1) {
            // téléportation
            delete clones[i];
            clones.erase(clones.begin()+i);
            --i;
        }
        else{clones[i]->update();} // update clone
    }

    for (std::size_t j = 0; j < avatars.size(); j++)
    {
        //avatars[j]->processPerspectivePortals(perspectivePortals);
        avatars[j]->presUpdate();
        
        //avatars[j]->modeDeplace = Deplacement::PLATFORM;
        for (std::size_t i = 0; i < ladders.size(); i++) {
            /*if (ladders[i]->inside(avatars[j]))
             {
             avatars[j]->modeDeplace = Deplacement::LADDER;
             }*/
            
        }
        avatars[j]->update(noGravityWell);
    }
    //warterfalls->update();
}
void WorldsBox2d::createPlatform(ofPolyline polyline){
    Platform* edge = new Platform;
    edge->create(world.getWorld(), polyline);
    platforms.push_back(edge);
}
void WorldsBox2d::createLadder(ofPolyline polyline){
    Ladder* edge = new Ladder();
    edge->create(world.getWorld(), polyline);
    ladders.push_back(edge);
}
void WorldsBox2d::createPortal(){
    //Portal *plat = new Portal( Portal::Orientation::HORIZONTAL, 50, 525, 35, 75 );
    //portals.push_back(plat);
}
void WorldsBox2d::createBoundsModif(float x, float y, float w, float h) {
    ofPolyline temp;
    temp.addVertex(ofPoint(x,y));
    temp.addVertex(ofPoint(w,y));
    temp.addVertex(ofPoint(w,h));
    temp.addVertex(ofPoint(x,h));
    temp.addVertex(ofPoint(x,y));
    createPlatform(temp);
}
/// attention code deguelas ///
void WorldsBox2d::importPortal(){
}