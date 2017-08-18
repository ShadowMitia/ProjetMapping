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
	constexpr const int WidthWorld2D = 20 * UNIT;
	constexpr const int HeightWorld2D = 4 * UNIT;

	constexpr const float speedAvatar = 15.0f;
	constexpr const float speedAvatarMax = 30.0f;
	constexpr const float impulseJumpAvatar = 200.0f;

}

enum class Sprite { AVATAR, FOOT, WATER, PLATFORM, BLOCK, UNKNOWN };
enum class Direction { LEFT, RIGHT, TOP, LOW, JUMP };
enum class Viewpoint { MODE_1, MODE_2 };

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
