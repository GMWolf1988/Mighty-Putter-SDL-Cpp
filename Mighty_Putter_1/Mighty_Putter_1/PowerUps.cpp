#include "PowerUps.h"

// Constructs a new power-up object with the given position and rotation.
PowerUps::PowerUps(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees)
    : RigidBody(pRenderer, "Content/Sprites/Power.png", position, rotationDegrees)
{
    InitStaticBox(mDrawRect->w, mDrawRect->h, 1.5f);
}

void PowerUps::SetXPRange(float minXP, float maxXP, const Vector2f& moveAmountP)
{
    mMinXP = minXP;
    mMaxXP = maxXP;
    mMoveAmountP = moveAmountP;
}

void PowerUps::SetYPRange(float minYP, float maxYP, const Vector2f& moveAmountP)
{
    mMinYP = minYP;
    mMaxYP = maxYP;
    mMoveAmountP = moveAmountP;
}

void PowerUps::Update(const InputState& input, double deltaTime)
{
    // Calculate the new position of the power-up
    Vector2f newPosP = mPosition + mMoveAmountP * deltaTime;

    // Check if the power-up has reached the end of the range, and invert the direction of movement if it has
    if (newPosP.x < mMinXP || newPosP.x > mMaxXP)
    {
        mMoveAmountP.x = -mMoveAmountP.x;
    }

    if (newPosP.y < mMinYP || newPosP.y > mMaxYP)
    {
        mMoveAmountP.y = -mMoveAmountP.y;
    }

    // Update the position of the power-up
    mPosition += mMoveAmountP * deltaTime;

    UpdateVertices();
  
}
// Draws the wall object.
void PowerUps::Draw()
{
    // Call base Draw function to draw the barrier sprite.
    Object::Draw();
}