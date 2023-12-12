#pragma once
#include "GameObject.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cmath>

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
    int getAcceleration() const {
        return sqrt(xAcc * xAcc + yAcc * yAcc);
    }
    ProjectileType getProjectile() const;

    void accelerate(int extent) {
        double angleRadians = rotationAngle * M_PI / 180.0;
        
        xAcc += extent * change * std::cos(angleRadians);
        yAcc += extent * change * std::sin(angleRadians);
    }

    void speedUp(int extent) {
        double angleRadians = rotationAngle * M_PI / 180.0;

        xVel += extent * change * std::cos(angleRadians);
        yVel += extent * change * std::sin(angleRadians);
    }

    void rotate(double angle);
    void shoot() {}
    void setProjectileType(ProjectileType projectileType) {}
};
