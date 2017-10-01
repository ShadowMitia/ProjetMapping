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
    
	constexpr const float gravity = 30.0f;
	//constexpr const float gravity = 0.0f;

	constexpr const float speedAvatar = 1.0f;  // a
	constexpr const float speedAvatarMax = 1.75f; // v max
	constexpr const float speedAvatarAirControl = 1.0f; 
	constexpr const float speedAvatarAirControlMax = 1.75f;
    constexpr const float coefFrotementAir = 0.04; 
	constexpr const float densityAvatar = 10.0f;
	constexpr const float bounceAvatar = 0.0001f;
	constexpr const float frictionAvatar = 0.0f;

    constexpr const float impulseJumpAvatar = 15.0f;			// impulsion de base pour les sauts

	//constexpr const float impulseJumpAvatar = 10.3f;			// impulsion de base pour les sauts

	constexpr const float impulseLateralJumpAvatar = 5.f;	// var pour "lisser" la courbe de saut + on la monte, + la cloche s'applatit
	constexpr const float attenuationImpulseJump = 0.84f;	// var pour "attenuer" les saut latéraux par rapport aux sauts droits

    
    constexpr const int MAX_WIIMOTES = 4;

}

enum class Sprite { AVATAR, AVATAR_CLONE, FOOT, WATER, PLATFORM, BLOCK, PICKUP, UNKNOWN };
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
    
    Sprite sprite = Sprite::UNKNOWN;
    
};

