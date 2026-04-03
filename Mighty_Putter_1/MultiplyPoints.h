#pragma once

#include <SDL.h>
#include "Vector.h"
#include "RigidBody.h"

// Define a multiply class that inherits from the rigidbody class
class MultiplyPoints : public RigidBody
{
public:
    // Constructor that initializes the multiply object with a given position and rotation
    MultiplyPoints(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees = 0);

    // Update function that updates the multiply object's state based on input and time
    void Update(const InputState& input, double deltaTime) override;

    // Draw function that draws the multiply object to the screen
    void Draw() override;

    void SetXPRange(float minXP, float maxXP, const Vector2f& moveAmountP);

    void SetYPRange(float minYP, float maxYP, const Vector2f& moveAmountP);

private:
    float mMinXP;
    float mMaxXP;
    Vector2f mMoveAmountP;
    float mMinYP;
    float mMaxYP;
};
