#pragma once
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "GameObject.h"
#include "CollisionHandler.h"
#include "Projectiles.h"
#include "PathFinder.h"
#include <vector>

class Projectile : public GameObject
{
    ProjectileType projectile;
    int damage = 10;
    double angle = -90;

    int calculateSize(int tankSize, ProjectileType projectile) {
        switch (projectile)
        {
        case CannonBall:
            return tankSize / 10;
        case FireBall:
        case SnowBall:
        case Chip:
        case Magnet:
        case BombaBall:
        case BlackHole:
        case SelfGuided:
            return tankSize / 5;
        case LazerBeam:
        case Reducer:
            return tankSize / 20;
        default:
            break;
        }
    }

    int calculateX(int tankX, int tankSize, double angle, ProjectileType type) {
        int sizes = (tankSize / 2 + calculateSize(tankSize, type) / 2);
        int x = static_cast<int>(cos((angle - 90) * M_PI / 180) * sizes);
        return tankX + x;
    }

    int calculateY(int tankY, int tankSize, double angle, ProjectileType type) {
        return tankY + static_cast<int>(sin((angle - 90) * M_PI / 180) * (tankSize / 2 + calculateSize(tankSize, type) / 2));
    }

public:

    bool operator==(const Projectile& other) const {
        return (xPos == other.getPos().first && yPos == other.getPos().second);
    }
    Projectile(int damage, int tankX, int tankY, int tankSize, int speed, ProjectileType type, double angle) : projectile(type), angle(angle), damage(damage),
        GameObject(calculateX(tankX, tankSize, angle, type), calculateY(tankY, tankSize, angle, type), calculateSize(tankSize, type), 45, angle, "./images/cannonBall.png") {};

    bool damageObject(GameObject& object) {
        return !object.withstandTheShot(damage);
    }

    double getAngle() const {
        return angle;
    }

    bool hitsWalls(int x, int y, std::vector<Projectile>& projectiles, std::vector<GameObject>& walls, std::vector<std::vector<bool>>& wallsMap) {

        for (auto& wall : walls) {
            if (CollisionHandler::squareCircleColliding(wall.getPos().first, wall.getPos().second, wall.getSize(), x, y, getSize() / 4))
            {
                if (damageObject(wall)) {
                    auto position = PathFinder::calculatePositionOnBinaryMap(wall.getPos(), wall.getSize());
                    wallsMap[position.first][position.second] = false;
                    auto it = std::find(walls.begin(), walls.end(), wall);
                    if (it != walls.end()) {
                        walls.erase(it);
                    }
                }

                auto it = projectiles.begin();
                while (it != projectiles.end()) {
                    if (*it == *this) {
                        it = projectiles.erase(it);
                        return true;
                    }
                    ++it;
                }
                return true;
            }
        }
        return false;
    }
};
