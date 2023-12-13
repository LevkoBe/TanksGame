#include "GameRun.h"

GameRun::GameRun(int windowSize, int gridSize, int difficulty): windowSize(windowSize), gridSize(gridSize), userTank(new Tank(difficulty * 10)) {
    createMap();
    for (int i = 0; i < difficulty; i++)
    {
        bots->push_back(Tank(difficulty * 10));
    }
}

void GameRun::createMap() {
    Map map(gridSize);
    int wallSize = windowSize / gridSize;
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if ((*map.map)[i][j] == Wall)
            {
                int xPos = wallSize * (i + 0.5);
                int yPos = wallSize * (j + 0.5);
                walls->push_back(GameObject(xPos, yPos, wallSize, 0, 0, 0, Square));
            }
        }
    }
}
