// Experiment.h
// Driver Program for Project files
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "GameEngine.h"
#include "Functions.h"
#include "Tile.h"

using namespace std;

// For some reason that I don't understand, this is necessary
#undef main

int main(void)
{
	// Instantiate GameEngine
	GameEngine Awesomeness;
	
	Awesomeness.play();

	return 0;
}