#include "GameRun.h"
#include "FolderReader.h"
#include <windows.h>

GameRun::GameRun(int windowSize, int gridSize, int difficulty): windowSize(windowSize), gridSize(gridSize), userTank(new Tank(difficulty * 10)) {
    createMap();
    for (int i = 0; i < difficulty; i++)
    {
        bots->push_back(Tank(difficulty * 10));
    }
}

void GameRun::createMap() {
    Map map(gridSize);
    std::vector<std::string> wallTextures = FolderReader::GetFilesInDirectory("./images/walls");
    int wallSize = windowSize / gridSize;
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if ((*map.map)[i][j] == Wall)
            {
                int xPos = wallSize * i;
                int yPos = wallSize * j;

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<size_t> distribution(0, wallTextures.size() - 1);
                size_t randomIndex = distribution(gen);
                std::string image = wallTextures[randomIndex];

                walls->push_back(GameObject(xPos, yPos, wallSize, 0, 0, image));
            }
        }
    }
}
