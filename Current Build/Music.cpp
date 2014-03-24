//  Music.cpp
//
//  Created by Christian Clark, Thomas Deranek, Garrett Duffy, and John Lake
//  Copyright (c) 2014 John Lake. All rights reserved.

#include "Music.h"

Music::Music(){
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    
    //Load music
    bgMusic = Mix_LoadMUS( "Sounds/LostWoodsDubstep.wav" );
    if( bgMusic == NULL )
    {
        printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

Music::~Music()
{
    //stop the music
    this->stop();
    
    //Free the music
    Mix_FreeMusic( bgMusic );
    bgMusic = NULL;
}

void Music::play()
{
    //Play the music
    Mix_PlayMusic( bgMusic, -1 );
}

void Music::stop()
{
    //Stop the music
    Mix_HaltMusic();
}