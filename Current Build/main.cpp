//
//  main.cpp
//  Zelda
// main.cpp
//  Created by John Lake, Thomas Deranek, Garrett Duffy, and Chris Clark
//  Copyright (c) 2014 John Lake, Thomas Deranek, Garrett Duffy, and Chris Clark. All rights reserved.

#include <iostream>

#include "SDL.h" 
#include "Map.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "Music.h"
#include "GameEngine.h"

using namespace std;

#undef main

int main (void)
{
	GameEngine Awesomeness;

	Awesomeness.play();

	return 0;
}

