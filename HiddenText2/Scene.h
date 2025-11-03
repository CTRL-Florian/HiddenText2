#pragma once

#include <string>
#include <iostream>

#include <SDL2/SDL.h>

class Scene
{
public:
	Scene();

	bool createWindow();
	bool createWindow(std::string s);

	SDL_Surface* getWinSurface();
	SDL_Window* getWindow() const;

	bool fill();
	bool fill(int r, int g, int b);

	bool update();

	bool closeWindow();

private:
	bool winSurface();
	SDL_Surface* mWinSurface = nullptr;

	SDL_Window* mWindow = nullptr;
};

bool initializeSDL();
bool quitSDL();