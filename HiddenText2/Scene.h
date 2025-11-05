#pragma once

#include "Rect.h"

#include <string>
#include <random>
#include <iostream>

#include <SDL2/SDL.h>

class Scene
{
public:
	Scene(); 
	Scene(std::string windowName, int width, int height);

	int getWidth() const { return mWidth; }
	int getHeight() const { return mHeight; }

	SDL_Window* getWindow() const { return mWindow; }
	SDL_Renderer* getRenderer() const { return mRenderer; }
	SDL_Texture* getBackground() const { return mBackground; }

	bool drawRect(SDL_Rect rect);
	bool drawRect(SDL_Rect rect, int r, int g, int b, int a);

	bool fill(); 
	bool fill(SDL_Rect rect, int r, int g, int b, int a);

	std::mt19937 mRNG;
	std::uniform_int_distribution<int> mBinDist;
	bool noisePixel();
	bool noisePixel(SDL_Texture* tex, SDL_Rect rect);
	std::uniform_int_distribution<int> mGrayDist;
	bool noiseGray();
	bool noiseGray(SDL_Texture* tex, SDL_Rect rect);

	bool keepBackground();

	bool update();
	bool update(bool clear);
	bool renderClear();

	bool SDLDestroy();

private:
	int mWidth;
	int mHeight;

	SDL_Rect mRect;

	SDL_Window* mWindow = nullptr;
	bool createWindow(std::string s);

	SDL_Renderer* mRenderer = nullptr;
	bool createRenderer();

	SDL_Texture* mBackground = nullptr;
	bool createBackground();
};

void position(SDL_Rect& rect, int x, int y);
void move(SDL_Rect& rect, int x, int y);