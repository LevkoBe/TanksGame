#include "Tank.h"

Tank::Tank(int coefficient, int size, std::string image) :
    GameObject(size / 2, size / 2, size, 0, 0.0, image),
    pDamage(coefficient), projectile(CannonBall) {}

void Tank::rotate(double angle) {
    rotationAngle += angle;
    double angleRadians = (rotationAngle - 90) * M_PI / 180.0;

    xVel = speed * std::cos(angleRadians);
    yVel = speed * std::sin(angleRadians);
}

void Tank::accelerate(int extent) {
    double angleRadians = (rotationAngle - 90) * M_PI / 180.0;

    xAcc += extent * change * std::cos(angleRadians);
    yAcc += extent * change * std::sin(angleRadians);
}

int Tank::getPDamage() const { return pDamage; }
ProjectileType Tank::getProjectile() const { return projectile; }

void Tank::stop() {
    xVel = 0;
    yVel = 0;
    speed = 0;
}
