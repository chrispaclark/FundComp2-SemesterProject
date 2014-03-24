// GameEngine.h
// contains the interface for the GameEngine class which contains all game assets
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "Tile.h"
#include "Functions.h"
#include "Player.h"
#include "Music.h"
#include "Map.h"

// constant integers for screen size
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define PLAYER_VEL 4

using namespace std;

class GameEngine
{
public:
	// constructor, runs initialize
	GameEngine();

	// destructor destroys SDL components and sets pointers to null
	~GameEngine();

	// Makes error logging easier
	void logSDLError(ostream &os, const string &msg);

	// initialize objects, SDL, etc
	int initialize();

	// Draw a square with a black background
	void drawSomething();

	// Render the background tiles
	void renderBackground(Tile* tiles[], SDL_Rect tileSprites[]);

	// Load the tile map from a file
	int mapTiles(Tile* tiles[], SDL_Rect tileSprites[], string str);

	//Get/Set Functions:
	SDL_Renderer* getRenderer();

	SDL_Texture* getTileTex();

	// The Great Play Function (basically main)
	void play();

private:
	// game window where all textures are drawn
	SDL_Window* geWindow;
	SDL_Renderer* geRenderer;

	// Player character animated sprite
	Player Link;

	// Map object for loading levels
	Map Background;
	
	// Background Music
	Music LostWoods;

};

#endif