//
//  Music.h
//  Zelda
//
//  Created by Christian Clark on 3/24/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#ifndef __Zelda__Music__
#define __Zelda__Music__

#include <iostream>
#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <string>

#endif /* defined(__Lab8__Music__) */

class Music
{
public:
    Music();    //constructor
    ~Music();   //deconstructor
    void play();    //plays music
    void stop();    //stops music
private:
    Mix_Music * bgMusic = NULL;    //the music that will be played
};
