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
    constexpr const int WidthWorld2D = 800;
    constexpr const int HeightWorld2D = 150;
    
	constexpr const float gravity = 15.0f;

	constexpr const float speedAvatar = 1.0f;
	constexpr const float speedAvatarMax = 2.0f;
	constexpr const float speedAvatarAirControl = 1.0f;
	constexpr const float speedAvatarAirControlMax = 1.7f;
    constexpr const float coefFrotementAir = 0.04;

    constexpr const float impulseJumpAvatar = 7.3f;			// impulsion de base pour les sauts
	constexpr const float impulseLateralJumpAvatar = 5.f;	// var pour "lisser" la courbe de saut + on la monte, + la cloche s'applatit
	constexpr const float attenuationImpulseJump = 0.84f;	// var pour "attenuer" les saut latéraux par rapport aux sauts droits

	constexpr const float densityAvatar = 10.0f;
    constexpr const float bounceAvatar = 0.03f;
    constexpr const float frictionAvatar = 4.0f;
    



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

