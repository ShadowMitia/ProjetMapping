//
//  Constant.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//
#pragma once

constexpr const int UNIT = 240;
constexpr const int WidthWorld2D = 20 * UNIT;
constexpr const int HeightWorld2D = 4 * UNIT;

enum class Sprite { AVATAR, FOOT, WATER, PLATFORM, BLOCK, UNKNOWN };
enum class Direction { LEFT, RIGHT, TOP, LOW, JUMP };

class dataSprite {
public:

  Sprite getSprite()
  {
    return sprite;
  }

  void setSprite(Sprite _sprite)
  {
    sprite = _sprite;
  }

private:
  Sprite sprite = Sprite::UNKNOWN;
    
};