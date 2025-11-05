#include "SDLFunctions.h"

bool initializeSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	TTF_Init();

	return true;
}

bool quitSDL()
{
	TTF_Quit();
	SDL_Quit();
	return true;
}