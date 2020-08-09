#include "errors.h"
#include <iostream>
#include <cstdlib>
#include <SDL.h>

void fatal(std::string error)
{
	std::cout << error << std::endl;
	SDL_Quit();
	exit(true);
}