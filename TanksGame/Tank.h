#pragma once
#include "GameObject.h"

enum ProjectileType {
    CannonBall, // basic
    FireBall,   // burns
    SnowBall,   // slows down
    Chip,       // turns into an ally
    Magnet,     // attracts to itself
    LazerBeam,  // basically basic
    Reducer     // makes smaller
};

class Tank : public GameObject {
private:
    int vMove;
    int vShoot;
    int vReload;
    int pHealth;
    int pDamage;
    int pxSize;
    ProjectileType projectile;

public:
    Tank(int coefficient = 100);

    Tank(int vMove, int vShoot, int vReload, int pHealth, int pDamage, int size, ProjectileType projectile = CannonBall);

    void move(int x, int y) {}
    void shoot() {}
    void setProjectileType(ProjectileType projectileType) {}
};
