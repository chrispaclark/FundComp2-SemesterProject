// GameEngine.cpp
// implementation for GameEngine class
//  Created by John Lake, Thomas Deranek, Garrett Duffy, and Chris Clark
//  Copyright (c) 2014 John Lake, Thomas Deranek, Garrett Duffy, Chris Clark. All rights reserved.

#include "GameEngine.h"

GameEngine::GameEngine()
{
	if (!initialize())
	{
		cout << "Error Initializing GameEngine Class Object!!!" << endl;
		exit(1);
	}
	// Set up player renderer
	Link.setRenderer(geRenderer);

	// Set up map renderer
	Background.setRenderer(geRenderer);

	// Load the tiles image into a texture
	Background.loadFromFile("Sprites/ZeldaBGSpriteSheet-LA.png");

	//Load the sprite sheet image for Link into a texture
	Link.loadIMGForTexture("Sprites/Link.png");
}

GameEngine::~GameEngine()
{
	// destroy SDL components and direct pointers to null
	SDL_DestroyRenderer(geRenderer);
	SDL_DestroyWindow(geWindow);

	geRenderer = nullptr;
	geWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
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
		//Enable VSync -- NOTE! slows down game ( a lot! )
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

SDL_Renderer* GameEngine::getRenderer()
{
	return geRenderer;
}


void GameEngine::play()
{
	// Initialize game-ending variable
	int gameOver = 0;


	Link.setSource(0, 0, 43, 49);
	Link.setScreenLocation(300, 40);
	Link.setCanvasLocation(300, 40);

	Link.setSize(43, 48);
	Link.setNumFrames(2);
	Link.setSpriteRow(0);

	Background.mapTiles("Other/rbTileMap.map");

	//play background music
	LostWoods.play();

	// Initialize SDL_Event to handle user input to game
	SDL_Event e;

	// while loop will run until it receives a gameOver signal (program shuts down)
	while (!gameOver)
	{
		// Process all SDL_Events
		while (SDL_PollEvent(&e))
		{
			switch (e.type) 
			{
			// If red x button hit, quit game
			case SDL_QUIT:
				gameOver = 1;
				break;
			// If a key is pressed increase respective velocity
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					Link.setXVel(-PLAYER_VEL);
					Link.setSpriteRow(5);
					Link.setNumFrames(10);
					break;
				case SDLK_RIGHT:
					Link.setXVel(PLAYER_VEL);
					Link.setSpriteRow(7);
					Link.setNumFrames(10);
					break;
				case SDLK_UP:
					Link.setYVel(-PLAYER_VEL);
					Link.setSpriteRow(6);
					Link.setNumFrames(10);
					break;
				case SDLK_DOWN:
					Link.setYVel(PLAYER_VEL);
					Link.setSpriteRow(4);
					Link.setNumFrames(10);
					break;
				}
				break;

			// If a key is pressed reset respective velocity
			case SDL_KEYUP:
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					if (Link.getXVel()<0)
						Link.setXVel(0);
					Link.setSpriteRow(1);
					Link.setNumFrames(3);
					break;

				case SDLK_RIGHT:
					if (Link.getXVel()>0)
						Link.setXVel(0);
					Link.setSpriteRow(3);
					Link.setNumFrames(3);
					break;

				case SDLK_UP:
					if (Link.getYVel()<0)
						Link.setYVel(0);
					
					Link.setNumFrames(1);
					Link.setSpriteRow(2);
					break;

				case SDLK_DOWN:
					if (Link.getYVel()>0)
						Link.setYVel(0);
					Link.setSpriteRow(0);
					Link.setNumFrames(3);
					break;
				}
				break;

			}
		}	// end of event handling while loop
		
		// Update links position on the screen
		Link.updatePosition();

		// if something is in link's way, stop him from moving through it
		if (Background.touchesWall(Link))
		{
			Link.undoUpdatePosition();
			Link.setVel(0, 0);
		}

		Link.updateFrame();

		// Set render clear color to black
		SDL_SetRenderDrawColor(geRenderer, 0, 0, 0, 255);

		// Clear renderer for latest frame
		SDL_RenderClear(geRenderer);

		// Render background from tile map
		Background.renderBackground();

		// Render Player to the screen
		Link.renderSprite();

		// Push renderer to the window
		SDL_RenderPresent(geRenderer);
	
		//Check if music is still playing or not
		//If there is no music playing
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			LostWoods.play();
		}
	}
}