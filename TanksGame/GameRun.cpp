#define NOMINMAX
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

void GameRun::processCommands(std::vector<Command> commands) {
    for (auto& command : commands)
    {
        switch (command)
        {
        case ScaleUp:
            changeSize(1.1);
            break;
        case ScaleDown:
            changeSize(0.9);
            break;
        case RotateClockWise:
            userTank->rotate(0.1);
            break;
        case RotateCounterClockWise:
            userTank->rotate(-0.1);
            break;
        case MoveForward:
            setSpeed(1);
            break;
        case MoveBackward:
            setSpeed(-1);
            break;
        case Shoot:
            userTank->shoot(projectiles);
            break;
        default:
            break;
        }
    }
}

GameState GameRun::update(std::vector<Command> commands) {
    processCommands(move(commands));
    moveUserTank();
    // todo: move projectiles
    // todo: move bots
    return positions();
}

GameState GameRun::positions() {
    GameState state;
    state.userTank = userTank;
    state.walls = walls;
    state.bots = bots;
    state.projectiles = projectiles;
    return state;
}

void GameRun::setSpeed(int extent) {
    switch (mode)
    {
    case LeftUpRightDown:
        break;
    case RotatePosition:
        break;
    case RotateVelocity:
        break;
    case RotateAcceleration:
        userTank->accelerate(extent);
    default:
        break;
    }
}

void GameRun::moveUserTank() { // todo: nullify when collision
    userTank->speedUp(userTank->getAcceleration()); // todo: check coefficients system
    int xExpected = userTank->getPos().first + userTank->getVel().first;
    int yExpected = userTank->getPos().second + userTank->getVel().second;
    bool stopTheTank = false;

    if (!insideGameField(xExpected, yExpected)) { return; }

    for (auto& wall : *walls)
    { // collisions with walls
        if (squareCircleColliding(wall.getPos().first, wall.getPos().second, wall.getSize(), xExpected, yExpected, userTank->getSize() / 2))
        {
            stopTheTank = true;
        }
    }

    for (auto& bot : *bots)
    { // collisions with bots
        if (circlesColliding(bot.getPos().first, bot.getPos().second, bot.getSize(), xExpected, yExpected, userTank->getSize() / 2))
        {
            stopTheTank = true;
        }
    }

    for (auto& projectile : *projectiles)
    { // collisions with projectiles
        if (circlesColliding(projectile.getPos().first, projectile.getPos().second, projectile.getSize(), xExpected, yExpected, userTank->getSize() / 2))
        {
            if (projectile.destroyObject(*userTank)) {
                std::cout << "Game over!" << std::endl;
            }
        }
    }

    if (stopTheTank)
    {
        userTank->speedUp(-userTank->getSpeed() / userTank->getChange());
    }

    // max speed
}

bool GameRun::circlesColliding(int x1, int y1, int radius1, int x2, int y2, int radius2) {

    int distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    return distance < (radius1 + radius2);
}

bool GameRun::squareCircleColliding(double squareX, double squareY, double squareSize, double circleX, double circleY, double circleRadius) {

    double closestX = std::max(squareX - squareSize / 2.0, std::min(circleX, squareX + squareSize / 2.0));
    double closestY = std::max(squareY - squareSize / 2.0, std::min(circleY, squareY + squareSize / 2.0));

    double distance = std::sqrt(std::pow(closestX - circleX, 2) + std::pow(closestY - circleY, 2));
    return distance < circleRadius;
}

bool GameRun::squareCircleColliding(int squareX, int squareY, int squareSize, int circleX, int circleY, int circleRadius) {
    double sqX = static_cast<double>(squareX);
    double sqY = static_cast<double>(squareY);
    double sqS = static_cast<double>(squareSize);
    double crX = static_cast<double>(circleX);
    double crY = static_cast<double>(circleY);
    double crR = static_cast<double>(circleRadius);
    return squareCircleColliding(sqX, sqY, sqS, crX, crY, crR);
}

bool GameRun::insideGameField(int x, int y) const {
    return x > 0 && y > 0 && x < windowSize && y < windowSize;
}

void GameRun::changeSize(double increase) {
    // todo: check if smaller than a cell;
    userTank->scale(increase);
}
