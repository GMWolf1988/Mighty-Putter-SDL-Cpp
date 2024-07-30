#pragma once

#include <string>
#include <SDL.h>

#include "Types.h"

// Define an Object class
class Object
{
public:
    // Destructor for cleaning up dynamically allocated memory
    ~Object();

    // Getter for the position of the object
    Vector2f GetPosition() const;

    // Setter for the position of the object
    void SetPosition(Vector2f position);

    // Move the object by a relative position vector
    void Move(Vector2f relativePosition);

    // Set the dimensions of the object
    void SetDimensions(Vector2 dimensions);

    // Set the rotation of the object in degrees
    void SetRotation(double angleDegrees);

    // Rotate the object by a specified angle in degrees
    void Rotate(double degrees);

    // Check if a given point is inside the object
    bool IsPointInside(Vector2f point) const;

    // Update function to be overridden by child classes
    virtual void Update(const InputState& input, double deltaTime) = 0;

    // Draw function to be overridden by child classes
    virtual void Draw();

    bool mEnabled{ true };

protected:
    // Constructor that takes a pointer to an SDL_Renderer object,
    // a path to the sprite texture file,
    // a Vector2f object representing the position of the object,
    // and an optional double representing the initial rotation of the object
    Object(SDL_Renderer* pRenderer, std::string spriteTexturePath, Vector2f position, double rotationDegrees);

    // Dependencies
    SDL_Renderer* mRenderer;

    // Drawing data
    Vector2 mTextureDimensions;
    SDL_Rect* mDrawRect;
    SDL_Texture* mSpriteTexture;

    // Spatial data
    Vector2f mPosition;
    double mRotationDegrees{ 0 };

    
};