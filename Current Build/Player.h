//
//  Player.h
//  Zelda
//
//  Created by John Lake on 3/14/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#ifndef __Zelda__Player__
#define __Zelda__Player__

#include <iostream>
#include "AnimatedSprite.h"

class Player : public AnimatedSprite{
public:


    void undoUpdatePosition();

    
private:
    bool hasJumped;
    int jumpBase;
    int currentPlatform; 

        //Weapons, attributes, etc.
};

#endif /* defined(__Snow__Player__) */
