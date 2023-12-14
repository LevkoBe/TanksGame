#include "GameRun.h"
#include <windows.h>

GameRun::GameRun(int windowSize, int gridSize, int difficulty): windowSize(windowSize), gridSize(gridSize), userTank(new Tank(difficulty * 10)) {
    createMap();
    for (int i = 0; i < difficulty; i++)
    {
        bots->push_back(Tank(difficulty * 10));
    }
}

std::vector<std::string> GetFilesInDirectory(const std::string& directory) {
    std::vector<std::string> files;

    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA((directory + "/*").c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                continue; // Skip directories
            }
            files.push_back(directory + "/" + findFileData.cFileName);
        } while (FindNextFileA(hFind, &findFileData) != 0);

        FindClose(hFind);
    }

    return files;
}

void GameRun::createMap() {
    Map map(gridSize);
    std::vector<std::string> wallTextures = GetFilesInDirectory("./images/walls");
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
