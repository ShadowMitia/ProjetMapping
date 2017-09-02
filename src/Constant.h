//
//  Constant.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//
#pragma once
#include "PhysicalizedElement/PhysicalizedElement.h"

namespace VarConst
{
	constexpr const int UNIT = 240;
	//constexpr const int WidthWorld2D = 20 * UNIT;
	//constexpr const int HeightWorld2D = 4 * UNIT;
    constexpr const int WidthWorld2D = 2240;
    constexpr const int HeightWorld2D = 160;
    
    
	constexpr const float speedAvatar = 3.0f; // impul
	constexpr const float speedAvatarMax = 5.0f;
	constexpr const float speedAvatarAirControl = 3.0f;
	constexpr const float speedAvatarAirControlMax = 10.0f;
    constexpr const float impulseJumpAvatar = 10.0f;
	constexpr const float densityAvatar = 10.0f;
    constexpr const float bounceAvatar = 0.03f;
    constexpr const float frictionAvatar = 0.0f;

}

enum class Sprite { AVATAR, FOOT, WATER, PLATFORM, BLOCK, UNKNOWN };
enum class Direction { LEFT, RIGHT, TOP, LOW, JUMP };
enum class Deplacement { PLATFORM , TOP, LADDER, JUMP };
enum class Viewpoint { MODE_ANGLE, MODE_PERSPECTIVE };

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

  PhysicalizedElement* Element;

private:
  Sprite sprite = Sprite::UNKNOWN;
    
};
