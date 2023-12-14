#include "GameObject.h"

GameObject::GameObject(int initialXPos, int initialYPos, int initialSize, int initialMaxSpeed, int initialMaxAccel, std::string image)
    : xPos(initialXPos), yPos(initialYPos), size(initialSize), maxSpeed(initialMaxSpeed), maxAccel(initialMaxAccel), image(image) {}

std::pair<int, int> GameObject::getPos() const {
    return std::make_pair(xPos, yPos);
}

std::pair<int, int> GameObject::getVel() const {
    return std::make_pair(xVel, yVel);
}

std::pair<int, int> GameObject::getAcc() const {
    return std::make_pair(xAcc, yAcc);
}

int GameObject::getMaxSpeed() const {
    return maxSpeed;
}

int GameObject::getMaxAccel() const {
    return maxAccel;
}

int GameObject::getSize() const {
    return size;
}

int GameObject::getChange() const {
    return change;
}

double GameObject::getSpeed() const {
    return sqrt(xVel * xVel + yVel * yVel);
}

bool GameObject::withStandTheShot(int damage) {
    healthPoints -= damage;
    if (healthPoints <= 0)
    {
        return false;
    }
    return true;
}

void GameObject::scale(double scales) {
    size *= scales;
}

