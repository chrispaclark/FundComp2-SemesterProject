// LTexture.h
// Contains the interface for the LTexture Class (loaded texture)
// This class is intended to be used to load the images for everything in the game

#include "SDL.h"
#include "SDL_image.h"
#include <string>

//
void logSDLError(std::ostream&, const std::string&);

class LTexture
{
public:
	// Initialize variables
	LTexture();
	// Free memory
	~LTexture();

	// Loads image at specified path
	void loadFromFile(std::string path);
	// Creates image from font string
	void loadFromText(std::string Text, SDL_Color Color);
	// Free up memory and direct pointers at nullptr
	void free();
	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	// Set blend mode
	void setBlendMode(SDL_BlendMode blending);
	// Set Alpha Modulation
	void setAlpha(Uint8 alpha);
	// Render the texture at a given point over Rect dimensions
	void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* cntr = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	// Get image dimensions
	int getWidth();
	int getHeight();
	
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};