#include "Scene.h"

Scene::Scene() : Scene("Window", 1280, 720)
{
	
}

Scene::Scene(std::string windowName, int width, int height) :
	mWidth{width}, mHeight{height}
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

bool Scene::fill() { return drawFilledRect(mRect, 255, 255, 255, 255); }
bool Scene::fill(int r, int g, int b, int a) { return drawFilledRect(mRect, r, g, b, a); }

bool Scene::drawFilledRect(SDL_Rect rect, int r, int g, int b, int a)
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

bool Scene::noisePixelOnText(SDL_Texture* tex, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);

	SDL_Rect rect{ x, y, w, h };

	return noisePixelOnText(tex, rect);
}

bool Scene::noisePixelOnText(SDL_Texture* tex, SDL_Rect rect)
{
	void* pixels;
	int pitch;
	if (SDL_LockTexture(tex, nullptr, &pixels, &pitch) != 0) {
		std::cerr << "Failed to lock texture: " << SDL_GetError() << std::endl;
		return false;
	}

	Uint32* p = static_cast<Uint32*>(pixels);
	int rowPixels = pitch / 4;

	for (int j = 0; j < rect.h; ++j) {
		Uint32* row = p + j * rowPixels;
		for (int i = 0; i < rect.w; ++i) {
			Uint32 pixel = row[i];
			Uint8 alpha = pixel >> 24;
			if (alpha > 0) {
				row[i] = (alpha << 24) | (mBinDist(mRNG) ? 0xFFFFFF : 0x000000);
			}
		}
	}

	SDL_UnlockTexture(tex);

	SDL_RenderCopy(mRenderer, tex, nullptr, &rect);
	return true;
}

SDL_Rect Scene::rectToCenter(SDL_Texture* tex) const
{
	int texW; int texH;
	SDL_QueryTexture(tex, nullptr, nullptr, &texW, &texH);

	int x = (mWidth - texW) / 2;
	int y = (mHeight - texH) / 2;

	SDL_Rect rect{ x, y, texW, texH };
	return rect;
}

bool Scene::keepBackground()
{
	if (!mBackground) return false;
	SDL_RenderCopy(mRenderer, mBackground, nullptr, &mRect);
	return true;
}

bool Scene::render(SDL_Texture* tex) { return render(tex, mRect); }
bool Scene::render(SDL_Texture* tex, SDL_Rect rect)
{
	SDL_RenderCopy(mRenderer, tex, nullptr, &rect);
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

void resize(SDL_Rect& rect, int m)
{
	if (m <= 0) return;
	resize(rect, rect.w * m, rect.h * m);
}

void resize(SDL_Rect& rect, int w, int h)
{
	if (w <= 0 || h <= 0) return;
	rect.w = w; rect.h = h;
}

void resizeAll(SDL_Rect& rect, int m)
{
	if (m <= 0) return;
	resize(rect, rect.w * m, rect.h * m);
}

void resizeAll(SDL_Rect& rect, int w, int h)
{
	if (w <= 0 || h <= 0) return;

	int xCenter = rect.x + rect.w / 2;
	int yCenter = rect.y + rect.h / 2;

	rect.w = w; rect.h = h;

	positionCenter(rect, xCenter, yCenter);
}

SDL_Texture* textTexture(SDL_Renderer* r, const char* s, int size)
{
	TTF_Font* font = TTF_OpenFont("D:/Projects/HiddenText2/HiddenText2/fonts/ARIAL.ttf", size);
	if (!font) {
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		TTF_CloseFont(font);
		return nullptr;
	}

	SDL_Color color{ 0, 0, 0, 255 };
	SDL_Surface* surface = TTF_RenderText_Blended(font, s, color);
	if (!surface) {
		std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
		TTF_CloseFont(font);
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTexture(
		r,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		surface->w,
		surface->h
	);

	if (!texture) {
		printf("Texture creation error: %s\n", SDL_GetError());
		SDL_FreeSurface(surface);
		return nullptr;
	}

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_UpdateTexture(texture, nullptr, surface->pixels, surface->pitch);

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);

	return texture;
}