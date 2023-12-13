#pragma once
#include "GameObject.h"
#include "Projectiles.h"

class Projectile: public GameObject
{
    ProjectileType projectile;
    int damage = 10;
public:
    Projectile(ProjectileType type = CannonBall, int damage = 10) :
        GameObject(0, 0, 100, 100, 100, -90, Circle), projectile(type), damage(damage) {};

    bool destroyObject(GameObject& object) {
        return !object.withStandTheShot(damage);
    }
};

