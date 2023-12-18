#pragma once
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "GameObject.h"
#include "Projectiles.h"

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
    Projectile(int damage, int tankX, int tankY, int tankSize, ProjectileType type, double angle) : projectile(type), angle(angle), damage(damage),
        GameObject(calculateX(tankX, tankSize, angle, type), calculateY(tankY, tankSize, angle, type), calculateSize(tankSize, type), 45, angle, "./images/cannonBall.png") {};

    bool destroyObject(GameObject& object) const {
        return !object.withstandTheShot(damage);
    }

    double getAngle() const {
        return angle;
    }
};
