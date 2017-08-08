//
//  Constant.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//
#pragma once

#define UNIT 240
#define WidthWord2D  20*UNIT
#define HeightWord2D 4*UNIT

enum class Sprite { AVATRA, FOOT, WATER, PLATFORM };
enum class Direction { LEFT, RIGHT, TOP, LOW, JUMP };

class dataSprite{
public:
    Sprite getSprite(){
        return sprite;
    }
    void setSprite(Sprite _sprite){
        sprite = _sprite;
    }
private:
    Sprite sprite;
    
};