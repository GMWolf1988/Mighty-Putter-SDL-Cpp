#pragma once

#include <cmath>

// Define a struct to represent a transformation with a position and orientation
struct Transform
{
    float positionX; // The x-coordinate of the position
    float positionY; // The y-coordinate of the position
    float cosine; // The cosine of the orientation angle
    float sine; // The sine of the orientation angle

    // Constructor that takes an x-coordinate, y-coordinate, and angle in radians to initialize the struct
    Transform(float x, float y, float angle)
        : positionX(x)
        , positionY(y)
        , cosine(cos(angle))
        , sine(sin(angle))
    {}
};