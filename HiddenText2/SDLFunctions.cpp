#include "SDLFunctions.h"

bool initializeSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	return true;
}

bool quitSDL()
{
	SDL_Quit();
	return true;
}