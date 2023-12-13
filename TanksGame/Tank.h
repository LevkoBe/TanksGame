#pragma once
#include "GameObject.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cmath>
#include "Projectiles.h"

class Tank : public GameObject {
private:
    int vMove = 0; // +=10
    int vShoot = 40;
    int vReload = 0; // may increase
    int pHealth = 100;
    int pDamage = 10;
    int pxSize = 40;
    double rotationAngle = 90.0;
    ProjectileType projectile;

public:
    Tank(int coefficient = 100);

    Tank(int vMove, int vShoot, int vReload, int pHealth, int pDamage, int size, ProjectileType projectile = CannonBall);

    int getVMove() const;
    int getVShoot() const;
    int getVReload() const;
    int getPHealth() const;
    int getPDamage() const;
    int getPxSize() const;
    int getAcceleration() const;
    ProjectileType getProjectile() const;

    void accelerate(int extent);

    void speedUp(int extent);

    void rotate(double angle);
    void shoot() {}
    void setProjectileType(ProjectileType projectileType) {}
};
