#include "Scene.h"

// Constructor for Scene class
Scene::Scene(SDL_Renderer* pRenderer, SDL_Rect* pViewport, const int screenWidth, const int screenHeight)
    : mRenderer(pRenderer) // Initialize member variable mRenderer with given pointer
    , mViewport(pViewport) // Initialize member variable mViewport with given pointer
    , mScreenWidth(screenWidth) // Initialize member variable mScreenWidth with given value
    , mScreenHeight(screenHeight) // Initialize member variable mScreenHeight with given value
{
}

// Load the sound effect for when the ball hits a wall
void Scene::LoadWallSoundEffect()
{
    // Load the sound effect from a file
    mWallSoundEffect = Mix_LoadWAV("Content/Audio/Ball_Richochet.mp3");
}

// Play the sound effect for when the ball hits a wall
void Scene::PlayWallSoundEffect()
{
    if (areSoundEffectsEnabled && mWallSoundEffect != nullptr)
    {
        Mix_PlayChannel(-1, mWallSoundEffect, 0);
    }
}

void Scene::LoadPotSoundEffect()
{
    mBallPottedEffect = Mix_LoadWAV("Content/Audio/Ball_Potted.mp3");
}

void Scene::PlayPotSoundEffect()
{
    if (areSoundEffectsEnabled && mBallPottedEffect != nullptr)
    {
        Mix_PlayChannel(-1, mBallPottedEffect, 0);
    }
}

void Scene::LoadPointSoundEffect()
{
    mPointEffect = Mix_LoadWAV("Content/Audio/Points.mp3");
}

void Scene::PlayPointSoundEffect()
{
    if (areSoundEffectsEnabled && mPointEffect != nullptr)
    {
        Mix_PlayChannel(-1, mPointEffect, 0);
    }
}

void Scene::LoadMultiplySoundEffect()
{
    mMultiplyEffect = Mix_LoadWAV("Content/Audio/Incredible.mp3");
}

void Scene::PlayMultiplySoundEffect()
{
    if (areSoundEffectsEnabled && mMultiplyEffect != nullptr)
    {
        Mix_PlayChannel(-1, mMultiplyEffect, 0);
    }
}

void Scene::LoadPowerSoundEffect()
{
    mPowerUpEffect = Mix_LoadWAV("Content/Audio/Power.mp3");
}

void Scene::PlayPowerSoundEffect()
{
    if (areSoundEffectsEnabled && mPowerUpEffect != nullptr)
    {
        Mix_PlayChannel(-1, mPowerUpEffect, 0);
    }
}

void Scene::LoadGoSoundEffect()
{
    mGoEffect = Mix_LoadWAV("Content/Audio/Go.mp3");
}

void Scene::PlayGoSoundEffect()
{
    if (areSoundEffectsEnabled && mGoEffect != nullptr)
    {
        Mix_PlayChannel(-1, mGoEffect, 0);
    }
}

void Scene::LoadAmazingSoundEffect()
{
    mAmazingEffect = Mix_LoadWAV("Content/Audio/Amazing.mp3");
}

void Scene::PlayAmazingSoundEffect()
{
    if (areSoundEffectsEnabled && mAmazingEffect != nullptr)
    {
        Mix_PlayChannel(-1, mAmazingEffect, 0);
    }
}


// Update function for Scene class
void Scene::Update(const InputState& input, double deltaTime)
{
    mTime += deltaTime; // Increment member variable mTime by deltaTime
}

// Function to get the next scene to transition to
Scene* Scene::GetNextScene()
{
    return mNextScene; // Return pointer to member variable mNextScene
}