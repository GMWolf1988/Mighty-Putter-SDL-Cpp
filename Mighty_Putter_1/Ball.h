#pragma once

#include <SDL.h>
#include "Vector.h"
#include "RigidBody.h"
#include <SDL_mixer.h>
#include <iostream>
#include <string>


// Declare extern variable for ball sound effects
extern bool areBallSoundEffectsEnabled;
// Define a Ball class that inherits from the RigidBody class
class Ball : public RigidBody
{
public:
    // Constructor that takes a pointer to an SDL_Renderer object,
    // a Vector2f object representing the position of the ball,
    // and an optional double representing the initial rotation of the ball
    Ball(SDL_Renderer* pRenderer, Vector2f position, double rotationDegrees = 0);
    ~Ball();

    //array for texture within private. 
    // bool for animation at any given time (indicating)
    //float for collision timer

    // Override the Update function of the parent RigidBody class
    // to take an InputState object and a delta time as arguments
    void Update(const InputState& input, double deltaTime) override;

    // Override the Draw function of the parent RigidBody class
    void Draw() override;

    void CollisionDetected();

    // Boolean to enable the power-up
    bool mMultiplierEnabled{ false };

private:

    // Private member variable to track whether the ball is in putting mode
    bool mInPuttingMode{ false };

    // Private member variable to store the direction the ball is being putted from
    Vector2f mPuttingFromVector;

    // Private member variable to store a force multiplier used to calculate the force applied
    // to the ball when it is putted
    float mForceMultiplier{ 60.f };
    float mForceMultiplierR{ 30.f };

    bool mIsRightMouseButtonPressed = false;

    // Animated sprites
    SDL_Texture** mStaticAnimationTextures;
    int mStaticAnimationFrameCount{4};
    float mStaticAnimationDelay{3.f};
    float mStaticAnimationDelayTime{3.f};

    SDL_Texture** mCollisionAnimationTextures;
    int mCollisionAnimationFrameCount{2};
    float mCollisionAnimationTimer{0.f};
    float mCollisionAnimationTime{1.f};

    int mFrameTime{100};

    Mix_Chunk* mBallHitEffect{ nullptr }; // Pointer to the sound effect for when the ball is hit by player
    // Load the sound effect for when the ball is hit
    void LoadBallSoundEffect();
    // Play the sound effect for when the ball is hit
    void PlayBallSoundEffect();



};