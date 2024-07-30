#include "Barrier.h"

// Constructs a new barrier object with the given position and rotation.
Barrier::Barrier(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees)
    : RigidBody(pRenderer, "Content/Sprites/Barrier.png", position, rotationDegrees)
{
    InitStaticBox(mDrawRect->w, mDrawRect->h, 1.5f);
}

void Barrier::SetXRange(float minX, float maxX, const Vector2f& moveAmount)
{
    mMinX = minX;
    mMaxX = maxX;
    mMoveAmount = moveAmount;
}

void Barrier::SetYRange(float minY, float maxY, const Vector2f& moveAmount)
{
    mMinY = minY;
    mMaxY = maxY;
    mMoveAmount = moveAmount;
}

void Barrier::Update(const InputState& input, double deltaTime)
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
void Barrier::Draw()
{
    // Call base Draw function to draw the barrier sprite.
    Object::Draw();
}