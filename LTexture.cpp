// LTexture.cpp
// Contains the implementation for the LTexture class

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <iostream>
#include "LTexture.h"

// GLOBALS DECLARED HERE (still considering better options)
SDL_Renderer *gRenderer = nullptr;
TTF_Font *gFont = nullptr;

// Global Function, Seperate from class.
// Placed here because textures will be used nearly everywhere, and this file will then be accessible
// Function allows for easy error logging
void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

// Initializes variables to zero and directs pointers to nullptr
LTexture::LTexture()
{
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

// resets variables to zero and pointers to nullptr
LTexture::~LTexture()
{
	free();
}

void LTexture::loadFromFile(std::string path)
{
	// Get rid of pre-existing texture
	free();
	// The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image from the provided file path
	SDL_Surface* loadedSurf = IMG_Load(path.c_str());
	if (loadedSurf == nullptr)
		logSDLError(std::cout, "IMG_Load");
	else
	{
		SDL_SetColorKey(loadedSurf, SDL_TRUE, SDL_MapRGB(loadedSurf->format, 0, 255, 255));

		// Create texture from surface pixels. Utilizes a "global" renderer
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurf);
		if (newTexture == nullptr)
		{
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
		else
		{
			// Get image dimensions
			mWidth = loadedSurf->w;
			mHeight = loadedSurf->h;
		}
		// Free the temporary surface
		SDL_FreeSurface(loadedSurf);
	}
	// Return success
	mTexture = newTexture;
}

void LTexture::loadFromText(std::string texText, SDL_Color textColor)
{
	// First must get rid of any pre-existing texture
	free();

	// Begin render process by creating a temporary surface
	SDL_Surface* textSurf = TTF_RenderText_Solid(gFont, texText.c_str(), textColor);
	if (textSurf != nullptr)
	{
		// Create texture from surface
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurf);
		if (mTexture == nullptr)
			logSDLError(std::cout, "CreateTextureFromSurface (Text)");
		else
		{
			// Get image dimensions
			mWidth = textSurf->w;
			mHeight = textSurf->h;
		}
		// Get rid of old surface
		SDL_FreeSurface(textSurf);
	}
	else
	{
		logSDLError(std::cout, "TTF_RenderText_Solid");
	}
}

void LTexture::free()
{
	// Free the texture if it exists, if not do nothing
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	// Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* cntr, SDL_RendererFlip flip)
{
	// Set renderering space and render to screen
	SDL_Rect textureQuad = { x, y, mWidth, mHeight };

	// Set clip rendering dimensions
	if (clip != nullptr)
	{
		textureQuad.w = clip->w;
		textureQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &textureQuad, angle, cntr, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}