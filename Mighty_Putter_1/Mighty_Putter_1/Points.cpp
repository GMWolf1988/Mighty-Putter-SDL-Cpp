#include "Points.h"

// Constructs a new point object with the given position and rotation.
Points::Points(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees)
    : RigidBody(pRenderer, "Content/Sprites/Points.png", position, rotationDegrees)
{
    InitStaticBox(mDrawRect->w, mDrawRect->h, 1.5f);
}

void Points::SetXPRange(float minXP, float maxXP, const Vector2f& moveAmountP)
{
    mMinXP = minXP;
    mMaxXP = maxXP;
    mMoveAmountP = moveAmountP;
}

void Points::SetYPRange(float minYP, float maxYP, const Vector2f& moveAmountP)
{
    mMinYP = minYP;
    mMaxYP = maxYP;
    mMoveAmountP = moveAmountP;
}

void Points::Update(const InputState& input, double deltaTime)
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

    // Update the position of the point
    mPosition += mMoveAmountP * deltaTime;

    UpdateVertices();

}
// Draws the Point object.
void Points::Draw()
{
    // Call base Draw function to draw the Point sprite.
    Object::Draw();
}