#define NOMINMAX
#include "GameRun.h"
#include "BotTank.h"
#include "FolderReader.h"
#include <windows.h>

GameRun::GameRun(int windowSize, int gridSize, int difficulty): windowSize(windowSize), gridSize(gridSize), userTank(new Tank(difficulty * 10, windowSize / gridSize)) {
    createMap();
    for (int i = 0; i < difficulty; i++)
    {
        allBots->push_back(BotTank(i + 1, windowSize / gridSize));
    }
    for (int i = 0; i < 3; i++)
    {
        addBot(i);
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
                (*wallsMap)[i][j] = true;
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
            userTank->rotate(10.0);
            break;
        case RotateCounterClockWise:
            userTank->rotate(-10.0);
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
    for (auto& projectile : (*projectiles)) {
        moveProjectile(projectile);
    }
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
        userTank->speedUp(extent);
        break;
    case RotateVelocity:
        userTank->speedUp(extent);
        break;
    case RotateAcceleration:
        userTank->accelerate(extent);
        break;
    default:
        break;
    }
}

void GameRun::moveUserTank() {
    userTank->speedUp(userTank->getAcceleration()); // todo: check coefficients system
    int xExpected = userTank->getPos().first + userTank->getVel().first;
    int yExpected = userTank->getPos().second + userTank->getVel().second;

    if (!insideGameField(xExpected, yExpected, userTank->getSize() / 4)) { return; }

    if (collisionsWithWalls(xExpected, yExpected)) { return; }

    if (collisionsWithBots(xExpected, yExpected)) { return; }
    
    if (collisionsWithProjectiles(xExpected, yExpected)) { return; }
    
    userTank->setPosition(xExpected, yExpected);

    if (mode == RotatePosition) { userTank->stop(); }
    // check max speed
}

void GameRun::moveProjectile(Projectile& projectile) {
    int x = projectile.getPos().first + projectile.getVel().first;
    int y = projectile.getPos().second + projectile.getVel().second;
    projectile.setPosition(x, y);

    if (!insideGameField(x, y, projectile.getSize() / 4)) {
        auto it = std::find(projectiles->begin(), projectiles->end(), projectile);
        if (it != projectiles->end()) {
            projectiles->erase(it);
        }
        return;
    }

    if (hitsWalls(x, y, projectile)) { return; } // todo: R-tree

    if (hitsBots(x, y, projectile)) { return; }
}

bool GameRun::collisionsWithWalls(int xExpected, int yExpected) {

    for (auto& wall : *walls) {
        if (squareCircleColliding(wall.getPos().first, wall.getPos().second, static_cast<int>(wall.getSize()), xExpected, yExpected, userTank->getSize() / 4)) {
            userTank->stop();
            return true;
        }
    }
    return false;
}

bool GameRun::collisionsWithBots(int xExpected, int yExpected) {
    for (auto& bot : *bots) {
        if (circlesColliding(bot.getPos().first, bot.getPos().second, bot.getSize() / 4, xExpected, yExpected, userTank->getSize() / 4))
        {
            userTank->stop();
            return true;
        }
    }
    return false;
}

bool GameRun::hitsWalls(int x, int y, Projectile projectile) {

    for (auto& wall : *walls) {
        if (squareCircleColliding(wall.getPos().first, wall.getPos().second, wall.getSize(), x, y, projectile.getSize() / 4))
        {
            if (projectile.destroyObject(wall)) {
                auto it = std::find(walls->begin(), walls->end(), wall);
                if (it != walls->end()) {
                    walls->erase(it);
                }
            }

            auto it = std::find(projectiles->begin(), projectiles->end(), projectile);
            if (it != projectiles->end()) {
                projectiles->erase(it);
            }
            return true;
        }
    }
    return false;
}

bool GameRun::hitsBots(int x, int y, Projectile projectile) {

    for (auto& bot : *bots) {
        if (circlesColliding(bot.getPos().first, bot.getPos().second, bot.getSize() / 4, x, y, projectile.getSize() / 4))
        {
            if (projectile.destroyObject(bot)) {
                auto it = std::find(bots->begin(), bots->end(), bot);
                if (it != bots->end()) {
                    bots->erase(it);
                }
            }
            auto it = std::find(projectiles->begin(), projectiles->end(), projectile);
            if (it != projectiles->end()) {
                projectiles->erase(it);
            }
            return true;
        }
    }
    return false;
}

bool GameRun::collisionsWithProjectiles(int xExpected, int yExpected) {
    for (auto& projectile : *projectiles) {
        if (circlesColliding(projectile.getPos().first, projectile.getPos().second, projectile.getSize() / 4, xExpected, yExpected, userTank->getSize() / 4))
        {
            if (projectile.destroyObject(*userTank)) {
                std::cout << "Game over!" << std::endl;
                return true;
            }
        }
    }
    return false;
}

bool GameRun::insideGameField(int x, int y, int radius) const {
    if (insideGameField(x - radius, y - radius) &&
        insideGameField(x - radius, y + radius) &&
        insideGameField(x + radius, y - radius) &&
        insideGameField(x + radius, y + radius))
    {
        return true;
    }
    userTank->stop();
    return false;
}

bool GameRun::addBot(int position) {
    if (allBots->size() <= 0) { return false; }

    auto theTank = allBots->back();
    allBots->pop_back();
    double cellSize = windowSize / gridSize;
    int xPos = cellSize / 2, yPos = cellSize / 2;

    switch (position) {
    case 0:
        xPos = cellSize * (gridSize - 0.5);
        break;
    case 1:
        xPos = yPos = cellSize * (gridSize - 0.5);
        break;
    case 2:
        yPos = cellSize * (gridSize - 0.5);
        break;
    }
    theTank.setPosition(xPos, yPos);
    bots->push_back(theTank);
    return true;
}

bool GameRun::circlesColliding(int x1, int y1, int radius1, int x2, int y2, int radius2) {
    int distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    return distance < (radius1 + radius2);
}

bool GameRun::squareCircleColliding(double squareTopLeftX, double squareTopLeftY, double squareSize, double circleCenterX, double circleCenterY, double circleRadius) {
    double closestX = std::max(squareTopLeftX, std::min(circleCenterX, squareTopLeftX + squareSize));
    double closestY = std::max(squareTopLeftY, std::min(circleCenterY, squareTopLeftY + squareSize));

    double distance = std::sqrt(std::pow(closestX - circleCenterX, 2) + std::pow(closestY - circleCenterY, 2));
    return distance < circleRadius;
}

bool GameRun::squareCircleColliding(int squareX, int squareY, int squareSize, int circleCenterX, int circleCenterY, int circleRadius) {
    double sqX = static_cast<double>(squareX);
    double sqY = static_cast<double>(squareY);
    double sqS = static_cast<double>(squareSize);
    double crX = static_cast<double>(circleCenterX);
    double crY = static_cast<double>(circleCenterY);
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
