// CharSprite.h
// Contains the interface for the CharSprite class
// CharSprite serves as the BASE CLASS for all character sprites (Both Hero and NPCs) 
// Holds both the functionality and the textures needed by the class
#include "LTexture.h"

class CharSprite
{
public:
	CharSprite();			// allocate memory, initialize pointers to null / ints to 0;
	~CharSprite();			// free up memory

	void process(SDL_Event &e);		// handle events concerning the character
	void move();			// Move character across the screen. Will change x/y vel as well as animate
	void checkPos(int x, int y, int w, int h);		// funnels CharSprite boundaries to map values and checks whether location is walkable

	void render();			// render character sprite to screen
private:
	LTexture *charSprite;	// Holds the different character textures, may have to use new/delete to accomodate animation

	int xpos, ypos;			// x/y-position of character for checking location and drawing
	int xvel, yvel;			// x/y-direction movement speed

	int cWidth, cHeight;	// (Character Width and Height)  for checking location and drawing
};