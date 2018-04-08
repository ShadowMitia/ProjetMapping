//
//  Constant.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//
#pragma once


#define nbLayer 3 //8

namespace VarConst
{

    
    constexpr const float gravity = 13.0f;
    constexpr const float speedAvatarMax = 1.80; // v max
    constexpr const float densityAvatar = 4.0f;
    constexpr const float bounceAvatar = 0.0001f;
    constexpr const float frictionAvatar = 1.0f;
    constexpr const float impulseJumpAvatarMAX = 5.9f;			// impulsion de base pour les sauts
    constexpr const float impulseJumpAvatarMIN = 2.6f;
    constexpr const uint64_t coyoteTime = 70000000;
    
    
    
    
    //constexpr const float impulseJumpAvatar = 15.0f;			// impulsion de base pour les sauts
    
    //constexpr const float impulseJumpAvatar = 10.3f;			// impulsion de base pour les sauts
    
    constexpr const float impulseLateralJumpAvatar = 5.f;	// var pour "lisser" la courbe de saut + on la monte, + la cloche s'applatit
    constexpr const float attenuationImpulseJump = 0.84f;	// var pour "attenuer" les saut latéraux par rapport aux sauts droits
    constexpr const int MAX_WIIMOTES = 4;
    
}

//enum class Direction { LEFT, RIGHT, TOP, LOW, JUMP };


