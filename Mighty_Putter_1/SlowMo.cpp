#include "SlowMo.h"

// Constructs a new barrier object with the given position and rotation.
SlowMo::SlowMo(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees)
    : RigidBody(pRenderer, "Content/Sprites/Slow_Mo.png", position, rotationDegrees)
{
    InitStaticBox(mDrawRect->w, mDrawRect->h, 1.5f);
}

void SlowMo::SetXRange(float minX, float maxX, const Vector2f& moveAmount)
{
    mMinX = minX;
    mMaxX = maxX;
    mMoveAmount = moveAmount;
}

void SlowMo::SetYRange(float minY, float maxY, const Vector2f& moveAmount)
{
    mMinY = minY;
    mMaxY = maxY;
    mMoveAmount = moveAmount;
}

void SlowMo::Update(const InputState& input, double deltaTime)
{
    // Calculate the new position of the barrier
    Vector2f newPos = mPosition + mMoveAmount * deltaTime;

    // Check if the barrier has reached the end of the range, and invert the direction of movement if it has
    if (newPos.x < mMinX || newPos.x > mMaxX)
    {
        mMoveAmount.x = -mMoveAmount.x;
    }

    if (newPos.y < mMinY || newPos.y > mMaxY)
    {
        mMoveAmount.y = -mMoveAmount.y;
    }

    // Update the position of the barrier
    mPosition += mMoveAmount * deltaTime;

    UpdateVertices();
}
// Draws the wall object.
void SlowMo::Draw()
{
    // Call base Draw function to draw the barrier sprite.
    Object::Draw();
}