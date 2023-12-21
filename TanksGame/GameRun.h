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
    GameRun(int windowSize, int gridSize, int difficulty, GameRun previousGame);

    bool isFinished() { return false; }

    template <typename TankType>
    bool collisionsWithUser(int xExpected, int yExpected, TankType& bot);

    std::pair<int, int> getPxCoordinates(int mapCoordX, int mapCoordY);

    void createMap();
    void restoreMap();

    float calculateRotationAngle(int startX, int startY, int targetX, int targetY) const;

    void processCommands(std::vector<Command> commands);

    GameState update(std::vector<Command> commands);

    void moveBot(BotTank& bot);

    GameState positions();

    void moveTank(Tank& tank);
    void moveTank(BotTank& tank);

    void moveProjectile(Projectile& projectile);

    bool collisionsWithWalls(int xExpected, int yExpected, double sensitivity);

    bool collisionsWithBots(int xExpected, int yExpected);

    bool collisionsBotBots(int xExpected, int yExpected, BotTank& actualBot);

    bool hitsBots(int x, int y, Projectile projectile);

    bool hitsUserTank(int x, int y, Projectile projectile);

    bool insideGameField(int x, int y, int size) const;
    
    bool addBot(int position);

    bool insideGameField(int x, int y) const;

    void changeSize(double increase);

    void run() {}

    bool hasLineOfSight(BotTank& source) const;
};

