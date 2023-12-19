#pragma once

class CollisionHandler
{
public:

    static bool circlesColliding(int x1, int y1, int radius1, int x2, int y2, int radius2);

    static bool squareCircleColliding(double squareX, double squareY, double squareSize, double circleX, double circleY, double circleRadius);

    static bool squareCircleColliding(int squareX, int squareY, int squareSize, int circleX, int circleY, int circleRadius);

};

