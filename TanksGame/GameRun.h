#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include "GameObject.h"
#include "Map.h"
#include "BotTank.h"
#include "Commands.h" // todo: check if needed line
#include "Projectile.h"
#include "GameState.h"
#include "PathFinder.h"

class GameRun {
private:
    int level;
    int windowSize = 800;
    int gridSize = 10;
    int cellSize = 80;
    std::shared_ptr<Tank> userTank;
    std::shared_ptr<std::vector<BotTank>> bots = std::make_shared<std::vector<BotTank>>();
    std::shared_ptr<std::vector<BotTank>> allBots = std::make_shared<std::vector<BotTank>>();
    std::shared_ptr<std::vector<GameObject>> walls = std::make_shared<std::vector<GameObject>>();
    std::shared_ptr<std::vector<Projectile>> projectiles = std::make_shared<std::vector<Projectile>>();
    std::shared_ptr<std::vector<std::vector<bool>>> wallsMap = 
        std::make_shared<std::vector<std::vector<bool>>>(gridSize, std::vector<bool>(gridSize, false));
    PathFinder pathfinder;

public:
    GameRun(int windowSize, int gridSize, int difficulty);

    template <typename TankType>
    bool collisionsWithUser(int xExpected, int yExpected, TankType& bot);

    std::pair<int, int> getPxCoordinates(int mapCoordX, int mapCoordY);

    void createMap();

    void moveTankWithSpeed(Tank& tank, int direction, double speed);

    int calculateSpeed(int startX, int startY, int targetX, int targetY, BotTank& bot) const;

    float calculateRotationAngle(int startX, int startY, int targetX, int targetY) const;

    std::pair<int, int> calculatePositionOnBinaryMap(const std::pair<int, int>& realPosition) const;

    void moveBot(Tank& bot);

    void reset() {}

    void processCommands(std::vector<Command> commands);

    GameState update(std::vector<Command> commands);

    void moveBot(BotTank& bot);

    GameState positions();

    void moveUserTank();

    template <typename TankType>
    void moveTank(TankType& tank);

    void moveProjectile(Projectile& projectile);

    bool collisionsWithWalls(int xExpected, int yExpected);

    bool collisionsWithBots(int xExpected, int yExpected);

    template <typename TankType>
    bool collisionsBotBots(int xExpected, int yExpected, TankType& actualBot);

    bool hitsWalls(int x, int y, Projectile projectile);

    bool hitsBots(int x, int y, Projectile projectile);

    bool hitsUserTank(int x, int y, Projectile projectile);

    bool collisionsWithProjectiles(int xExpected, int yExpected);

    bool insideGameField(int x, int y, int size) const;
    
    bool addBot(int position);

    bool circlesColliding(int x1, int y1, int radius1, int x2, int y2, int radius2);

    bool squareCircleColliding(double squareX, double squareY, double squareSize, double circleX, double circleY, double circleRadius);

    bool squareCircleColliding(int squareX, int squareY, int squareSize, int circleX, int circleY, int circleRadius);

    bool insideGameField(int x, int y) const;

    void changeSize(double increase);

    void run() {}
};

