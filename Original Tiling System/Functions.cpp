// Functions.cpp
// implementation for global scope fns

#include "Functions.h"

void logSDLError(ostream &os, const string &msg)
{
	os << msg << " error: " << SDL_GetError() << endl;
}
