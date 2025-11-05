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
	createBackground();

	mRNG.seed(std::random_device{}());
	mBinDist = std::uniform_int_distribution<int>(0, 1);
	mGrayDist = std::uniform_int_distribution<int>(0, 255);

	mRect = { 0, 0, mWidth, mHeight };
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

bool Scene::createBackground() 
{
	mBackground = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);

	if (!mBackground) {
		std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	return true;
}

bool Scene::drawRect(SDL_Rect rect) { return drawRect(rect, 255, 255, 255, 255); }
bool Scene::drawRect(SDL_Rect rect, int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
	SDL_RenderDrawRect(mRenderer, &rect);
	return true;
}

bool Scene::fill() { return fill(mRect, 255, 255, 255, 255); }
bool Scene::fill(SDL_Rect rect, int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
	SDL_RenderFillRect(mRenderer, &rect);
	return true;
}

bool Scene::noisePixel() { return noisePixel(mBackground, mRect); }
bool Scene::noisePixel(SDL_Texture* tex, SDL_Rect rect)
{
	void* pixels;
	int pitch;
	SDL_LockTexture(tex, nullptr, &pixels, &pitch);

	Uint32* p = static_cast<Uint32*>(pixels);
	int rowPixels = pitch / 4;

	for (int y = 0; y < rect.h; ++y) {
		Uint32* row = p + y * rowPixels;
		for (int x = 0; x < rect.w; ++x) {
			row[x] = mBinDist(mRNG) ? 0xFFFFFFFF : 0xFF000000;
		}
	}

	SDL_UnlockTexture(tex);

	SDL_RenderCopy(mRenderer, tex, nullptr, &rect);

	return false;
}

bool Scene::noiseGray() { return noiseGray(mBackground, mRect); }
bool Scene::noiseGray(SDL_Texture* tex, SDL_Rect rect)
{
	void* pixels;
	int pitch;
	SDL_LockTexture(tex, nullptr, &pixels, &pitch);

	Uint32* p = static_cast<Uint32*>(pixels);
	int rowPixels = pitch / 4;

	for (int y = 0; y < rect.h; ++y) {
		Uint32* row = p + y * rowPixels;
		for (int x = 0; x < rect.w; ++x) {
			Uint8 gray = static_cast<Uint8>(mGrayDist(mRNG));
			row[x] = 0xFF000000 | (gray << 16) | (gray << 8) | gray;
		}
	}

	SDL_UnlockTexture(tex);

	SDL_RenderCopy(mRenderer, tex, nullptr, &rect);

	return false;
}

bool Scene::keepBackground()
{
	SDL_RenderCopy(mRenderer, mBackground, nullptr, &mRect);
	return true;
}

bool Scene::update() { return update(true); }
bool Scene::update(bool clear)
{
	SDL_RenderPresent(mRenderer);
	if (clear) SDL_RenderClear(mRenderer);
	return true;
}

bool Scene::renderClear()
{
	SDL_RenderClear(mRenderer);
	return true;
}

bool Scene::SDLDestroy()
{
	SDL_DestroyTexture(mBackground);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);

	return true;
}

void position(SDL_Rect& rect, int x, int y) 
{ 
	rect.x = x; rect.y = y; 
}

void positionCenter(SDL_Rect& rect, int x, int y)
{
	rect.x = x - (rect.w) / 2;
	rect.y = y - (rect.h) / 2;
}

void move(SDL_Rect& rect, int x, int y) 
{ 
	rect.x += x; rect.y += y; 
}