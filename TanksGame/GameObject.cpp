#include "GameObject.h"

GameObject::GameObject(int initialXPos, int initialYPos, int initialSize, int speed, double angle, std::string image)
    : xPos(initialXPos), yPos(initialYPos), size(initialSize), image(image), speed(speed), rotationAngle(angle) { setVelocity(); }

std::pair<int, int> GameObject::getPos() const {
    return std::make_pair(xPos, yPos);
}

std::pair<int, int> GameObject::getVel() const {
    return std::make_pair(xVel, yVel);
}

void GameObject::setPosition(int x, int y) {
    xPos = x;
    yPos = y;
}

void GameObject::setVelocity(int x, int y) {
    xVel = x;
    yVel = y;
}

void GameObject::setSpeed(int s) {
    speed = s;
}

void GameObject::setAngle(double angle) {
    rotationAngle = angle;
}

double GameObject::getAngle() const {
    return rotationAngle;
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

int GameObject::getHP() const {
    return healthPoints;
}

void GameObject::speedUp(int extent) {
    speed += extent * change;
    setVelocity();
}

void GameObject::setVelocity() {
    double angleRadians = (rotationAngle - 90) * M_PI / 180.0;

    xVel = speed * std::cos(angleRadians);
    yVel = speed * std::sin(angleRadians);
}

bool GameObject::withstandTheShot(int damage) {
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

