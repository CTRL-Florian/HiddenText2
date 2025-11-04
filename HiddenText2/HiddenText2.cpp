#include "Scene.h"
#include "SDLFunctions.h"

#include <chrono>
#include <thread>

#include <SDL2/SDL.h>

int main(int argc, char** args) {

    initializeSDL();

    Scene scene("Window", 1280, 720);

    scene.fill();
    scene.update();

    SDL_Delay(500);

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        scene.noise();
        scene.update();

        SDL_Delay(15);
    }

    scene.SDLDestroy();

    quitSDL();

    return EXIT_SUCCESS;
}