#pragma once

#include "Tank.h"
#include "BotTank.h"
#include "Projectile.h"
#include "GameObject.h"
#include <vector>
#include <algorithm>

class CollisionHandler {
public:
    static bool circlesColliding(int x1, int y1, int radius1, int x2, int y2, int radius2);

    static bool squareCircleColliding(double squareTopLeftX, double squareTopLeftY, double squareSize, double circleCenterX, double circleCenterY, double circleRadius);

    static bool squareCircleColliding(int squareX, int squareY, int squareSize, int circleCenterX, int circleCenterY, int circleRadius);

    static bool collisionsWithWalls(int xExpected, int yExpected, const std::vector<GameObject>& walls, Tank& userTank);

    static bool collisionsWithBots(int xExpected, int yExpected, const std::vector<BotTank>& bots, Tank& userTank);

    static bool collisionsWithUser(int xExpected, int yExpected, BotTank& bot, const Tank& user);

    static bool collisionsBotBots(int xExpected, int yExpected, const BotTank& actualBot, const std::vector<BotTank>& bots);

    static bool hitsWalls(int x, int y, const Projectile& projectile, std::vector<GameObject>& walls, std::vector<Projectile>& projectiles);

    static bool hitsBots(int x, int y, const Projectile& projectile, std::vector<BotTank>& bots, std::vector<Projectile>& projectiles);

    static bool hitsUserTank(int x, int y, const Projectile& projectile, Tank& userTank, std::vector<Projectile>& projectiles);
};

