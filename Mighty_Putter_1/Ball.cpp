#include "Ball.h"
#include "Scalar.h"
#include "SDL_image.h"
#include "Texture.h"


// Ball class that inherits from RigidBody
Ball::Ball(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees)
    : RigidBody(pRenderer, "Content/Sprites/Ball.png", position, rotationDegrees)
{
    // Initialize circle properties for the Ball object
    InitCircle(12.f, 1.1f, 0.8f);

    // Load textures arrays
    mStaticAnimationTextures = (SDL_Texture**)malloc(mStaticAnimationFrameCount * sizeof(SDL_Texture*));
    mStaticAnimationTextures[0] = load_texture(mRenderer, "Content/Sprites/Ball.png");
    mStaticAnimationTextures[1] = load_texture(mRenderer, "Content/Sprites/Ball1.png");
    mStaticAnimationTextures[2] = load_texture(mRenderer, "Content/Sprites/Ball2.png");
    mStaticAnimationTextures[3] = load_texture(mRenderer, "Content/Sprites/Ball3.png");

    mCollisionAnimationTextures = (SDL_Texture**)malloc(mCollisionAnimationFrameCount * sizeof(SDL_Texture*));
    mCollisionAnimationTextures[0] = load_texture(mRenderer, "Content/Sprites/Ball.png");
    mCollisionAnimationTextures[1] = load_texture(mRenderer, "Content/Sprites/Ball4.png");
}

Ball::~Ball()
{
    for (size_t i = 0; i < mStaticAnimationFrameCount; ++i)
    {
        delete mStaticAnimationTextures[i];
    }

    for (size_t i = 0; i < mCollisionAnimationFrameCount; ++i)
    {
        delete mCollisionAnimationTextures[i];
    }
}

// Load the sound effect for when the ball hits a wall
void Ball::LoadBallSoundEffect()
{
    // Load the sound effect from a file
    mBallHitEffect = Mix_LoadWAV("Content/Audio/Ball_Hit.mp3");
}

// Play the sound effect for when the ball hits a wall
void Ball::PlayBallSoundEffect()
{
    if (areBallSoundEffectsEnabled)
    {
        // Play the wall hit sound effect
        Mix_PlayChannel(-1, mBallHitEffect, 0);
    }
}

// Update function that updates the Ball object's state based on input and time
void Ball::Update(const InputState& input, double deltaTime)
{
    // Load the sound effect for when the ball hits a wall
    LoadBallSoundEffect();
    // Check if left or right mouse button was pressed and the ball is not already moving
    if (input.mWasMouseLeftPressed && mForce == 0.f && IsPointInside(Vector2f(input.mCursorPosition)))
    {
        mInPuttingMode = true;
    }

    // Check if in putting mode and update the putting from vector
    if (mInPuttingMode)
    {
        mPuttingFromVector = Vector2f(input.mCursorPosition);
    }

    if (mMultiplierEnabled) 
    {
        mForceMultiplier = 1.5 * 60.f;
    }
    else
    {
        mForceMultiplier = 60.f;
    }

    if (input.mWasMouseLeftPressed && mForce == 0.f && IsPointInside(Vector2f(input.mCursorPosition)))
    {
        mInPuttingMode = true;
    }

    if (input.mWasMouseRightPressed && mForce == 0.f && IsPointInside(Vector2f(input.mCursorPosition)))
    {
        mInPuttingMode = true;
        mIsRightMouseButtonPressed = true;
    }

    // Check if in putting mode and update the putting from vector
    if (mInPuttingMode)
    {
        mPuttingFromVector = Vector2f(input.mCursorPosition);
    }

    if (mMultiplierEnabled)
    {
        mForceMultiplierR = 1.5 * 30.f;
    }
    else
    {
        mForceMultiplierR = 30.f;
    }

    // Check if left mouse button was released and the ball is not already moving
    if (input.mWasMouseLeftReleased && mForce == 0.f)
    {
        mInPuttingMode = false;
        mMultiplierEnabled = false; // Disable the multiplier for the next shot
        // Play the wall hit sound effect
        PlayBallSoundEffect();
        std::cout << "\nBall was Hit!..." << std:: endl;

        // Calculate force vector and direction based on the mouse position
        Vector2f forceVector = mPosition - mPuttingFromVector;
        Vector2f forceDirection = forceVector.Normalised();

        // TODO: find a better way of determining magnitude based on the vector drawn by the player
        // Calculate force magnitude and add the force to the ball
        float forceMagnitude = forceVector.Length() * mForceMultiplier;
        Vector2f force = forceDirection * forceMagnitude;
        AddForce(force);
    }

    // Check if right mouse button was released and the ball is not already moving
    if (input.mWasMouseRightReleased && mForce == 0.f)
    {
        mInPuttingMode = false;
        mMultiplierEnabled = false; // Disable the multiplier for the next shot
        // Play the wall hit sound effect
        PlayBallSoundEffect();
        std::cout << "\nBall was Hit!..." << std::endl;

        // Calculate force vector and direction based on the mouse position
        Vector2f forceVector = mPosition - mPuttingFromVector;
        Vector2f forceDirection = forceVector.Normalised();

        // TODO: find a better way of determining magnitude based on the vector drawn by the player
        // Calculate force magnitude and add the force to the ball
        float forceMagnitude = forceVector.Length() * mForceMultiplierR;
        Vector2f force = forceDirection * forceMagnitude;
        AddForce(force);

        mIsRightMouseButtonPressed = false;
    }

    if (!mInPuttingMode && mForce == 0.f)
    {
        mStaticAnimationDelay -= deltaTime;
    }
    else
    {
        mStaticAnimationDelay = mStaticAnimationDelayTime;
    }

    if (mCollisionAnimationTimer > 0.f)
    {
        mCollisionAnimationTimer -= deltaTime;
    }

    // Call base Update function to update the Ball object's physics simulation
    RigidBody::Update(input, deltaTime);
}

// Methods animates array

// Draw function that draws the Ball object to the screen
// check to see what state the ball is in. 
void Ball::Draw()
{
    if (mStaticAnimationDelay <= 0.f)
    {
        // It's been a while since the player interacted with the ball. Make it flash
        Uint32 ticks = SDL_GetTicks();
        Uint32 sprite = (ticks / mFrameTime) % mStaticAnimationFrameCount;

        // Calculate the top-left corner of the draw rectangle
        mDrawRect->x = mPosition.x - (mDrawRect->w / 2);
        mDrawRect->y = mPosition.y - (mDrawRect->h / 2);

        // Render the sprite with the given rotation angle at the object's position
        SDL_RenderCopyEx(mRenderer, mStaticAnimationTextures[sprite], NULL, mDrawRect, mRotationDegrees, NULL, SDL_FLIP_NONE);
    }
    else if (mCollisionAnimationTimer > 0.f)
    {
        // The ball collided with something
        Uint32 ticks = SDL_GetTicks();
        Uint32 sprite = (ticks / mFrameTime) % mCollisionAnimationFrameCount;

        // Calculate the top-left corner of the draw rectangle
        mDrawRect->x = mPosition.x - (mDrawRect->w / 2);
        mDrawRect->y = mPosition.y - (mDrawRect->h / 2);

        // Render the sprite with the given rotation angle at the object's position
        SDL_RenderCopyEx(mRenderer, mCollisionAnimationTextures[sprite], NULL, mDrawRect, mRotationDegrees, NULL, SDL_FLIP_NONE);
    }
    else
    {
        // No animation, just draw the white ball
        Object::Draw();
    }

    // If in putting mode, draw a red line indicating the force vector
    if (mInPuttingMode)
    {
        if (mIsRightMouseButtonPressed)
        {
            SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255); // Blue color
        }
        else
        {
            SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255); // Red color
        }
        SDL_RenderDrawLine(mRenderer, mPosition.x, mPosition.y, mPuttingFromVector.x, mPuttingFromVector.y);
    }
}

void Ball::CollisionDetected()
{
    mCollisionAnimationTimer = mCollisionAnimationTime;
}