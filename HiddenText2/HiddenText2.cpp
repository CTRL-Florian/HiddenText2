#include "Scene.h"
#include "SDLFunctions.h"

#include <chrono>
#include <thread>

#include <SDL2/SDL.h>

int main(int argc, char** args) {

    initializeSDL();

    Scene scene;

    scene.fill();
    scene.update();

    SDL_Delay(500);

    /*SDL_Rect rect{ 100, 100, 200, 200 };
    SDL_Texture* tex = SDL_CreateTexture(scene.getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, 200, 200);*/

    auto r = scene.getRenderer();
    auto textT = textTexture(r, "HELLO", 375);

    int count = 0;
    int multiplier = 5;

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        if (count < multiplier) {
            scene.keepBackground();
            scene.noisePixelOnText(textT, 50, 50);
            count++;
        }
        else if (count >= multiplier) {
            scene.noisePixel();
            scene.noisePixelOnText(textT, 50, 50);
            count = 0;
        }

        scene.update();

        SDL_Delay(1);
    }

    SDL_DestroyTexture(textT);
    scene.SDLDestroy();

    quitSDL();

    return EXIT_SUCCESS;
}

/*if (rect.x > 900) {
            position(rect, 100, rect.y);
        }
        else {
            move(rect, 10, 0);
        }

        if (count < multiplier) {
            scene.keepBackground();
            scene.noisePixel(tex, rect);
            count++;
        }
        else if (count >= multiplier) {
            scene.noisePixel();
            scene.noisePixel(tex, rect);
            count = 0;
        }*/