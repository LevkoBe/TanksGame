#include <iostream>
#include "GameRun.h"
#include "Renderer.h"


int main() {
    GameRun game;
    Renderer renderer(800, game);
    renderer.run();

    return 0;
}
