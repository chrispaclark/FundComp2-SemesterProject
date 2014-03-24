//
//  Tile.h
//  Zelda
//
//  Created by John Lake on 3/23/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#ifndef __Zelda__Tile__
#define __Zelda__Tile__


#include <iostream>
#include "Boundary.h"
#include <string>
#include <cstdlib>
#include "SDL.h"
#define TILE_SIDELENGTH 40	// Ensure that this is proportional to the screensize
#define TILE_SS_SIDELENGTH 16

#define TOTAL_TILES 192
#define TYLE_TYPES 50

#define TILE_GREENGRASS 0
#define TILE_BROWNGRASS 1
#define TILE_FLOWER1 2

#define TILE_DEFISH_TL 3
#define TILE_DEFISH_TM 4
#define TILE_DEFISH_TR 5
#define TILE_DEFISH_BL 6
#define TILE_DEFISH_BM 7
#define TILE_DEFISH_BR 8

#define TILE_DIRTWALL_BL 9
#define TILE_DIRTWALL_ML 10
#define TILE_DIRTWALL_BR 11
#define TILE_DIRTWALL_MR 12
#define TILE_DIRTWALL_TLBC 13
#define TILE_DIRTWALL_TM 14
#define TILE_DIRTWALL_TLBE 15
#define TILE_DIRTWALL_TRBE 16

#define TILE_BROWNPLAINS_TL 17
#define TILE_BROWNPLAINS_BL 18
#define TILE_BROWNPLAINS_TR 19
#define TILE_BROWNPLAINS_BR 20

#define TILE_GREENPLAINS_TL 21
#define TILE_GREENPLAINS_BL 22
#define TILE_GREENPLAINS_TR 23
#define TILE_GREENPLAINS_BR 24

#define TILE_GRASS_3x3_TL 25
#define TILE_GRASS_3x3_ML 26
#define TILE_GRASS_3x3_BL 27
#define TILE_GRASS_3x3_TM 28
#define TILE_GRASS_3x3_MM 29
#define TILE_GRASS_3x3_BM 30
#define TILE_GRASS_3x3_TR 31
#define TILE_GRASS_3x3_MR 32
#define TILE_GRASS_3x3_BR 33

#define TILE_GREENPRAIRIE_TL 34
#define TILE_GREENPRAIRIE_ML 35
#define TILE_GREENPRAIRIE_BL 36
#define TILE_GREENPRAIRIE_TM 37
#define TILE_GREENPRAIRIE_MM 38
#define TILE_GREENPRAIRIE_BM 39
#define TILE_GREENPRAIRIE_TR 40
#define TILE_GREENPRAIRIE_MR 41
#define TILE_GREENPRAIRIE_BR 42

#define TILE_SAND 43

#define TILE_TREEONWHITE_TL 44
#define TILE_TREEONWHITE_BL 45
#define TILE_TREEONWHITE_TR 46
#define TILE_TREEONWHITE_BR 47

#define TILE_TREEONGREEN_TL 48
#define TILE_TREEONGREEN_TR 49

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

	SDL_Rect * getRect();
    Boundary getBounds(); 

        // Experimental: Draw Tile to screen from within class
        //void drawTile();

private:
        // Type of tile
	int tileType;

        // Array of rects of sprite locations
	SDL_Rect tiles[TYLE_TYPES];

    Boundary bounds;

        // Tile dimensions and location
	SDL_Rect tileDimensions;
    
        // Pointer to GameEngine Renderer
	SDL_Renderer* geTileRenderer;
};



#endif /* defined(__Zelda__Tile__) */
