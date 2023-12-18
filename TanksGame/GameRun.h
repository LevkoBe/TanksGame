#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include "GameObject.h"
#include "BotTank.h"
#include "Commands.h"
#include "Projectile.h"
#include "GameState.h"
#include "PathFinder.h"
#include "CollisionHandler.h" // Include CollisionHandler header

enum ControlMode {
    LeftUpRightDown,
    RotatePosition,
    RotateVelocity,
    RotateAcceleration
};

class GameRun {
private:
    int level;
    int windowSize = 800;
    int gridSize = 10;
    int cellSize = 80;
    ControlMode mode = RotateVelocity;
    std::shared_ptr<Tank> userTank;
    std::shared_ptr<std::vector<BotTank>> bots;
    std::shared_ptr<std::vector<BotTank>> allBots;
    std::shared_ptr<std::vector<GameObject>> walls;
    std::shared_ptr<std::vector<Projectile>> projectiles;
    std::shared_ptr<std::vector<std::vector<bool>>> wallsMap;
    PathFinder pathfinder;

public:
    GameRun(int windowSize, int gridSize, int difficulty);

    std::pair<int, int> getPxCoordinates(int mapCoordX, int mapCoordY);

    void createMap();
    void createWall(int i, int j, const std::vector<std::string>& wallTextures);
    void createBots(int count);
    void addBot(int position);
    void initializeUserTankRotation();

    void moveBot(BotTank& bot);
    void processCommands(std::vector<Command> commands);
    GameState update(std::vector<Command> commands);
    GameState positions();

    void setUserTankSpeed(int extent);
    void moveUserTank();
    void moveTank(BotTank& tank);
    void moveTank(Tank& tank);

    void moveProjectile(Projectile& projectile);

    bool insideGameField(int x, int y, int radius) const;
    void changeSize(double increase);
    bool insideGameField(int x, int y) const;


    float calculateRotationAngle(int startX, int startY, int targetX, int targetY) const;

    std::pair<int, int> calculatePositionOnBinaryMap(const std::pair<int, int>& realPosition) const;
};
