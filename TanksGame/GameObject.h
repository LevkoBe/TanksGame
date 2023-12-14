#pragma once
#include <iostream>
#include <tuple>
#include <cmath>

enum ObjectShape {
    Circle,
    Square
};

class GameObject {
protected:
    int xPos = 0;
    int yPos = 0;
    int xVel = 0;
    int yVel = 0;
    int xAcc = 0;
    int yAcc = 0;
    int change = 10; // standardized increase for velocity, acceleration, and position
    int size = 100;
    int maxSpeed = 100;
    int maxAccel = 10;
    int healthPoints = 100;
    std::string image = "none";

public:
    GameObject(int initialXPos, int initialYPos, int initialSize, int initialMaxSpeed, int initialMaxAccel, std::string image);

    std::pair<int, int> getPos() const;

    std::pair<int, int> getVel() const;

    std::pair<int, int> getAcc() const;

    int getSize() const;

    int getChange() const;

    double getSpeed() const;

    bool withStandTheShot(int damage);

    int getMaxSpeed() const;

    int getMaxAccel() const;

    std::string getImageName() const {
        return image;
    }

    void scale(double scales);
};