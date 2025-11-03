#include "Scene.h"

#include <chrono>
#include <thread>

int main(int argc, char** args) {

    initializeSDL();

    Scene scene;

    scene.createWindow();
    scene.fill();
    scene.update();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    scene.closeWindow();

    quitSDL();

    return EXIT_SUCCESS;
}