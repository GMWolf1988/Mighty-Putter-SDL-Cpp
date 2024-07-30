#include "Hole.h"

// Constructs a new barrier object with the given position and rotation.
Hole::Hole(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees)
    : RigidBody(pRenderer, "Content/Sprites/Hole.png", position, rotationDegrees)
{
    // Initializes the rigid body with a static circle shape.
    InitStaticCircle(0.1f, 0.1f);
}

// Updates the barrier object's state based on the given input and elapsed time.
void Hole::Update(const InputState& input, double deltaTime)
{
    // Do nothing for a static object.
}

// Draws the wall object.
void Hole::Draw()
{
    // Call base Draw function to draw the barrier sprite.
    Object::Draw();
}