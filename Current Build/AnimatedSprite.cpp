//
//  AnimatedSprite.cpp
//  Zelda
//
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#include <iostream> 

#include "Sprite.h"
#include "AnimatedSprite.h"

using namespace std; 

AnimatedSprite::AnimatedSprite()
: Sprite()
{
    numFrames = 1;
}

    //Used for animation.  UPDATE ACCORDINGLY.
void AnimatedSprite::setNumFrames(int n)
{
    numFrames = n;
}

void AnimatedSprite::updateFrame()
{
    frame++;
    if(frame>=numFrames) frame=0;
    src.x = src.w * int(((SDL_GetTicks()/100) % numFrames));
}



void AnimatedSprite::setSpriteRow(int s)
{
    spriteRow = s;
    src.y = src.h*spriteRow;
}



int AnimatedSprite::getSpriteRow()
{
    return spriteRow;
}

int AnimatedSprite::getNumFrames()
{
    return numFrames;
}

