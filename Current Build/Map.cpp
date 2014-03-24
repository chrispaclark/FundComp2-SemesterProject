//
//  Map.cpp
//  Zelda
//
//  Created by John Lake on 3/23/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//


#include <string>
#include <fstream>

#include "SDL.h"
#include "SDL_image.h"

#include "Map.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

Map::Map()
{
	// Define the the locations of the tile sprites on the SS
	initializeTileSprites();
}

int Map::mapTiles(const string s)
{
    // Success flag
	int success = true;

    // Open the map
	ifstream map(s.c_str());
	ifstream* pmap = &map;

    //if the map failed to load
	if (pmap == nullptr)
    {
		cout << "Failed to load tile map" << endl;
		success = false;
    }
	else
        {
            // Initialize the tiles
            // Set initial values for tile placement
			int x = 0, y = 0;
			for (int i = 0; i < TOTAL_TILES; i++)
            {
                //Determines what kind of tile will be made
				int tileType;

                // Read tile from map
				map >> tileType;
                //cout << i << ": " << tileType << endl;

            // Check to see if there was a problem reading the map
			if (map.fail())
            {
                // Stop loading map
				cout << "Error reading from map! Unexpected end of file" << endl;
				success = false;
				break;
            }

            // if the map reads in a valid tile number
			if ((tileType >= 0) && (tileType < TYLE_TYPES))
            {
				tiles[i] = new Tile(x, y, tileType);
            }
			else
            {
				//	cout << "Error loading map: Invalid tile type at" << i << endl;
				success = false;
				break;
            }

            // Move to next column
			x += TILE_SIDELENGTH;

            // Move to next row
			if (x >= SCREEN_WIDTH)
            {
				x = 0;
				y += TILE_SIDELENGTH;
            }
        }	// end for loop

    }
	return success;
}


void Map::initializeTileSprites()
{
	// Store the locations of each tile in order of: xpos, ypos, width, height

    tileSprites[TILE_GREENGRASS].x = 222;
    tileSprites[TILE_GREENGRASS].y = 154;
    tileSprites[TILE_GREENGRASS].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENGRASS].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_BROWNGRASS].x = 239;
    tileSprites[TILE_BROWNGRASS].y = 154;
    tileSprites[TILE_BROWNGRASS].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_BROWNGRASS].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_FLOWER1].x = 273;
    tileSprites[TILE_FLOWER1].y = 256;
    tileSprites[TILE_FLOWER1].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_FLOWER1].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DEFISH_TL].x = 35;
    tileSprites[TILE_DEFISH_TL].y = 52;
    tileSprites[TILE_DEFISH_TL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DEFISH_TL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DEFISH_TM].x = 35+17;
    tileSprites[TILE_DEFISH_TM].y = 52;
    tileSprites[TILE_DEFISH_TM].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DEFISH_TM].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DEFISH_TR].x = 35+17+17;
    tileSprites[TILE_DEFISH_TR].y = 52;
    tileSprites[TILE_DEFISH_TR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DEFISH_TR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DEFISH_BL].x = 35;
    tileSprites[TILE_DEFISH_BL].y = 52+17;
    tileSprites[TILE_DEFISH_BL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DEFISH_BL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DEFISH_BM].x = 35+17;
    tileSprites[TILE_DEFISH_BM].y = 52+17;
    tileSprites[TILE_DEFISH_BM].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DEFISH_BM].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DEFISH_BR].x = 35+17+17;
    tileSprites[TILE_DEFISH_BR].y = 52+17;
    tileSprites[TILE_DEFISH_BR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DEFISH_BR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DIRTWALL_BL].x = 52;
    tileSprites[TILE_DIRTWALL_BL].y = 239;
    tileSprites[TILE_DIRTWALL_BL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DIRTWALL_BL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DIRTWALL_ML].x = 52;
    tileSprites[TILE_DIRTWALL_ML].y = 239-17;
    tileSprites[TILE_DIRTWALL_ML].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DIRTWALL_ML].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DIRTWALL_BR].x = 52+17;
    tileSprites[TILE_DIRTWALL_BR].y = 239;
    tileSprites[TILE_DIRTWALL_BR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DIRTWALL_BR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DIRTWALL_MR].x = 52+17;
    tileSprites[TILE_DIRTWALL_MR].y = 239-17;
    tileSprites[TILE_DIRTWALL_MR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DIRTWALL_MR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DIRTWALL_TLBC].x = 171;
    tileSprites[TILE_DIRTWALL_TLBC].y = 188;
    tileSprites[TILE_DIRTWALL_TLBC].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DIRTWALL_TLBC].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DIRTWALL_TM].x = 18;
    tileSprites[TILE_DIRTWALL_TM].y = 188;
    tileSprites[TILE_DIRTWALL_TM].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DIRTWALL_TM].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DIRTWALL_TLBE].x = 52;
    tileSprites[TILE_DIRTWALL_TLBE].y = 205;
    tileSprites[TILE_DIRTWALL_TLBE].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DIRTWALL_TLBE].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_DIRTWALL_TRBE].x = 69;
    tileSprites[TILE_DIRTWALL_TRBE].y = 205;
    tileSprites[TILE_DIRTWALL_TRBE].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_DIRTWALL_TRBE].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_BROWNPLAINS_TL].x = 103;
    tileSprites[TILE_BROWNPLAINS_TL].y = 86;
    tileSprites[TILE_BROWNPLAINS_TL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_BROWNPLAINS_TL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_BROWNPLAINS_BL].x = 103;
    tileSprites[TILE_BROWNPLAINS_BL].y = 86+17;
    tileSprites[TILE_BROWNPLAINS_BL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_BROWNPLAINS_BL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_BROWNPLAINS_TR].x = 103+17;
    tileSprites[TILE_BROWNPLAINS_TR].y = 86;
    tileSprites[TILE_BROWNPLAINS_TR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_BROWNPLAINS_TR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_BROWNPLAINS_BR].x = 103+17;
    tileSprites[TILE_BROWNPLAINS_BR].y = 86+17;
    tileSprites[TILE_BROWNPLAINS_BR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_BROWNPLAINS_BR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPLAINS_TL].x = 103;
    tileSprites[TILE_GREENPLAINS_TL].y = 120;
    tileSprites[TILE_GREENPLAINS_TL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPLAINS_TL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPLAINS_BL].x = 103;
    tileSprites[TILE_GREENPLAINS_BL].y = 120 + 17;
    tileSprites[TILE_GREENPLAINS_BL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPLAINS_BL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPLAINS_TR].x = 103 + 17;
    tileSprites[TILE_GREENPLAINS_TR].y = 120;
    tileSprites[TILE_GREENPLAINS_TR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPLAINS_TR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPLAINS_BR].x = 103 + 17;
    tileSprites[TILE_GREENPLAINS_BR].y = 120 + 17;
    tileSprites[TILE_GREENPLAINS_BR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPLAINS_BR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GRASS_3x3_TL].x = 1;
    tileSprites[TILE_GRASS_3x3_TL].y = 86;
    tileSprites[TILE_GRASS_3x3_TL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GRASS_3x3_TL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GRASS_3x3_TM].x = 1 + 17;
    tileSprites[TILE_GRASS_3x3_TM].y = 86;
    tileSprites[TILE_GRASS_3x3_TM].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GRASS_3x3_TM].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GRASS_3x3_TR].x = 1 + 34;
    tileSprites[TILE_GRASS_3x3_TR].y = 86;
    tileSprites[TILE_GRASS_3x3_TR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GRASS_3x3_TR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GRASS_3x3_ML].x = 1;
    tileSprites[TILE_GRASS_3x3_ML].y = 86+17;
    tileSprites[TILE_GRASS_3x3_ML].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GRASS_3x3_ML].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GRASS_3x3_MM].x = 1 + 17;
    tileSprites[TILE_GRASS_3x3_MM].y = 86+17;
    tileSprites[TILE_GRASS_3x3_MM].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GRASS_3x3_MM].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GRASS_3x3_MR].x = 1 + 34;
    tileSprites[TILE_GRASS_3x3_MR].y = 86+17;
    tileSprites[TILE_GRASS_3x3_MR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GRASS_3x3_MR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GRASS_3x3_BL].x = 1;
    tileSprites[TILE_GRASS_3x3_BL].y = 86 + 34;
    tileSprites[TILE_GRASS_3x3_BL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GRASS_3x3_BL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GRASS_3x3_BM].x = 1 + 17;
    tileSprites[TILE_GRASS_3x3_BM].y = 86 + 34;
    tileSprites[TILE_GRASS_3x3_BM].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GRASS_3x3_BM].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GRASS_3x3_BR].x = 1 + 34;
    tileSprites[TILE_GRASS_3x3_BR].y = 86 + 34;
    tileSprites[TILE_GRASS_3x3_BR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GRASS_3x3_BR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPRAIRIE_TL].x = 52;
    tileSprites[TILE_GREENPRAIRIE_TL].y = 137;
    tileSprites[TILE_GREENPRAIRIE_TL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPRAIRIE_TL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPRAIRIE_ML].x = 52;
    tileSprites[TILE_GREENPRAIRIE_ML].y = 137 + 17;
    tileSprites[TILE_GREENPRAIRIE_ML].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPRAIRIE_ML].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPRAIRIE_BL].x = 52;
    tileSprites[TILE_GREENPRAIRIE_BL].y = 137 + 17 + 17;
    tileSprites[TILE_GREENPRAIRIE_BL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPRAIRIE_BL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPRAIRIE_TM].x = 52 + 17;
    tileSprites[TILE_GREENPRAIRIE_TM].y = 137;
    tileSprites[TILE_GREENPRAIRIE_TM].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPRAIRIE_TM].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPRAIRIE_MM].x = 52 + 17;
    tileSprites[TILE_GREENPRAIRIE_MM].y = 137+17;
    tileSprites[TILE_GREENPRAIRIE_MM].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPRAIRIE_MM].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPRAIRIE_BM].x = 52 + 17;
    tileSprites[TILE_GREENPRAIRIE_BM].y = 137 + 17 + 17;
    tileSprites[TILE_GREENPRAIRIE_BM].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPRAIRIE_BM].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPRAIRIE_TR].x = 52 + 17 + 17;
    tileSprites[TILE_GREENPRAIRIE_TR].y = 137;
    tileSprites[TILE_GREENPRAIRIE_TR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPRAIRIE_TR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPRAIRIE_MR].x = 52 + 17 + 17;
    tileSprites[TILE_GREENPRAIRIE_MR].y = 137 + 17;
    tileSprites[TILE_GREENPRAIRIE_MR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPRAIRIE_MR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_GREENPRAIRIE_BR].x = 52 + 17 + 17;
    tileSprites[TILE_GREENPRAIRIE_BR].y = 137 + 17 + 17;
    tileSprites[TILE_GREENPRAIRIE_BR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_GREENPRAIRIE_BR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_SAND].x = 171;
    tileSprites[TILE_SAND].y = 256;
    tileSprites[TILE_SAND].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_SAND].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_SAND].x = 171;
    tileSprites[TILE_SAND].y = 256;
    tileSprites[TILE_SAND].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_SAND].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_TREEONWHITE_TL].x = 137;
    tileSprites[TILE_TREEONWHITE_TL].y = 120;
    tileSprites[TILE_TREEONWHITE_TL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_TREEONWHITE_TL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_TREEONWHITE_BL].x = 137;
    tileSprites[TILE_TREEONWHITE_BL].y = 120 + 17;
    tileSprites[TILE_TREEONWHITE_BL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_TREEONWHITE_BL].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_TREEONWHITE_TR].x = 137 + 17;
    tileSprites[TILE_TREEONWHITE_TR].y = 120;
    tileSprites[TILE_TREEONWHITE_TR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_TREEONWHITE_TR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_TREEONWHITE_BR].x = 137 + 17;
    tileSprites[TILE_TREEONWHITE_BR].y = 120 + 17;
    tileSprites[TILE_TREEONWHITE_BR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_TREEONWHITE_BR].h = TILE_SS_SIDELENGTH;

    tileSprites[TILE_TREEONGREEN_TL].x = 137;
    tileSprites[TILE_TREEONGREEN_TL].y = 103;
    tileSprites[TILE_TREEONGREEN_TL].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_TREEONGREEN_TL].h = TILE_SS_SIDELENGTH;
    
    tileSprites[TILE_TREEONGREEN_TR].x = 137 + 17;
    tileSprites[TILE_TREEONGREEN_TR].y = 103;
    tileSprites[TILE_TREEONGREEN_TR].w = TILE_SS_SIDELENGTH;
    tileSprites[TILE_TREEONGREEN_TR].h = TILE_SS_SIDELENGTH;
}

int Map::touchesWall(Player &p){
    for(int i = 0;i< TOTAL_TILES;i++)
	{
		// if the player is colliding with a wall type tile (consider seperating to two ifs to make clearer)
        if(p.collidesWith(tiles[i]) && tiles[i]->getTileType() >= 2 && tiles[i]->getTileType() <= 8)
            return 1;
        
    }
    return 0;
}


void Map::setRenderer(SDL_Renderer *geRenderer)
{
	geTileRenderer = geRenderer;

	if (geTileRenderer == nullptr)
	{
		cout << "Error: *geRenderer failed to pass to *geTileRenderer!" << endl;
		SDL_Delay(3000);
		exit(2);
	}
}

void Map::renderBackground()
{
	if (geTileRenderer == nullptr)
	{
		cout << "ERROR!!! Printing tiles with null renderer!" << endl;
		SDL_Delay(3000);
		exit(2);
	}

    for (int i = 0; i < TOTAL_TILES; i++)
    {
        SDL_RenderCopy(geTileRenderer, tileSetSS, &tileSprites[tiles[i]->getTileType()], tiles[i]->getRect());
	}
}

int Map::loadFromFile(string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		logSDLError(cout, "IMG_Load");
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(geTileRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			logSDLError(cout, "CreateTextureFromSurface");
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	tileSetSS = newTexture;
	return tileSetSS != NULL;
}