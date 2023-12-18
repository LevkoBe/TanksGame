#pragma once
#include <iostream>
#include <vector>

class Tank;
class GameObject;
class Projectile;

struct GameState {
    std::shared_ptr<Tank> userTank;
    std::shared_ptr<std::vector<BotTank>> bots;
    std::shared_ptr<std::vector<GameObject>> walls;
    std::shared_ptr<std::vector<Projectile>> projectiles;
};