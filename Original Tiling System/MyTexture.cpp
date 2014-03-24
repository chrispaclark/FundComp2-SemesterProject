// MyTexture.cpp
// implementation for texture wrapping class

#include "MyTexture.h"
#include "Functions.h"

MyTexture::MyTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

MyTexture::~MyTexture()
{
	//Deallocate
	free();
}

void MyTexture::setRenderer(SDL_Renderer* ren)
{
	geTexRenderer = ren;
}


bool MyTexture::loadFromFile(string path)
{
	//Get rid of preexisting texture
	free();

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
		newTexture = SDL_CreateTextureFromSurface(geTexRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			logSDLError(cout, "CreateTextureFromSurface");
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void MyTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void MyTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void MyTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void MyTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void MyTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(geTexRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int MyTexture::getWidth()
{
	return mWidth;
}

int MyTexture::getHeight()
{
	return mHeight;
}

SDL_Texture* MyTexture::getTexture()
{
	return mTexture;
}