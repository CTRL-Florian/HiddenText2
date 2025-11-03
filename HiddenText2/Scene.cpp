#include "Scene.h"

Scene::Scene()
{

}

bool Scene::createWindow() { return createWindow("Window"); }
bool Scene::createWindow(std::string s)
{
	if (mWindow != nullptr) {
		std::cerr << "Scene already has an open window." << std::endl;
		return false;
	}

	mWindow = SDL_CreateWindow(s.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

	if (!mWindow) {
		std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	return true;
}

bool Scene::winSurface() {
	if (mWindow == nullptr) {
		return false;
	}

	mWinSurface = SDL_GetWindowSurface(mWindow);

	if (!mWinSurface) {
		std::cerr << "Error getting surface: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	return true;
}

SDL_Surface* Scene::getWinSurface()
{
	if (mWinSurface == nullptr) {
		std::cout << "Attempting to set winSurface..." << std::endl;
		if (!winSurface()) std::cout << "Return value will be a nullptr." << std::endl;
	}

	return mWinSurface;
}

SDL_Window* Scene::getWindow() const
{
	if (mWindow == nullptr) std::cout << "Return value will be a nullptr." << std::endl;
	return mWindow;
}

bool Scene::fill() { return fill(255, 255, 255); }
bool Scene::fill(int r, int g, int b)
{
	if (mWinSurface == nullptr) {
		if (!winSurface()) {
			std::cout << "Cannot fill: The scene has no window surface, or it's pointer is not known." << std::endl;
			return false;
		}
	}

	SDL_FillRect(mWinSurface, NULL, SDL_MapRGB(mWinSurface->format, r, g, b));
	return true;
}

bool Scene::update()
{
	if (mWindow == nullptr) {
		std::cout << "Cannot update: The scene has no window, or it's pointer is not known." << std::endl;
		return false;
	}

	SDL_UpdateWindowSurface(mWindow);
	return true;
}

bool Scene::closeWindow()
{
	if (mWindow == nullptr) std::cout << "No window to close." << std::endl;
	else SDL_DestroyWindow(mWindow);

	return true;
}

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