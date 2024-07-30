#include "Object.h"
#include "Texture.h"

// Constructor for the Object class
Object::Object(SDL_Renderer* pRenderer, std::string spriteTexturePath, Vector2f position, double rotationDegrees)
    : mRenderer(pRenderer) // Initialize mRenderer member variable with the passed-in SDL_Renderer pointer
    , mSpriteTexture(load_texture(pRenderer, spriteTexturePath)) // Load texture using the passed-in renderer and texture path, and initialize mSpriteTexture member variable
    , mPosition(position) // Initialize mPosition member variable with the passed-in position vector
    , mRotationDegrees(rotationDegrees) // Initialize mRotationDegrees member variable with the passed-in rotation angle
{
    // Get the size of the loaded texture
    SDL_Point textureSize = get_texture_size(mSpriteTexture);

    // Create a new SDL_Rect to represent the object's position and dimensions
    mDrawRect = new SDL_Rect;
    mDrawRect->w = textureSize.x; // Set the width of the rectangle to the width of the loaded texture
    mDrawRect->h = textureSize.y; // Set the height of the rectangle to the height of the loaded texture
}

// Destructor for the Object class
Object::~Object()
{
    SDL_DestroyTexture(mSpriteTexture); // Destroy the object's texture
    mSpriteTexture = NULL; // Set the texture pointer to NULL
    delete mDrawRect; // Delete the object's SDL_Rect
}

// Getter for the object's position
Vector2f Object::GetPosition() const
{
    return mPosition; // Return the object's position vector
}

// Setter for the object's position
void Object::SetPosition(Vector2f position)
{
    mPosition = position; // Set the object's position vector to the passed-in vector
}

// Method to move the object by a relative amount
void Object::Move(Vector2f relativePosition)
{
    mPosition += relativePosition; // Add the passed-in vector to the object's position vector
}

void Object::SetDimensions(Vector2 dimensions)
{
    // Update width and height of the draw rectangle
    mDrawRect->w = dimensions.x;
    mDrawRect->h = dimensions.y;
}

void Object::SetRotation(double angleDegrees)
{
    // Set the rotation angle in degrees
    mRotationDegrees = angleDegrees;
}

void Object::Rotate(double degrees)
{
    // Add to the existing rotation angle
    mRotationDegrees += degrees;
}

bool Object::IsPointInside(Vector2f point) const
{
    // Calculate the bottom-left corner of the object
    float fromX = mPosition.x - (mDrawRect->w / 2);
    float fromY = mPosition.y - (mDrawRect->h / 2);

    // Check if the point is inside the object's bounds
    return (point.x >= fromX
        && point.x <= fromX + mDrawRect->w
        && point.y >= fromY
        && point.y <= fromY + mDrawRect->h);
}

void Object::Draw()
{

    // Return early if the object is disabled
    if (!mEnabled) 
    {
        return;
    }
    // Calculate the top-left corner of the draw rectangle
    mDrawRect->x = mPosition.x - (mDrawRect->w / 2);
    mDrawRect->y = mPosition.y - (mDrawRect->h / 2);

    // Render the sprite with the given rotation angle at the object's position
    SDL_RenderCopyEx(mRenderer, mSpriteTexture, NULL, mDrawRect, mRotationDegrees, NULL, SDL_FLIP_NONE);
}