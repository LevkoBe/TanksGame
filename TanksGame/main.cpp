#include <iostream>
#include "GameManager.h"


int main() {
    int windowSize = 800;
    int gridSize = 5;
    int difficulty = 3;
    GameManager game(windowSize, gridSize, difficulty);
    game.run();

    return 0;
}
