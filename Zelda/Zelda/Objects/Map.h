//
//  Map.h
//  Zelda
//
//  Created by John Lake on 3/23/14.
//  Copyright (c) 2014 John Lake. All rights reserved.
//

#ifndef __Zelda__Map__
#define __Zelda__Map__

#include <iostream>
#include "Player.h"
#include "Tile.h"
#include <string>


class Map{

public:
    void setRenderer(SDL_Renderer*);
    void renderBackground();
    int mapTiles(string);
    void initializeTileSprites();
    int touchesWall(Player&);
private:
    Tile * tiles[TOTAL_TILES];
    SDL_Rect tileSprites[TYLE_TYPES];
    SDL_Renderer *r;
    SDL_Texture * tileSetSS;
    
};

#endif /* defined(__Zelda__Map__) */
