#pragma once
#include <queue>
#include <cmath>
#include <vector>
#include <memory>  // ...for std::shared_ptr

struct Node {
    int x, y, cost, heuristic, direction;

    Node(int x, int y, int cost, int heuristic, int direction)
        : x(x), y(y), cost(cost), heuristic(heuristic), direction(direction) {}

    Node(const Node& other)
        : x(other.x), y(other.y), cost(other.cost), heuristic(other.heuristic), direction(other.direction) {}

    Node(Node&& other)
        : x(std::move(other.x)), y(std::move(other.y)), cost(std::move(other.cost)),
        heuristic(std::move(other.heuristic)), direction(std::move(other.direction)) {}

    Node& operator=(const Node& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            cost = other.cost;
            heuristic = other.heuristic;
            direction = other.direction;
        }
        return *this;
    }

    Node& operator=(Node&& other) {
        if (this != &other) {
            x = std::move(other.x);
            y = std::move(other.y);
            cost = std::move(other.cost);
            heuristic = std::move(other.heuristic);
            direction = std::move(other.direction);
        }
        return *this;
    }

    bool operator>(const Node& other) const {
        return (cost + heuristic) > (other.cost + other.heuristic);
    }

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};


class PathFinder {
private:
    const int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // (up, down, left, right)
    std::shared_ptr<std::vector<std::vector<bool>>> wallsMap;
    const int gridSize;

public:
    PathFinder(std::shared_ptr<std::vector<std::vector<bool>>> wallsMap, int gridSize);

    Node findNextCell(int startX, int startY, int targetX, int targetY) const;

    static std::pair<int, int> calculatePositionOnBinaryMap(const std::pair<int, int>& realPosition, int cellSize) {
        int x = (realPosition.first + 1) / cellSize;
        int y = (realPosition.second + 1) / cellSize;
        return { x, y };
    }

    bool hasLineOfSight(int xSource, int ySource, int xTarget, int yTarget) const {

        int dx = abs(xTarget - xSource);
        int dy = abs(yTarget - ySource);
        int sx = (xSource < xTarget) ? 1 : -1;
        int sy = (ySource < yTarget) ? 1 : -1;
        int err = dx - dy;

        while (xSource != xTarget || ySource != yTarget) {
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                xSource += sx;
            }
            if (e2 < dx) {
                err += dx;
                ySource += sy;
            }

            if ((*wallsMap)[xSource][ySource]) {
                return false;
            }
        }

        return true;
    }

private:
    bool isValid(int x, int y) const;

    int calculateHeuristic(int x, int y, int targetX, int targetY) const;

    Node secondOnTheWay(const Node& startNode, const Node& targetNode, const std::vector<Node>& visitedNodes) const;
};
