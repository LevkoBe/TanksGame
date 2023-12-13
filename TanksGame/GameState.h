#pragma once
#include <iostream>
#include <vector>

class Tank;
class GameObject;
class Projectile;

struct GameState {
    std::pair<int, int> userTankPosition;
    std::shared_ptr<std::vector<Tank>> bots;
    std::shared_ptr<std::vector<GameObject>> walls;
    std::shared_ptr<std::vector<Projectile>> projectiles;
};