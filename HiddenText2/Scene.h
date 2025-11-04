#pragma once

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
	SDL_Texture* getTexture() const { return mTexture; }

	bool fill(); 
	bool fill(int r, int g, int b);

	std::mt19937 mRNG;
	std::uniform_int_distribution<int> mBinDist;
	bool noisePixel();
	std::uniform_int_distribution<int> mGrayDist;
	bool noiseGray();

	bool update();

	bool SDLDestroy();

private:
	int mWidth;
	int mHeight;

	SDL_Window* mWindow = nullptr;
	bool createWindow(std::string s);

	SDL_Renderer* mRenderer = nullptr;
	bool createRenderer();

	SDL_Texture* mTexture = nullptr;
	bool createTexture();
};