#pragma once
#include <iostream>
#include <vector>
#include <random>

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
    Map(int gridSize = 10) : gridSize(gridSize), map(createMap()) {}
private:
    void printMatrix(const std::shared_ptr<std::vector<std::vector<MazeCell>>>& matrix) {
        std::system("cls");
        for (const auto& row : *matrix) {
            for (MazeCell value : row) {
                if (value == Wall) {
                    std::cout << ". ";
                }
                else if (value == Path) {
                    std::cout << "# ";
                }
                else if (value == CurrentSpot) {
                    std::cout << "* ";
                }
                else if (value == Destination) {
                    std::cout << "+ ";
                }
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::pair<int, int>> nearestCells(std::shared_ptr<std::pair<int, int>> cell) {
        auto nearest = std::vector<std::pair<int, int>>();
        if (cell->first + 1 >= 0 && cell->second >= 0 && cell->first + 1 < gridSize && cell->second < gridSize) {
            nearest.push_back(std::make_pair(cell->first + 1, cell->second));
        }
        if (cell->first - 1 >= 0 && cell->second >= 0 && cell->first - 1 < gridSize && cell->second < gridSize) {
            nearest.push_back(std::make_pair(cell->first - 1, cell->second));
        }
        if (cell->first >= 0 && cell->second + 1 >= 0 && cell->first < gridSize && cell->second + 1 < gridSize) {
            nearest.push_back(std::make_pair(cell->first, cell->second + 1));
        }
        if (cell->first >= 0 && cell->second - 1 >= 0 && cell->first < gridSize && cell->second - 1 < gridSize) {
            nearest.push_back(std::make_pair(cell->first, cell->second - 1));
        }
        return nearest;
    }

    std::shared_ptr<std::vector<std::vector<MazeCell>>> createMap() {
        auto map = std::make_shared<std::vector<std::vector<MazeCell>>>(gridSize, std::vector<MazeCell>(gridSize, Wall));   // no path
        (*map)[0][gridSize - 1] = (*map)[gridSize - 1][0] = (*map)[gridSize - 1][gridSize - 1] = Destination;               // corners

        for (int i = 1; i < 4; i++) {
            auto visited = std::make_shared<std::vector<std::pair<int, int>>>(std::vector<std::pair<int, int>>());

            auto position = std::make_shared<std::pair<int, int>>(startingPoint(map));
            while (true) { // break when change destination into current
                auto neighbours = getNeighbours(map, position);
                auto newPair = getRandomPair(map, neighbours, visited); // if was given dest
                (*map)[position->first][position->second] = Path;
                if (!neighbours->empty())
                {
                    visited->push_back(*position);
                }
                position = std::make_shared<std::pair<int, int>>(newPair);
                if ((*map)[position->first][position->second] == Destination)
                {
                    (*map)[position->first][position->second] = Path;
                    printMatrix(map);
                    break;
                }
                (*map)[position->first][position->second] = CurrentSpot;
                printMatrix(map);
            }
            for (int i = 0; i < gridSize; i++)
            {
                for (int j = 0; j < gridSize; j++)
                {
                    if ((*map)[i][j] == Path)
                    {
                        (*map)[i][j] = Destination;
                    }
                }
            }
            if (i == 1) {
                (*map)[0][gridSize - 1] = Wall;
                (*map)[gridSize - 1][0] = Wall;
                (*map)[gridSize - 1][gridSize - 1] = Wall;
                (*map)[position->first][position->second] = Destination;
            }
            printMatrix(map);
        }
        return map;
    }

    std::pair<int, int> startingPoint(std::shared_ptr<std::vector<std::vector<MazeCell>>> map) {
        auto position = std::make_pair<int, int>(0, 0);
        if ((*map)[0][0] == Wall) { }
        else if ((*map)[0][gridSize - 1] == Wall) { position.second = gridSize - 1; }
        else if ((*map)[gridSize - 1][0] == Wall) { position.first = gridSize - 1; }
        else {
            position.first = gridSize - 1;
            position.second = gridSize - 1;
        }
        return position;
    }

    std::pair<int, int> getRandomPair(std::shared_ptr<std::vector<std::vector<MazeCell>>> map,
        const std::shared_ptr<std::vector<std::pair<int, int>>>& neighbours, std::shared_ptr<std::vector<std::pair<int, int>>> visited) {
        if (!neighbours || neighbours->empty()) {
            auto toReturn = visited->back();
            visited->pop_back();
            return toReturn;
        }

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<size_t> distribution(0, neighbours->size() - 1);
        size_t randomIndex = distribution(gen);

        return (*neighbours)[randomIndex];
    }

    bool closeToDestination(std::shared_ptr<std::vector<std::vector<MazeCell>>> map, std::pair<int, int> toCheck) {
        auto coordinates = std::make_pair(toCheck.first + 1, toCheck.second);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] == Destination) {
            return true;
        }
        coordinates = std::make_pair(toCheck.first - 1, toCheck.second);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] == Destination) {
            return true;
        }
        coordinates = std::make_pair(toCheck.first, toCheck.second + 1);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] == Destination) {
            return true;
        }
        coordinates = std::make_pair(toCheck.first, toCheck.second - 1);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] == Destination) {
            return true;
        }
        return false;
    }

    std::shared_ptr<std::vector<std::pair<int, int>>> getNeighbours(std::shared_ptr<std::vector<std::vector<MazeCell>>> map, std::shared_ptr<std::pair<int, int>> currentSpot) {

        auto neighbours = std::make_shared<std::vector<std::pair<int, int>>>(std::vector<std::pair<int, int>>());

        // checking whether we're close to destination

        auto coordinates = std::make_pair(currentSpot->first + 1, currentSpot->second);
        if ((insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] == Destination)) {
            neighbours->push_back(coordinates);
            return neighbours;
        }
        coordinates = std::make_pair(currentSpot->first - 1, currentSpot->second);
        if ((insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] == Destination)) {
            neighbours->push_back(coordinates);
            return neighbours;
        }
        coordinates = std::make_pair(currentSpot->first, currentSpot->second + 1);
        if ((insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] == Destination)) {
            neighbours->push_back(coordinates);
            return neighbours;
        }
        coordinates = std::make_pair(currentSpot->first, currentSpot->second - 1);
        if ((insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] == Destination)) {
            neighbours->push_back(coordinates);
            return neighbours;
        }

        // checking whether we step on the path

        coordinates = std::make_pair(currentSpot->first + 1, currentSpot->second);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] != Path && nonPathNeighbours(map, coordinates)
            && std::find(neighbours->begin(), neighbours->end(), coordinates) == neighbours->end()) {
            neighbours->push_back(coordinates);
        }
        coordinates = std::make_pair(currentSpot->first - 1, currentSpot->second);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] != Path && nonPathNeighbours(map, coordinates)
            && std::find(neighbours->begin(), neighbours->end(), coordinates) == neighbours->end()) {
            neighbours->push_back(coordinates);
        }
        coordinates = std::make_pair(currentSpot->first, currentSpot->second + 1);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] != Path && nonPathNeighbours(map, coordinates)
            && std::find(neighbours->begin(), neighbours->end(), coordinates) == neighbours->end()) {
            neighbours->push_back(coordinates);
        }
        coordinates = std::make_pair(currentSpot->first, currentSpot->second - 1);
        if (insideTheGameField(map, coordinates) && (*map)[coordinates.first][coordinates.second] != Path && nonPathNeighbours(map, coordinates)
            && std::find(neighbours->begin(), neighbours->end(), coordinates) == neighbours->end()) {
            neighbours->push_back(coordinates);
        }

        return neighbours;
    }

    bool nonPathNeighbours(std::shared_ptr<std::vector<std::vector<MazeCell>>> map, std::pair<int, int> toCheck) {

        auto neighbour = std::make_pair(toCheck.first + 1, toCheck.second);
        if (insideTheGameField(map, neighbour) && (*map)[neighbour.first][neighbour.second] == Path) {
            return false;
        }
        neighbour = std::make_pair(toCheck.first - 1, toCheck.second);
        if (insideTheGameField(map, neighbour) && (*map)[neighbour.first][neighbour.second] == Path) {
            return false;
        }
        neighbour = std::make_pair(toCheck.first, toCheck.second + 1);
        if (insideTheGameField(map, neighbour) && (*map)[neighbour.first][neighbour.second] == Path) {
            return false;
        }
        neighbour = std::make_pair(toCheck.first, toCheck.second - 1);
        if (insideTheGameField(map, neighbour) && (*map)[neighbour.first][neighbour.second] == Path) {
            return false;
        }
        return true;
    }

    bool insideTheGameField(std::shared_ptr<std::vector<std::vector<MazeCell>>> map, std::pair<int, int> toCheck) {
        if (toCheck.first < 0 || toCheck.second < 0 || toCheck.first >= gridSize || toCheck.second >= gridSize)
        {
            return false;
        }
        return true;
    }
};
