#include "Scene.h"

Scene::Scene() : Scene("Window", 1280, 720)
{
	
}

Scene::Scene(std::string windowName, int width, int height) :
	mWidth{width},
	mHeight{height}
{
	createWindow(windowName);
	createRenderer();
	createTexture();

	mRNG.seed(std::random_device{}());
	mBinDist = std::uniform_int_distribution<int>(0, 1);
	mGrayDist = std::uniform_int_distribution<int>(0, 255);
}

bool Scene::createWindow(std::string s)
{
	mWindow = SDL_CreateWindow(s.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, SDL_WINDOW_ALWAYS_ON_TOP);

	if (!mWindow) {
		std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	return true;
}

bool Scene::createRenderer() 
{
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!mRenderer) {
		std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	return true;
}

bool Scene::createTexture() 
{
	mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);

	if (!mTexture) {
		std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	return true;
}

bool Scene::fill() { return fill(255, 255, 255); }
bool Scene::fill(int r, int g, int b)
{
	SDL_SetRenderDrawColor(mRenderer, r, g, b, 255);
	SDL_RenderClear(mRenderer);
	return true;
}

bool Scene::noisePixel()
{
	void* pixels;
	int pitch;
	SDL_LockTexture(mTexture, nullptr, &pixels, &pitch);

	Uint32* p = static_cast<Uint32*>(pixels);
	int rowPixels = pitch / 4;

	for (int y = 0; y < mHeight; ++y) {
		Uint32* row = p + y * rowPixels;
		for (int x = 0; x < mWidth; ++x) {
			row[x] = mBinDist(mRNG) ? 0xFFFFFFFF : 0xFF000000;
		}
	}

	SDL_UnlockTexture(mTexture);

	SDL_RenderClear(mRenderer);
	SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);

	return false;
}

bool Scene::noiseGray()
{
	void* pixels;
	int pitch;
	SDL_LockTexture(mTexture, nullptr, &pixels, &pitch);

	Uint32* p = static_cast<Uint32*>(pixels);
	int rowPixels = pitch / 4;

	for (int y = 0; y < mHeight; ++y) {
		Uint32* row = p + y * rowPixels;
		for (int x = 0; x < mWidth; ++x) {
			Uint8 gray = static_cast<Uint8>(mGrayDist(mRNG));
			row[x] = 0xFF000000 | (gray << 16) | (gray << 8) | gray;
		}
	}

	SDL_UnlockTexture(mTexture);

	SDL_RenderClear(mRenderer);
	SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);

	return false;
}

bool Scene::update()
{
	SDL_RenderPresent(mRenderer);
	return true;
}

bool Scene::SDLDestroy()
{
	SDL_DestroyTexture(mTexture);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);

	return true;
}