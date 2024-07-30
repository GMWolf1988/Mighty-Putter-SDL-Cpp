#pragma once

#include <SDL.h>
#include "Vector.h"
#include "Object.h"
#include "RigidBody.h"

// Define a Barrier class that inherits from the Object class
class Barrier : public RigidBody
{
public:
    // Constructor that initializes the ball object with a given position and rotation
    Barrier(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees = 0);

    // Update function that updates the Wall object's state based on input and time
    void Update(const InputState& input, double deltaTime) override;

    // Draw function that draws the Wall object to the screen
    void Draw() override;

    // This function sets the range of x - coordinates and moves the range by the specified amount
    void SetXRange(float minX, float maxX, const Vector2f& moveAmount);
    // This function sets the range of y - coordinates and moves the range by the specified amount
    void SetYRange(float minY, float maxY, const Vector2f& moveAmount);

    // These functions return the minimum and maximum x- and y-coordinates of the object
    float GetMinX() const;
    float GetMaxX() const;
    float GetMinY() const;
    float GetMaxY() const;

    // This function slows down the object by the specified factor for the specified duration
    void SlowDown(float factor, double duration);

private:
    // These variables store the object's minimum and maximum x-coordinates, its movement amount, and its minimum and maximum y-coordinates
    float mMinX;
    float mMaxX;
    Vector2f mMoveAmount;
    float mMinY;
    float mMaxY;

};
