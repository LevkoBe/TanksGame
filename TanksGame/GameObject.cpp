#include "GameObject.h"

GameObject::GameObject(int initialXPos, int initialYPos, int initialSize, int initialMaxSpeed, int initialMaxAccel, int angle, ObjectShape shape)
    : xPos(initialXPos), yPos(initialYPos), size(initialSize), maxSpeed(initialMaxSpeed), maxAccel(initialMaxAccel), angle(angle), shape(shape) {}

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


