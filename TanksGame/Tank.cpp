#include "Tank.h"

Tank::Tank(int coefficient) :
    GameObject(0, 0, coefficient / 100 * 100, coefficient / 100 * 100, coefficient / 100 * 100, -90, Circle),
    pHealth(coefficient / 100 * 100), pDamage(coefficient / 100 * 10), pxSize(coefficient / 100 * 100),
    projectile(CannonBall), vMove(coefficient / 100 * 10), vShoot(coefficient / 100 * 20), vReload(coefficient / 100 * 10) {}

Tank::Tank(int vMove, int vShoot, int vReload, int pHealth, int pDamage, int size, ProjectileType projectile) :
    GameObject(0, 0, size, size, size, -90, Circle),
    vMove(vMove), vShoot(vShoot), vReload(vReload), pHealth(pHealth), pDamage(pDamage), pxSize(size), projectile(projectile) {}

void Tank::rotate(double angle) {
    rotationAngle += angle;
}

void Tank::accelerate(int extent) {
    double angleRadians = rotationAngle * M_PI / 180.0;

    xAcc += extent * change * std::cos(angleRadians);
    yAcc += extent * change * std::sin(angleRadians);
}

void Tank::speedUp(int extent) {
    double angleRadians = rotationAngle * M_PI / 180.0;

    xVel += extent * change * std::cos(angleRadians);
    yVel += extent * change * std::sin(angleRadians);
}

int Tank::getAcceleration() const {
    return sqrt(xAcc * xAcc + yAcc * yAcc);
}

int Tank::getVMove() const { return vMove; }
int Tank::getVShoot() const { return vShoot; }
int Tank::getVReload() const { return vReload; }
int Tank::getPHealth() const { return pHealth; }
int Tank::getPDamage() const { return pDamage; }
int Tank::getPxSize() const { return pxSize; }
ProjectileType Tank::getProjectile() const { return projectile; }
