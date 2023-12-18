#include "CollisionHandler.h"
#include <cmath>

bool CollisionHandler::circlesColliding(int x1, int y1, int radius1, int x2, int y2, int radius2) {
    int distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    return distance < (radius1 + radius2);
}

bool CollisionHandler::squareCircleColliding(double squareTopLeftX, double squareTopLeftY, double squareSize, double circleCenterX, double circleCenterY, double circleRadius) {
    double closestX = std::max(squareTopLeftX, std::min(circleCenterX, squareTopLeftX + squareSize));
    double closestY = std::max(squareTopLeftY, std::min(circleCenterY, squareTopLeftY + squareSize));

    double distance = std::sqrt(std::pow(closestX - circleCenterX, 2) + std::pow(closestY - circleCenterY, 2));
    return distance < circleRadius;
}

bool CollisionHandler::squareCircleColliding(int squareX, int squareY, int squareSize, int circleCenterX, int circleCenterY, int circleRadius) {
    double sqX = static_cast<double>(squareX);
    double sqY = static_cast<double>(squareY);
    double sqS = static_cast<double>(squareSize);
    double crX = static_cast<double>(circleCenterX);
    double crY = static_cast<double>(circleCenterY);
    double crR = static_cast<double>(circleRadius);
    return squareCircleColliding(sqX, sqY, sqS, crX, crY, crR);
}

bool CollisionHandler::collisionsWithWalls(int xExpected, int yExpected, const std::vector<GameObject>& walls, Tank& userTank) {
    for (const auto& wall : walls) {
        if (squareCircleColliding(wall.getPos().first, wall.getPos().second, static_cast<int>(wall.getSize()), xExpected, yExpected, userTank.getSize() / 4)) {
            userTank.stop();
            return true;
        }
    }
    return false;
}

bool CollisionHandler::collisionsWithBots(int xExpected, int yExpected, const std::vector<BotTank>& bots, Tank& userTank) {
    for (const auto& bot : bots) {
        if (circlesColliding(bot.getPos().first, bot.getPos().second, bot.getSize() / 4, xExpected, yExpected, userTank.getSize() / 4)) {
            userTank.stop();
            return true;
        }
    }
    return false;
}

bool CollisionHandler::collisionsWithUser(int xExpected, int yExpected, BotTank& bot, const Tank& user) {
    if (circlesColliding(user.getPos().first, user.getPos().second, user.getSize() / 4, xExpected, yExpected, bot.getSize() / 4)) {
        bot.stop();
        return true;
    }
    return false;
}

bool CollisionHandler::collisionsBotBots(int xExpected, int yExpected, const BotTank& actualBot, const std::vector<BotTank>& bots) {
    for (const auto& bot : bots) {
        if (bot == actualBot) continue;
        if (circlesColliding(bot.getPos().first, bot.getPos().second, bot.getSize() / 4, xExpected, yExpected, actualBot.getSize() / 4)) {
            return true;
        }
    }
    return false;
}

bool CollisionHandler::hitsWalls(int x, int y, const Projectile& projectile, std::vector<GameObject>& walls, std::vector<Projectile>& projectiles) {
    for (auto& wall : walls) {
        if (squareCircleColliding(wall.getPos().first, wall.getPos().second, wall.getSize(), x, y, projectile.getSize() / 4)) {
            if (projectile.destroyObject(wall)) {
                auto it = std::find(walls.begin(), walls.end(), wall);
                if (it != walls.end()) {
                    walls.erase(it);
                }
            }
            auto it = std::find(projectiles.begin(), projectiles.end(), projectile);
            if (it != projectiles.end()) {
                projectiles.erase(it);
            }
            return true;
        }
    }
    return false;
}

bool CollisionHandler::hitsBots(int x, int y, const Projectile& projectile, std::vector<BotTank>& bots, std::vector<Projectile>& projectiles) {
    for (auto& bot : bots) {
        if (circlesColliding(bot.getPos().first, bot.getPos().second, bot.getSize() / 4, x, y, projectile.getSize() / 4)) {
            if (projectile.destroyObject(bot)) {
                auto it = std::find(bots.begin(), bots.end(), bot);
                if (it != bots.end()) {
                    bots.erase(it);
                }
            }
            auto it = std::find(projectiles.begin(), projectiles.end(), projectile);
            if (it != projectiles.end()) {
                projectiles.erase(it);
            }
            return true;
        }
    }
    return false;
}

bool CollisionHandler::hitsUserTank(int x, int y, const Projectile& projectile, Tank& userTank, std::vector<Projectile>& projectiles) {
    if (circlesColliding(userTank.getPos().first, userTank.getPos().second, userTank.getSize() / 4, x, y, projectile.getSize() / 4)) {
        if (projectile.destroyObject(userTank)) {
            //userTank = nullptr; // instead we could check whether userTank still has HP
        }
        auto it = std::find(projectiles.begin(), projectiles.end(), projectile);
        if (it != projectiles.end()) {
            projectiles.erase(it);
        }
        return true;
    }
    return false;
}
