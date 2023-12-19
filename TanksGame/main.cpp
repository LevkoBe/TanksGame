#include <iostream>
#include "GameManager.h"


int main() {
    int windowSize = 900;
    int gridSize = 10;
    int difficulty = 3;
    GameManager game(windowSize, gridSize, difficulty);
    game.run();

    return 0;
}
