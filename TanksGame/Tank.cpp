#include "Tank.h"

Tank::Tank(int coefficient) :
    GameObject(0, 0, coefficient / 100 * 100, coefficient / 100 * 100, coefficient / 100 * 100, -90, Circle),
    pHealth(coefficient / 100 * 100), pDamage(coefficient / 100 * 10), pxSize(coefficient / 100 * 100),
    projectile(CannonBall), vMove(coefficient / 100 * 10), vShoot(coefficient / 100 * 20), vReload(coefficient / 100 * 10) {}

Tank::Tank(int vMove, int vShoot, int vReload, int pHealth, int pDamage, int size, ProjectileType projectile) :
    GameObject(0, 0, size, size, size, -90, Circle),
    vMove(vMove), vShoot(vShoot), vReload(vReload), pHealth(pHealth), pDamage(pDamage), pxSize(size), projectile(projectile) {}
