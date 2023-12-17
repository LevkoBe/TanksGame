#pragma once
#include <vector>
#include "GameObject.h"
#include "Projectiles.h"
#include "Projectile.h"

class Tank : public GameObject {
private:
    int pDamage = 10;
    ProjectileType projectile = CannonBall;

public:
    Tank(int coefficient = 100, int size = 100, std::string image = "./images/prototank001.png");

    int getPDamage() const;
    ProjectileType getProjectile() const;

    void accelerate(int extent);

    void rotate(double angle);

    void shoot(std::shared_ptr<std::vector<Projectile>> projectiles) {
        projectiles->push_back(Projectile(pDamage, xPos, yPos, size, projectile, rotationAngle));
    }

    void stop();
    
    void setProjectileType(ProjectileType projectileType) {}
};
