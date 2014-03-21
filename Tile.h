// Tile.h
// Contains the Tile class interface. Tiles are supposed to be called and rendered accross the screen filling it and making a background

#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <string>
#include <cstdlib>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "Functions.h"

// Tile properties
#define TILE_SIDELENGTH 40	// Ensure that this is proportional to the screensize
#define TILE_SS_SIDELENGTH 16

#define TOTAL_TILES 192
#define TYLE_TYPES 9
#define TILE_GREENGRASS 0
#define TILE_BROWNGRASS 1
#define TILE_FLOWER1 2
#define TILE_DEFISH_TL 3
#define TILE_DEFISH_TM 4
#define TILE_DEFISH_TR 5
#define TILE_DEFISH_BL 6
#define TILE_DEFISH_BM 7
#define TILE_DEFISH_BR 8



using namespace std;

class Tile
{
public:
	// Constructor
	Tile(int x, int y, int type);

	// Destructor
	~Tile();

	// Get/Set for tile class:
	int getTileType();

	SDL_Rect getRect();

	// Experimental: Draw Tile to screen from within class
	//void drawTile();

private:
	// Type of tile
	int tileType;

	// Array of rects of sprite locations
	SDL_Rect tiles[TYLE_TYPES];

	// Tile dimensions and location
	SDL_Rect tileDimensions;

	// Pointer to GameEngine Renderer
	SDL_Renderer* geTileRenderer;
};

#endif