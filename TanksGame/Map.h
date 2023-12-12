#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <memory>

enum MazeCell {
    CurrentSpot,
    Path,
    Wall, // Wall
    Destination
};

class Map {
private:
    int gridSize = 10;
public:
    std::shared_ptr<std::vector<std::vector<MazeCell>>> map;
    Map(int gridSize = 10);
private:
    void printMatrix(const std::shared_ptr<std::vector<std::vector<MazeCell>>>& matrix);

    std::vector<std::pair<int, int>> nearestCells(std::shared_ptr<std::pair<int, int>> cell);

    std::shared_ptr<std::vector<std::vector<MazeCell>>> createMap();

    std::pair<int, int> startingPoint(std::shared_ptr<std::vector<std::vector<MazeCell>>> map);

    std::pair<int, int> getRandomPair(std::shared_ptr<std::vector<std::vector<MazeCell>>> map,
        const std::shared_ptr<std::vector<std::pair<int, int>>>& neighbours, std::shared_ptr<std::vector<std::pair<int, int>>> visited);

    bool closeToDestination(std::shared_ptr<std::vector<std::vector<MazeCell>>> map, std::pair<int, int> toCheck);

    std::shared_ptr<std::vector<std::pair<int, int>>> getNeighbours(std::shared_ptr<std::vector<std::vector<MazeCell>>> map, std::shared_ptr<std::pair<int, int>> currentSpot);

    bool nonPathNeighbours(std::shared_ptr<std::vector<std::vector<MazeCell>>> map, std::pair<int, int> toCheck);

    bool insideTheGameField(std::shared_ptr<std::vector<std::vector<MazeCell>>> map, std::pair<int, int> toCheck);
}; // todo: add method to rarefy the thickness on walls (thin the wall density)
