#include "CollisionHandler.h"
#include <cmath>
#include <algorithm>

bool CollisionHandler::circlesColliding(int x1, int y1, int radius1, int x2, int y2, int radius2) {
    int distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    return distance < (radius1 + radius2);
}

bool CollisionHandler::squareCircleColliding(double squareTopLeftX, double squareTopLeftY, double squareSize, double circleCenterX, double circleCenterY, double circleRadius) {
    double closestX = std::max(squareTopLeftX, std::min(circleCenterX, squareTopLeftX + squareSize));
    double closestY = std::max(squareTopLeftY, std::min(circleCenterY, squareTopLeftY + squareSize));

    double distance = std::sqrt(std::pow(closestX - circleCenterX, 2) + std::pow(closestY - circleCenterY, 2));
    return distance < circleRadius;
}

bool CollisionHandler::squareCircleColliding(int squareX, int squareY, int squareSize, int circleCenterX, int circleCenterY, int circleRadius) {
    double sqX = static_cast<double>(squareX);
    double sqY = static_cast<double>(squareY);
    double sqS = static_cast<double>(squareSize);
    double crX = static_cast<double>(circleCenterX);
    double crY = static_cast<double>(circleCenterY);
    double crR = static_cast<double>(circleRadius);
    return squareCircleColliding(sqX, sqY, sqS, crX, crY, crR);
}
