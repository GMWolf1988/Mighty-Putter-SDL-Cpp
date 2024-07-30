#include "Wall.h"

// Constructs a new wall object with the given position and rotation.
Wall::Wall(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees)
    : RigidBody(pRenderer, "Content/Sprites/Wall.png", position, rotationDegrees)
{
    // Initializes the rigid body with a static box shape.
    InitStaticBox(mDrawRect->w, mDrawRect->h, 1.5f);
}

// Updates the wall object's state based on the given input and elapsed time.
void Wall::Update(const InputState& input, double deltaTime)
{
    // Do nothing for a static object.
}

// Draws the wall object.
void Wall::Draw()
{
    // Call base Draw function to draw the wall sprite.
    Object::Draw();
}