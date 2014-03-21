// GameEngine.cpp
// implementation for GameEngine class

#include "GameEngine.h"
#include "Functions.h"

GameEngine::GameEngine()
{
	if (!initialize())
	{
		cout << "Error Initializing GameEngine Class Object!!!" << endl;
		exit(1);
	}
	TileTexture.setRenderer(geRenderer);
	TileTexture.loadFromFile("Images/ZeldaBGSpriteSheet-LA.png");
}

GameEngine::~GameEngine()
{
	// destroy SDL components and direct pointers to null
	SDL_DestroyRenderer(geRenderer);
	SDL_DestroyWindow(geWindow);

	geRenderer = nullptr;
	geWindow = nullptr;
}

int GameEngine::initialize()
{
	// Initializes success
	int success = true;

	// Initialize SDL and its components
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		logSDLError(cout, "SDL_Init");
		success = false;
	}
	else
	{
		//Enable VSync
		if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
		{
			printf("Warning: VSync not enabled!");
		}
		else
		{
			// Initialize PNG image loading
			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			{
				logSDLError(cout, "IMG_Init");
				success = false;
			}
			else
			{
				// Create Window
				geWindow = SDL_CreateWindow("ZeldaProject", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
				if (geWindow == nullptr)
				{
					logSDLError(cout, "CreateWindow");
					success = false;
				}
				else
				{
					// Create Renderer for gameWindow
					geRenderer = SDL_CreateRenderer(geWindow, -1, SDL_RENDERER_ACCELERATED);
					if (geRenderer == nullptr)
					{
						logSDLError(cout, "CreateRenderer");
						success = false;
					}
					else
					{
						// Initialize the renderer draw color
						int RED = 255;
						int BLUE = 255;
						int GREEN = 255;
						int ALPHA = 255;
						SDL_SetRenderDrawColor(geRenderer, RED, BLUE, GREEN, ALPHA);
					}
				}

			}
		}
	}
	return success;
}

void GameEngine::drawSomething()
{
	// Create SDL_Rect over which rectangle is drawn
	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

	// Draw Green Rectangle
	SDL_SetRenderDrawColor(geRenderer, 25, 150, 75, 255);
	SDL_RenderFillRect(geRenderer, &fillRect);
}

SDL_Renderer* GameEngine::getRenderer()
{
	return geRenderer;
}

SDL_Texture* GameEngine::getTileTex()
{
	return TileTexture.getTexture();
}

void GameEngine::renderBackground(Tile* tiles[], SDL_Rect tileSprites[])
{
	for (int i = 0; i < TOTAL_TILES; i++)
	{
		SDL_RenderCopy(getRenderer(), getTileTex(), &tileSprites[tiles[i]->getTileType()], &tiles[i]->getRect());
	}
}

int GameEngine::mapTiles(Tile* tiles[], SDL_Rect tileSprites[])
{
	// Success flag
	int success = true;

	// Open the map
	ifstream map("Other/rbTileMap.map");
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
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType;
			// Read tile from map
			map >> tileType;
			cout << i << ": " << tileType << endl;

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
				cout << "Error loading map: Invalid tile type at" << i << endl;
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

		//Clip the sprite sheet
		if (success)
		{
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
		}
	}

	return success;
}

void GameEngine::play()
{
	// set of Tiles in background;
	Tile* tileSet[TOTAL_TILES];
	SDL_Rect tileSprites[TYLE_TYPES];

	if (!mapTiles(tileSet, tileSprites))
	{
		cout << "Error loading tiles from map!" << endl;
		exit(1);
	}

	int quit = false;
	SDL_Event e;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
			else if (e.type == SDL_KEYDOWN)
			{
				// select action based on input
				switch (e.key.keysym.sym)
				{
				case SDLK_q:
					quit = true;
					break;
				}
			}
		}
		// Fill the screen with black background
		SDL_SetRenderDrawColor(geRenderer, 0, 0, 0, 255);
		SDL_RenderClear(geRenderer);

		// Tile Background
		renderBackground(tileSet, tileSprites);

		// Draw green square (just because.... green is cool)
		// drawSomething();

		// Update Window
		SDL_RenderPresent(geRenderer);
	}
}