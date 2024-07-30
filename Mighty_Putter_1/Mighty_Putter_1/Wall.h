#pragma once

#include <SDL.h>

#include "Vector.h"
#include "RigidBody.h"

// Wall class that inherits from RigidBody
class Wall : public RigidBody
{
public:
    // Constructor that initializes the Wall object with a given position and rotation
    Wall(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees = 0);

    // Update function that updates the Wall object's state based on input and time
    void Update(const InputState& input, double deltaTime) override;

    // Draw function that draws the Wall object to the screen
    void Draw() override;
};