#pragma once
#include <iostream>
#include <tuple>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
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
    int speed = 0;
    int xAcc = 0;
    int yAcc = 0;
    int change = 10; // standardized increase for velocity, acceleration, and position
    int size = 100;
    int healthPoints = 100;
    double rotationAngle = 0.0;
    std::string image = "none";

public:
    GameObject(int initialXPos, int initialYPos, int initialSize, int speed, double angle = 0, std::string image = "none");
    
    bool operator==(const GameObject& other) const {
        // Compare all relevant attributes for equality
        return std::tie(xPos, yPos, xVel, yVel, speed, xAcc, yAcc, change, size, healthPoints, rotationAngle, image) ==
            std::tie(other.xPos, other.yPos, other.xVel, other.yVel, other.speed, other.xAcc, other.yAcc, other.change,
                other.size, other.healthPoints, other.rotationAngle, other.image);
    }

    std::pair<int, int> getPos() const;

    std::pair<int, int> getVel() const;

    void setPosition(int x, int y);

    void setVelocity(int x, int y);

    void setSpeed(int s);

    void setAngle(double angle);

    std::pair<int, int> getAcc() const;

    int getAcceleration() const;

    int getSize() const;

    int getChange() const;

    double getSpeed() const;

    void speedUp(int extent);

    void setVelocity();

    bool withstandTheShot(int damage);

    std::string getImageName() const {
        return image;
    }

    void scale(double scales);

    double getAngle() const;
};