#pragma once

#include <SDL.h>

#include "Vector.h"
#include "RigidBody.h"

// Define a Hole class that inherits from the Object class
class Hole : public RigidBody
{
public:
    // Constructor that initializes the hole object with a given position and rotation
    Hole(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees = 0);

    // Update function that updates the hole object's state based on input and time
    void Update(const InputState& input, double deltaTime) override;

    // Draw function that draws the hole object to the screen
    void Draw() override;
};