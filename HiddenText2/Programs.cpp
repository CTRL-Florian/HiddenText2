#include "Programs.h"
#include "SDLFunctions.h"

void fillProgram()
{
    initializeSDL();
    Scene scene;

    scene.fill();
    scene.update();

    int r = 255;  int g = 0; int b = 0; // Initial color values.
    int a = 255;                        // Opacity.
    int step = 3;                       // Rate at which the color changes.
    int fase = 0;                       // What transformation is currently going on.

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        switch (fase) {
        case 0: // Red to green.
            r -= step;
            g += step;
            if (r <= 0 && g >= 255) {
                r = 0; g = 255; fase = 1;
            }
            break;
        case 1: // Green to blue
            g -= step;
            b += step;
            if (g <= 0 && b >= 255) {
                g = 0; b = 255; fase = 2;
            }
            break;
        case 2: // Blue to red.
            b -= step;
            r += step;
            if (b <= 0 && r >= 255) {
                b = 0; r = 255; fase = 0;
            }
            break;
        }

        scene.fill(r, g, b, a);     // Fill the background with color values.
        scene.update();             // Update the window.

        SDL_Delay(20);
    }

    scene.SDLDestroy();
    quitSDL();
}

void resizeProgram()
{
    initializeSDL();
    Scene scene;

    int size = 100;                     // Initial size.
    SDL_Rect rect{ 0, 0, size, size};   // Initial rect.
    positionCenter(rect, scene.getXCenter(), scene.getYCenter());   // Center rect.

    int r = 255; int g = 0; int b = 0; int a = 255;
    int step = 1;

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        if (size >= 300) size = 100;
        else size += step;

        resizeAll(rect, size, size);    // Resizes in all directions (the center stays the same).

        scene.fill();                           // Set white background.
        scene.drawFilledRect(rect, r, g, b, a); // Draw filled rect.

        scene.update(); // Update the window.

        SDL_Delay(1);
    }

    scene.SDLDestroy();
    quitSDL();
}

void squareProgram()
{
    initializeSDL();

    Scene scene;

    int w = 200; int h = 200;   // Width & Height of the square

    SDL_Rect rect{ 100, 100, w, h };
    SDL_Texture* tex = SDL_CreateTexture(scene.getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, w, h);
    
    int count = 0;          // Counter to count iterations.
    int multiplier = 6;     // Times the text changes before the background changes.

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        if (rect.x > 900) {
            position(rect, 100, rect.y);
        }
        else {
            move(rect, 10, 0);
        }

        if (count < multiplier) {
            scene.keepBackground();         // Keep the previous background.
            scene.noisePixel(tex, rect);    // Applying noise on square.
            count++;
        }
        else if (count >= multiplier) {
            scene.noisePixel();             // Applying noise on background (takes scene background texture & window size).
            scene.noisePixel(tex, rect);    // Applying noise on square.
            count = 0;
        }

        scene.update();     // Update the window.

        SDL_Delay(1);
    }

    scene.SDLDestroy();

    quitSDL();
}

void textProgram()
{
    initializeSDL();

    Scene scene;

    auto r = scene.getRenderer();               
    auto textT = textTexture(r, "HELLO", 375);  // Create a texture with the text "HELLO".
    auto rect = scene.rectToCenter(textT);      // Find the rect to center the text.

    int count = 0;          // Counter to count iterations.
    int multiplier = 5;     // Times the text changes before the background changes.

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        if (count < multiplier) {
            scene.keepBackground();                 // Keep the previous background.
            scene.noisePixelOnText(textT, rect);    // Add a noise to the text.
            count++;
        }
        else if (count >= multiplier) {
            scene.noisePixel();                     // Applying noise on background (takes scene background texture & window size).
            scene.noisePixelOnText(textT, rect);    // Add a noise to the text.
            count = 0;
        }

        scene.update();     // Update the window.

        SDL_Delay(1);
    }

    SDL_DestroyTexture(textT);
    scene.SDLDestroy();

    quitSDL();
}