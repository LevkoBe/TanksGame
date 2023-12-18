#include "GameRun.h"
#include "Map.h"
#include "FolderReader.h"
#include <random>

GameRun::GameRun(int windowSize, int gridSize, int difficulty)
    : windowSize(windowSize), level(difficulty), gridSize(gridSize),
    cellSize(windowSize / gridSize), userTank(new Tank(difficulty * 10, cellSize)),
    pathfinder(wallsMap, gridSize) {
    createMap();
    createBots(difficulty);
    initializeUserTankRotation();
}

void GameRun::moveBot(BotTank& bot) {
    std::pair<int, int> botMapPos = calculatePositionOnBinaryMap(bot.getPos());
    std::pair<int, int> userMapPos = calculatePositionOnBinaryMap(userTank->getPos());

    Node nextCell = pathfinder.findNextCell(botMapPos.first, botMapPos.second, userMapPos.first, userMapPos.second);
    auto coords = getPxCoordinates(nextCell.x, nextCell.y);

    bot.setSpeed(level * (cellSize) / 30);
    bot.setAngle(calculateRotationAngle(bot.getPos().first, bot.getPos().second, coords.first, coords.second));
    bot.setVelocity();
    moveTank(bot);
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

std::pair<int, int> GameRun::calculatePositionOnBinaryMap(const std::pair<int, int>& realPosition) const {
    int x = realPosition.first / cellSize;
    int y = realPosition.second / cellSize;
    return { x, y };
}

void GameRun::createMap() {
    Map map(gridSize);
    std::vector<std::string> wallTextures = FolderReader::GetFilesInDirectory("./images/walls");
    int wallSize = cellSize;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if ((*map.map)[i][j] == Wall) {
                createWall(i, j, wallTextures);
            }
        }
    }
}

void GameRun::createWall(int i, int j, const std::vector<std::string>& wallTextures) {
    int xPos = cellSize * i;
    int yPos = cellSize * j;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> distribution(0, wallTextures.size() - 1);
    size_t randomIndex = distribution(gen);
    std::string image = wallTextures[randomIndex];

    walls->push_back(GameObject(xPos, yPos, cellSize, 0, 0, image));
    (*wallsMap)[i][j] = true;
}

void GameRun::createBots(int count) {
    for (int i = 0; i < count; i++) {
        allBots->push_back(BotTank(i + 1, cellSize));
    }
    for (int i = 0; i < 3; i++) {
        addBot(i);
    }
}

void GameRun::addBot(int position) {
    if (allBots->empty()) return;

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
}

void GameRun::initializeUserTankRotation() {
    Node nextCell = pathfinder.findNextCell(0, 0, gridSize - 1, gridSize - 1);
    userTank->setAngle(calculateRotationAngle(0, 0, nextCell.x, nextCell.y));
}

void GameRun::processCommands(std::vector<Command> commands) {
    for (auto& command : commands) {
        switch (command) {
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
            setUserTankSpeed(1);
            break;
        case MoveBackward:
            setUserTankSpeed(-1);
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

    for (auto& bot : *bots) {
        moveBot(bot);
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

void GameRun::setUserTankSpeed(int extent) {
    switch (mode) {
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
    moveTank(*userTank);
}

void GameRun::moveTank(Tank& tank) {
    tank.speedUp(tank.getAcceleration());
    int xExpected = tank.getPos().first + tank.getVel().first;
    int yExpected = tank.getPos().second + tank.getVel().second;

    if (!insideGameField(xExpected, yExpected, tank.getSize() / 4)) {
        return;
    }

    if (CollisionHandler::collisionsWithWalls(xExpected, yExpected, *walls, *userTank)) {
        return;
    }

    if (CollisionHandler::collisionsWithBots(xExpected, yExpected, *bots, *userTank)) {
        return;
    }

    tank.setPosition(xExpected, yExpected);

    if (mode == RotatePosition) {
        tank.stop();
    }
}

void GameRun::moveTank(BotTank& tank) {
    tank.speedUp(tank.getAcceleration());
    int xExpected = tank.getPos().first + tank.getVel().first;
    int yExpected = tank.getPos().second + tank.getVel().second;

    if (!insideGameField(xExpected, yExpected, tank.getSize() / 4)) {
        return;
    }

    if (CollisionHandler::collisionsWithWalls(xExpected, yExpected, *walls, *userTank)) {
        return;
    }

    if (CollisionHandler::collisionsBotBots(xExpected, yExpected, tank, *bots)) {
        return;
    }

    if (CollisionHandler::collisionsWithUser(xExpected, yExpected, tank, *userTank)) {
        return;
    }

    tank.setPosition(xExpected, yExpected);

    if (mode == RotatePosition) {
        tank.stop();
    }
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

    if (CollisionHandler::hitsWalls(x, y, projectile, *walls, *projectiles)) {
        return;
    }

    if (CollisionHandler::hitsBots(x, y, projectile, *bots, *projectiles)) {
        return;
    }

    if (CollisionHandler::hitsUserTank(x, y, projectile, *userTank, *projectiles)) {
        return;
    }
}

bool GameRun::insideGameField(int x, int y, int radius) const {
    if (insideGameField(x - radius, y - radius) &&
        insideGameField(x - radius, y + radius) &&
        insideGameField(x + radius, y - radius) &&
        insideGameField(x + radius, y + radius)) {
        return true;
    }

    userTank->stop();
    return false;
}

void GameRun::changeSize(double increase) {
    userTank->scale(increase);
}


bool GameRun::insideGameField(int x, int y) const {
    return x > 0 && y > 0 && x < windowSize && y < windowSize;
}
