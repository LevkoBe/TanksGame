#pragma once
#include "GameObject.h"
#include "Projectiles.h"

class Projectile: public GameObject
{
    ProjectileType projectile;
    int damage = 10;
    double angle = -90;
public:
    Projectile(ProjectileType type = CannonBall, int damage = 10, double angle = 0) :
        GameObject(0, 0, 100, 100, 100, "none"), projectile(type), damage(damage), angle(angle - 90) {};

    bool destroyObject(GameObject& object) {
        return !object.withStandTheShot(damage);
    }

    double getAngle() {
        return angle;
    }
};

