// MyTexture.h
// implementation for texture wrapper class

#ifndef MYTEXTURE_H
#define MYTEXTURE_H

#include <iostream>
#include <string>
#include <cstdlib>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

using namespace std;

class MyTexture
{
public:
	//Initializes variables
	MyTexture();

	//Deallocates memory
	~MyTexture();

	//The renderer cannot be initialized passed in on GameEngine initialization because the renderer
	//is not available until after the initialize() function runs.
	void setRenderer(SDL_Renderer*);

	//Loads image at specified path
	bool loadFromFile(string path);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	SDL_Texture* getTexture();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;

	// pointer to GameEngine Renderer
	SDL_Renderer* geTexRenderer;
};

#endif