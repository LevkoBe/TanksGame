#include "PathFinder.h"

PathFinder::PathFinder(std::shared_ptr<std::vector<std::vector<bool>>> wallsMap, int gridSize) : wallsMap(wallsMap), gridSize(gridSize) {}

Node PathFinder::findNextCell(int startX, int startY, int targetX, int targetY) const {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::vector<std::vector<bool>> visited(gridSize, std::vector<bool>(gridSize, false));

    openSet.push(Node(startX, startY, 0, calculateHeuristic(startX, startY, targetX, targetY), -1));

    std::vector<Node> visitedNodes = std::vector<Node>();

    while (!openSet.empty()) {
        Node current = openSet.top();
        visitedNodes.push_back(current);
        openSet.pop();

        if (current.x == targetX && current.y == targetY) {
            auto startNode = Node(startX, startY, 0, 0, 0);
            auto targetNode = Node(targetX, targetY, 0, 0, 0);
            return secondOnTheWay(startNode, targetNode, visitedNodes);
        }

        visited[current.x][current.y] = true;


        for (int i = 0; i < 4; ++i) {
            const int nextX = current.x + directions[i][0];
            const int nextY = current.y + directions[i][1];

            if (isValid(nextX, nextY) && !visited[nextX][nextY]) {
                openSet.push(Node(nextX, nextY, current.cost + 1, calculateHeuristic(nextX, nextY, targetX, targetY), i));
                visited[nextX][nextY] = true;
            }
        }
    }

    // Return an invalid node if no valid path is found
    return Node(-1, -1, -1, -1, -1);
}

bool PathFinder::isValid(int x, int y) const {
    return x >= 0 && x < gridSize && y >= 0 && y < gridSize && !(*wallsMap)[x][y];
}

int PathFinder::calculateHeuristic(int x, int y, int targetX, int targetY) const {
    return std::abs(x - targetX) + std::abs(y - targetY); // Manhattan distance heuristic
}

Node PathFinder::secondOnTheWay(const Node& startNode, const Node& targetNode, const std::vector<Node>& visitedNodes) const {
    Node current = targetNode;
    Node previous = targetNode;
    int index = visitedNodes.size() - 1;

    while (!(current == startNode)) {
        Node probablyNext = visitedNodes[index--];
        if (!(probablyNext == current)) {
            continue;
        }
        int parentDirection = probablyNext.direction;
        int parentX = current.x - directions[parentDirection][0];
        int parentY = current.y - directions[parentDirection][1];
        previous = std::move(current);
        current = Node(parentX, parentY, 0, 0, parentDirection);
    }

    return previous;
}