#include "GameObject.h"

GameObject::GameObject(int initialXPos, int initialYPos, int initialSize, int initialMaxSpeed, int initialMaxAccel, int angle, ObjectShape shape)
    : xPos(initialXPos), yPos(initialYPos), size(initialSize), maxSpeed(initialMaxSpeed), maxAccel(initialMaxAccel), angle(angle), shape(shape) {}

std::tuple<int, int> GameObject::getPos() const {
    return std::make_tuple(xPos, yPos);
}

std::tuple<int, int> GameObject::getVel() const {
    return std::make_tuple(xVel, yVel);
}

int GameObject::getMaxSpeed() const {
    return maxSpeed;
}

std::tuple<int, int> GameObject::getAcc() const {
    return std::make_tuple(xAcc, yAcc);
}

int GameObject::getMaxAccel() const {
    return maxAccel;
}


