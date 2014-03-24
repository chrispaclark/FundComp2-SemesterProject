//
//  Map.h
//  Zelda
//
//  Created by John Lake on 3/23/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#ifndef __Zelda__Map__
#define __Zelda__Map__

#include <string>
#include <iostream>

#include "Player.h"
#include "Tile.h"
#include "MyTexture.h"



class Map{

public:
	// Constructor Initializes tile locations on SS
	Map();

	// Set the renderer that will be used by the map class
    void setRenderer(SDL_Renderer*);

	// Draw the background of tiles to the renderer
    void renderBackground();

	// Read in map file (tile locations on screen)
    int mapTiles(string);

	// Ran in constructor, stores locations of tile sprites in array of SDL_Rects
	void initializeTileSprites();

	// Checks to see if the player is touching a wall tile
    int touchesWall(Player&);

	//Get/Set Fns
	MyTexture getTextureWrap();

private:
	// Stores the tile map (drawn to screen)
    Tile * tiles[TOTAL_TILES];

	// Locations of Tile Sprites on SS texture 
    SDL_Rect tileSprites[TYLE_TYPES];

	// Renderer used for drawing tiles (pointer to same one in GameEngine
    SDL_Renderer *geTileRenderer;

	// SDL_Texture that holds the Tile SS
    MyTexture tileSetSS;
    
};

#endif /* defined(__Zelda__Map__) */
