//
//  Constant.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//
#pragma once



namespace VarConst
{
    constexpr const int UNIT = 240;
    //constexpr const int WidthWorld2D = 20 * UNIT;
    //constexpr const int HeightWorld2D = 4 * UNIT;
    constexpr const int WidthWorld2D = 464;
    constexpr const int HeightWorld2D = 464;
    
    constexpr const float gravity = 13.0f;
    constexpr const float speedAvatarMax = 1.80f; // v max
    constexpr const float densityAvatar = 20.0f;
    constexpr const float bounceAvatar = 0.0001f;
    constexpr const float frictionAvatar = 0.0f;
    constexpr const float impulseJumpAvatarMAX = 5.9f;			// impulsion de base pour les sauts
    constexpr const float impulseJumpAvatarMIN = 2.6f;
    constexpr const float speedAvatarAirControlMax = 1.5f;
    constexpr const uint64_t coyoteTime = 70000000;
    
    constexpr const float speedAvatar = 1.0f;  // a
    
    
    constexpr const float speedAvatarAirControl = 1.0f;
    constexpr const float coefFrotementAir = 0.00;
    
    
    //constexpr const float impulseJumpAvatar = 15.0f;			// impulsion de base pour les sauts
    
    //constexpr const float impulseJumpAvatar = 10.3f;			// impulsion de base pour les sauts
    
    constexpr const float impulseLateralJumpAvatar = 5.f;	// var pour "lisser" la courbe de saut + on la monte, + la cloche s'applatit
    constexpr const float attenuationImpulseJump = 0.84f;	// var pour "attenuer" les saut latéraux par rapport aux sauts droits
    constexpr const int MAX_WIIMOTES = 4;
    
}

/*
 Category bits:
 PLATFORM : 0x0001
 PORTAL   : 0x0002
 LADDER   : 0x0004
 CLONE    : 0x0008
 AVATAR   : 0x0016
 BLOCK    : 0x0032
 PICKUP   : 0x0064
 MUSHROOM : 0x0128
 */

//enum class Direction { LEFT, RIGHT, TOP, LOW, JUMP };


