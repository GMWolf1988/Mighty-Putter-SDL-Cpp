#pragma once
#include <SDL.h>
#include "Vector.h"
#include "RigidBody.h"

// Define a PowerUps class that inherits from the rigidbody class
class PowerUps : public RigidBody
{
public:
    // Constructor that initializes the ball object with a given position and rotation
    PowerUps(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees = 0);

    // Update function that updates the Wall object's state based on input and time
    void Update(const InputState& input, double deltaTime) override;

    // Draw function that draws the Wall object to the screen
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