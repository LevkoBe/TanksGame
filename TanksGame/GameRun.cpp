#define NOMINMAX
#include "GameRun.h"
#include "BotTank.h"
#include "FolderReader.h"
#include "CollisionHandler.h"
#include <windows.h>

GameRun::GameRun(int windowSize, int gridSize, int difficulty) : windowSize(windowSize), level(difficulty), gridSize(gridSize),
cellSize(windowSize / gridSize), userTank(new Tank(difficulty * 10, cellSize)), pathfinder(wallsMap, gridSize) {
    createMap();
    for (int i = 0; i < difficulty; i++)
    {
        allBots->push_back(BotTank(i + 1, cellSize));
    }
    for (int i = 0; i < 3; i++)
    {
        addBot(i);
    }
    // rotate userTank accordingly to map
    Node nextCell = pathfinder.findNextCell(0, 0, gridSize - 1, gridSize - 1);
    userTank->setAngle(calculateRotationAngle(0, 0, nextCell.x, nextCell.y));
}

GameRun::GameRun(int windowSize, int gridSize, int difficulty, GameRun previousGame) : windowSize(windowSize), level(difficulty), gridSize(gridSize),
cellSize(windowSize / gridSize), userTank(new Tank(difficulty * 10, cellSize)), pathfinder(wallsMap, gridSize) {
    wallsMap = move(previousGame.wallsMap);
    restoreMap();
    for (int i = 0; i < difficulty; i++)
    {
        allBots->push_back(BotTank(i + 1, cellSize));
    }
    for (int i = 0; i < 3; i++)
    {
        addBot(i);
    }
    // rotate userTank accordingly to map
    Node nextCell = pathfinder.findNextCell(0, 0, gridSize - 1, gridSize - 1);
    userTank->setAngle(calculateRotationAngle(0, 0, nextCell.x, nextCell.y));
}

void GameRun::moveBot(BotTank& bot) {
    std::pair<int, int> botMapPos = PathFinder::calculatePositionOnBinaryMap(bot.getPos(), cellSize);
    std::pair<int, int> userMapPos = PathFinder::calculatePositionOnBinaryMap(userTank->getPos(), cellSize);

    Node nextCell = pathfinder.findNextCell(botMapPos.first, botMapPos.second, userMapPos.first, userMapPos.second);
    auto coords = getPxCoordinates(nextCell.x, nextCell.y);

    bot.setSpeed(bot.getChange() * level * (cellSize) / 300);
    bot.setAngle(calculateRotationAngle(bot.getPos().first, bot.getPos().second, coords.first, coords.second));
    bot.setVelocity();
    

    if (hasLineOfSight(bot)) {
        bot.shoot(projectiles);
    }
    else {
        moveTank(bot);
    }
}

std::pair<int, int> GameRun::getPxCoordinates(int mapCoordX, int mapCoordY) {
    int pxX = (mapCoordX + 0.5) * cellSize;
    int pxY = (mapCoordY + 0.5) * cellSize;
    return { pxX, pxY };
}

float GameRun::calculateRotationAngle(int startX, int startY, int targetX, int targetY) const {
    int dx = targetX - startX;
    int dy = targetY - startY;
    return atan2(dy, dx) * 180.0 / M_PI + 90.0;
}

void GameRun::createMap() {
    Map map(gridSize);
    std::vector<std::string> wallTextures = FolderReader::GetFilesInDirectory("./images/walls");
    int wallSize = cellSize;
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
                std::uniform_int_distribution<size_t> distribution(0, 100);
                size_t randomIndex = distribution(gen);
                if (randomIndex < 60)
                {
                    std::string image = wallTextures[randomIndex % (wallTextures.size() - 1)];
                    walls->push_back(GameObject(xPos, yPos, wallSize, 0, 0, image));
                    (*wallsMap)[i][j] = true;
                }
            }
        }
    }
}

void GameRun::restoreMap() {
    std::vector<std::string> wallTextures = FolderReader::GetFilesInDirectory("./images/walls");
    int wallSize = cellSize;
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if ((*wallsMap)[i][j] == true)
            {
                int xPos = wallSize * i;
                int yPos = wallSize * j;

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<size_t> distribution(0, 100);
                size_t randomIndex = distribution(gen);

                std::string image = wallTextures[randomIndex % (wallTextures.size() - 1)];
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
            userTank->rotate(10.0);
            break;
        case RotateCounterClockWise:
            userTank->rotate(-10.0);
            break;
        case MoveForward:
            userTank->speedUp(1);
            break;
        case MoveBackward:
            userTank->speedUp(-1);
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
    moveTank(*userTank);
    for (auto& projectile : (*projectiles)) {
        moveProjectile(projectile);
    }
    if (userTank != nullptr)
    {
        for (auto& bot : *bots) {
            moveBot(bot);
        }
    }
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

void GameRun::moveTank(Tank& tank) {
    int xExpected = tank.getPos().first + tank.getVel().first;
    int yExpected = tank.getPos().second + tank.getVel().second;

    if (!insideGameField(xExpected, yExpected, tank.getSize() / 4) ||
        collisionsWithWalls(xExpected, yExpected, 1)) {
        tank.stop();
        return;
    }

    if (collisionsWithBots(xExpected, yExpected)) {
        tank.stop();
        return;
    }

    tank.setPosition(xExpected, yExpected);
}

void GameRun::moveTank(BotTank& tank) {
    int xExpected = tank.getPos().first + tank.getVel().first;
    int yExpected = tank.getPos().second + tank.getVel().second;

    if (!insideGameField(xExpected, yExpected, tank.getSize() / 4) ||
        collisionsWithWalls(xExpected, yExpected, 0.5)) {
        tank.stop();
        return;
    }

    if (collisionsBotBots(xExpected, yExpected, tank) || collisionsWithUser(xExpected, yExpected, tank)) {
        tank.stop();
        return;
    }

    tank.setPosition(xExpected, yExpected);
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

    if (projectile.hitsWalls(x, y, *projectiles, *walls, *wallsMap)) { return; } // todo: R-tree

    if (hitsBots(x, y, projectile)) { return; }

    if (hitsUserTank(x, y, projectile)) { return; }
}

bool GameRun::collisionsWithWalls(int xExpected, int yExpected, double sensitivity) {

    for (auto& wall : *walls) {
        if (CollisionHandler::squareCircleColliding(wall.getPos().first, wall.getPos().second, static_cast<int>(wall.getSize()), xExpected, yExpected, static_cast<int>(sensitivity * userTank->getSize() / 4))) {
            return true;
        }
    }
    return false;
}

bool GameRun::collisionsWithBots(int xExpected, int yExpected) {
    for (auto& bot : *bots) {
        if (CollisionHandler::circlesColliding(bot.getPos().first, bot.getPos().second, bot.getSize() / 4, xExpected, yExpected, userTank->getSize() / 4)) {
            return true;
        }
    }
    return false;
}

template <typename TankType>
bool GameRun::collisionsWithUser(int xExpected, int yExpected, TankType& bot) {
    if (CollisionHandler::circlesColliding(userTank->getPos().first, userTank->getPos().second, userTank->getSize() / 4, xExpected, yExpected, bot.getSize() / 4)) {
        return true;
    }
    return false;
}


bool GameRun::collisionsBotBots(int xExpected, int yExpected, BotTank& actualBot) {
    for (auto& bot : *bots) {
        if (bot == actualBot) { continue; }
        if (CollisionHandler::circlesColliding(bot.getPos().first, bot.getPos().second, bot.getSize() / 4, xExpected, yExpected, userTank->getSize() / 4)) {
            return true;
        }
    }
    return false;
}

bool GameRun::hitsBots(int x, int y, Projectile projectile) {

    for (auto& bot : *bots) {
        if (CollisionHandler::circlesColliding(bot.getPos().first, bot.getPos().second, bot.getSize() / 4, x, y, projectile.getSize() / 4))
        {
            if (projectile.damageObject(bot)) {
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

bool GameRun::hitsUserTank(int x, int y, Projectile projectile) {

    if (CollisionHandler::circlesColliding(userTank->getPos().first, userTank->getPos().second, userTank->getSize() / 4, x, y, projectile.getSize() / 4))
    {
        projectile.damageObject(*userTank);

        auto it = std::find(projectiles->begin(), projectiles->end(), projectile);
        if (it != projectiles->end()) {
            projectiles->erase(it);
        }
        return true;
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
    return false;
}

bool GameRun::addBot(int position) {
    if (allBots->size() <= 0) { return false; }

    auto theTank = allBots->back();
    allBots->pop_back();
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

bool GameRun::insideGameField(int x, int y) const {
    return x > 0 && y > 0 && x < windowSize && y < windowSize;
}

bool GameRun::hasLineOfSight(BotTank& bot) const {
    int botX = bot.getPos().first;
    int botY = bot.getPos().second;
    int userX = userTank->getPos().first;
    int userY = userTank->getPos().second;

    if (pathfinder.hasLineOfSight(botX / cellSize, botY / cellSize, userX / cellSize, userY / cellSize)) {
        bot.setAngle(calculateRotationAngle(botX, botY, userX, userY));
        return true;
    }

    return false;
}


void GameRun::changeSize(double increase) {
    // todo: check if smaller than a cell;
    userTank->scale(increase);
}
