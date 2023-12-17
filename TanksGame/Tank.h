#pragma once
#include "GameObject.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cmath>
#include <vector>
#include "Projectiles.h"
#include "Projectile.h"

class Tank : public GameObject {
private:
    int vMove = 0; // +=10
    int vShoot = 40;
    int vReload = 0; // may increase
    int pHealth = 100;
    int pDamage = 10;
    int speed = 0;
    double rotationAngle = 90.0;
    ProjectileType projectile;

public:
    Tank(int coefficient = 100, int size = 100, std::string image = "./images/prototank001.png");

    Tank(int vMove, int vShoot, int vReload, int pHealth, int pDamage, int size, ProjectileType projectile = CannonBall);

    int getVMove() const;
    int getVShoot() const;
    int getVReload() const;
    int getPHealth() const;
    int getPDamage() const;
    int getAcceleration() const;
    ProjectileType getProjectile() const;

    void setPosition(int x, int y);

    void setVelocity(int x, int y);

    void accelerate(int extent);

    void speedUp(int extent);

    void rotate(double angle);

    void shoot(std::shared_ptr<std::vector<Projectile>> projectiles) {
        Projectile prj(projectile, pDamage, rotationAngle);
    }

    void stop();

    double getAngle() const {
        return rotationAngle;
    }
    
    void setProjectileType(ProjectileType projectileType) {}
};
