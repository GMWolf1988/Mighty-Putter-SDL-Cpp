#pragma once
#include <SDL.h>
#include "Object.h"
#include "RigidBody.h"

// Define a Barrier class that inherits from the Object class
class SlowMo : public RigidBody
{
public:
    // Constructor that initializes the ball object with a given position and rotation
    SlowMo(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees = 0);

    // Update function that updates the Wall object's state based on input and time
    void Update(const InputState& input, double deltaTime) override;

    // Draw function that draws the Wall object to the screen
    void Draw() override;

    void SetXRange(float minX, float maxX, const Vector2f& moveAmount);

    void SetYRange(float minY, float maxY, const Vector2f& moveAmount);

private:
    float mMinX;
    float mMaxX;
    Vector2f mMoveAmount;
    float mMinY;
    float mMaxY;


};

