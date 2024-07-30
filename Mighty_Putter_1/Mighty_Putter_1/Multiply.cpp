#include "MultiplyPoints.h"

// Constructs a new multiply object with the given position and rotation.
MultiplyPoints::MultiplyPoints(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees)
    : RigidBody(pRenderer, "Content/Sprites/Score_Multi.png", position, rotationDegrees)
{
    InitStaticCircle(2.f, 1.5f);
}

void MultiplyPoints::SetXPRange(float minXP, float maxXP, const Vector2f& moveAmountP)
{
    mMinXP = minXP;
    mMaxXP = maxXP;
    mMoveAmountP = moveAmountP;
}

void MultiplyPoints::SetYPRange(float minYP, float maxYP, const Vector2f& moveAmountP)
{
    mMinYP = minYP;
    mMaxYP = maxYP;
    mMoveAmountP = moveAmountP;
}

void MultiplyPoints::Update(const InputState& input, double deltaTime)
{
    // Calculate the new position of the multiply
    Vector2f newPosP = mPosition + mMoveAmountP * deltaTime;

    // Check if the multiply has reached the end of the range, and invert the direction of movement if it has
    if (newPosP.x < mMinXP || newPosP.x > mMaxXP)
    {
        mMoveAmountP.x = -mMoveAmountP.x;
    }

    if (newPosP.y < mMinYP || newPosP.y > mMaxYP)
    {
        mMoveAmountP.y = -mMoveAmountP.y;
    }

    // Update the position of the multiply
    mPosition += mMoveAmountP * deltaTime;

    UpdateVertices();

}
// Draws the multiply object.
void MultiplyPoints::Draw()
{
    // Call base Draw function to draw the multiply sprite.
    Object::Draw();
}
