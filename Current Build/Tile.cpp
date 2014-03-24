//
//  Tile.cpp
//  Zelda
//
//  Created by John Lake on 3/23/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#include "Tile.h"


#include <iostream>
#include "Tile.h"

Tile::Tile(int x, int y, int type)
{
        // Set the tile dimensions and location
	tileDimensions.x = x;
	tileDimensions.y = y;
	tileDimensions.w = TILE_SIDELENGTH;
	tileDimensions.h = TILE_SIDELENGTH;
    bounds.setBounds(x,y,x+TILE_SIDELENGTH,y+TILE_SIDELENGTH); 

	tileType = type;
}

Tile::~Tile()
{
        // Deconstruct dimensions
	tileDimensions.x = 0;
	tileDimensions.y = 0;
	tileDimensions.w = 0;
	tileDimensions.h = 0;

        // Direct pointer for GameEngine Renderer to null
	geTileRenderer = nullptr;
}

int Tile::getTileType()
{
	return tileType;
}

SDL_Rect * Tile::getRect()
{
	return &tileDimensions;
}

Boundary Tile::getBounds(){
    return bounds;
}