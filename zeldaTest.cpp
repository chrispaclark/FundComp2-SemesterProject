#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 515;
const int SCREEN_HEIGHT = 338;
const float MOVE_CONST = 2.5;

void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

class LTexture
{
public:
	// initialize vars
	LTexture();
	// deallocate mem
	~LTexture();
	bool loadFromFile(std::string path);
	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blender);
	void setAlpha(Uint8 alpha);
	void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);	//(x,y,srcRect,angle,cntr,flip)
	int getWidth();
	int getHeight();
private:
	SDL_Texture* oTexture;
	int mWidth;
	int mHeight;
};

// Global functions and data

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;
//Link sprites
SDL_Rect gLinkSpriteClips[4];
LTexture gLinkAndZeldaSS;
LTexture gBackground;

// Definitions for class fns
LTexture::LTexture()
{
	// Initialize
	oTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	// Call free to deallocate mem and point to NULLs
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	
	free();
	SDL_Texture* newTex = nullptr;
	SDL_Surface* loadedSurf = IMG_Load(path.c_str());
	if (loadedSurf == nullptr)
	{
		logSDLError(std::cout, "IMG_Load");
	}
	SDL_SetColorKey(loadedSurf, SDL_TRUE, SDL_MapRGB(loadedSurf->format, 0, 0, 0));
	newTex = SDL_CreateTextureFromSurface(gRenderer, loadedSurf);
	if (newTex == nullptr)
	{
		logSDLError(std::cout, "CreateTextureFromSurface");
	}
	mWidth  = loadedSurf->w;
	mHeight = loadedSurf->h;
	// Free surface ?? Why not newTex?
	SDL_FreeSurface(loadedSurf);
	// set oTexture
	oTexture = newTex;

	return (oTexture != nullptr);
}

void LTexture::free()
{
	if (oTexture != nullptr)
	{
		SDL_DestroyTexture(oTexture);
		oTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(oTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blender)
{
	SDL_SetTextureBlendMode(oTexture, blender);
}

void LTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(oTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	// Set rendering space and render to screen. In null event, mWidth and mHeight make it full screen
	SDL_Rect RenderQuad = { x, y, mWidth, mHeight };
	// If not null set width and height to clip sizes
	if (clip != nullptr)
	{
		RenderQuad.w = clip->w;
		RenderQuad.h = clip->h;
	}
	// Now render to screen at x,y, with RenderQuad w/h, rotated angle, 
	SDL_RenderCopyEx(gRenderer, oTexture, clip, &RenderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	bool success = true;
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		success = false;
		std::cout << "Error initializing SDL" << std::endl;
	}
	else
	{
		//Enable VSync
		if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
		{
			printf("Warning: VSync not enabled!");
		}
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		//Create Window
		gWindow = SDL_CreateWindow("Link is trapped in a box!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			logSDLError(std::cout, "CreateWindow");
			success = false;
		}
		
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == nullptr)
			{
				logSDLError(std::cout, "CreateRenderer");
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				// Initialize IMG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	//Load sprite sheet texture
	if (!gLinkAndZeldaSS.loadFromFile("Images/LinkAndZeldaSS.png"))	// Link Coordinates: (540, 40) w/h: 30/30
	{
		std::cout << "Failed to load Link and Zelda sprite sheet texture!\n";
		success = false;
	}
	else
	{
		if (!gBackground.loadFromFile("Images/Lost_Woods_Scene.png"))
		{
			std::cout << "Failed to load background scene!\n";
		}
		else
		{
			// select Link from the Sprite Sheet (facing forward w/sheild)
			gLinkSpriteClips[0].x = 540;
			gLinkSpriteClips[0].y = 41;
			gLinkSpriteClips[0].w = 30;
			gLinkSpriteClips[0].h = 32;
			// select Link from the Sprite Sheet (facing right)
			gLinkSpriteClips[1].x = 262;
			gLinkSpriteClips[1].y = 43;
			gLinkSpriteClips[1].w = 30;
			gLinkSpriteClips[1].h = 32;
			// select Link from the Sprite Sheet(facing upward)
			gLinkSpriteClips[2].x = 420;
			gLinkSpriteClips[2].y = 43;
			gLinkSpriteClips[2].w = 30;
			gLinkSpriteClips[2].h = 32;
		}
	}
	return success;
}

void close()
{
	//Free loaded images
	gLinkAndZeldaSS.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char** argv)
{
	if (!init())
	{
		std::cout << "Failed to initialize" << std::endl;
		return 1;
	}
	else
	{
		if (!loadMedia())
		{
			std::cout << "Failed to load media" << std::endl;
		}
		else
		{
			bool quit = false;
			int x = 350, y = 125;
			int linkIndex = 0;
			//render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
			SDL_RendererFlip flip = SDL_FLIP_NONE;
			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if (currentKeyStates[SDL_SCANCODE_UP])
				{
					y -= MOVE_CONST;
					flip = SDL_FLIP_NONE;
					linkIndex = 2;
				}
				if (currentKeyStates[SDL_SCANCODE_DOWN])
				{
					y += MOVE_CONST;
					linkIndex = 0;
				}
				if (currentKeyStates[SDL_SCANCODE_LEFT])
				{
					x -= MOVE_CONST;
					flip = SDL_FLIP_HORIZONTAL;
					linkIndex = 1;
				}
				if (currentKeyStates[SDL_SCANCODE_RIGHT])
				{
					x += MOVE_CONST;
					flip = SDL_FLIP_NONE;
					linkIndex = 1;
				}
				
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				SDL_RenderClear(gRenderer);
				//RenderBackground
				gBackground.render(0, 0, nullptr, 0.0, NULL);
				//Render link sprite 			//render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
				/*if (y >= 150 && x < 355 || x > 320) y = 150;
				if (y <= 125 && x < 355 || x > 320) y = 125;
				if (x >= 355 && y < 150 || y > 125) x = 355;
				if (x <= 320 && y < 150 || y > 125) x = 320;*/

				gLinkAndZeldaSS.render(x, y, &gLinkSpriteClips[linkIndex], 0.0, NULL, flip);
				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	return 0;
}