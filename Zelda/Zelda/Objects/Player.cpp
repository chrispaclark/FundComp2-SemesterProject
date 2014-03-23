//
//  Player.cpp
//  Zelda
//
//  Created by John Lake on 3/14/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#include "Player.h"
#include <iostream> 
using namespace std;




    //Used in collisions, so that a sprite doesn't get stuck in a wall.
void Player::undoUpdatePosition(){
    xScreen -= xVel;
    yScreen -= yVel;
    xCanvas -= xVel;
    yCanvas -= yVel;
    xVel-= xAcc;
    yVel -= yAcc;
    setBounds(xCanvas,yCanvas,xCanvas+width,yCanvas+height);
}

