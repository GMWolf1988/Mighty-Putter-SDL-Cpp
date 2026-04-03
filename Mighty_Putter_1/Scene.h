#pragma once
#include <SDL.h>
#include "Types.h"
#include <iostream>
#include <SDL_mixer.h>

// Declare extern variable for ball sound effects
extern bool areSoundEffectsEnabled;

/**
 * Scene is an abstract class encapsulating data and logic for a single screen or scene in the game.
 * There should be one concrete implementation of Scene for each distinct scene (such as a level).
 */
class Scene
{
public:
    /**
     * Scene's constructor should only perform member initialisation. Asset loading should be done
     * via the Load method.
     */
    Scene(SDL_Renderer* pRenderer, SDL_Rect* pViewport, const int screenWidth, const int screenHeight);

    /**
     * Load is called once per scene before its first update.
     */
    virtual void Load() = 0;

    /**
     * Update is called once per frame before drawing.
     */
    virtual void Update(const InputState& input, double deltaTime);

    /**
     * Draw is called once per frame after scene state is updated.
     */
    virtual void Draw(double deltaTime) = 0;

    /**
     * GetNextScene returns the next scene, if any. Should only be set in Update when the scene
     * needs to be swapped to a different one.
     */
    Scene* GetNextScene();

    // Define protected member variables for the Scene class
protected:
    SDL_Renderer* mRenderer; // Pointer to the SDL_Renderer object for rendering the scene
    SDL_Rect* mViewport; // Pointer to the SDL_Rect object representing the viewport of the scene

    const int mScreenWidth; // The width of the screen
    const int mScreenHeight; // The height of the screen

    float mTime{ 0.0f }; // Time since the scene's first update

    Scene* mNextScene{ nullptr }; // Pointer to the next scene, if any

    Mix_Chunk* mWallSoundEffect{ nullptr }; // Pointer to the sound effect for when the ball hits a wall
    Mix_Chunk* mBallHitEffect{ nullptr }; // Pointer to the sound effect for when the ball is hit by player
    Mix_Chunk* mBallPottedEffect{ nullptr }; // Pointer to the sound effect for when the ball has been potted
    Mix_Chunk* mPointEffect{ nullptr };
    Mix_Chunk* mMultiplyEffect{ nullptr };
    Mix_Chunk* mPowerUpEffect{ nullptr };
    Mix_Chunk* mGoEffect{ nullptr };
    Mix_Chunk* mAmazingEffect{ nullptr };


    // Load the sound effect for when the ball hits a wall
    void LoadWallSoundEffect();
    // Play the sound effect for when the ball hits a wall
    void PlayWallSoundEffect();
    // Load the sound effect for when the ball is hit
    void LoadBallSoundEffect();
    // Play the sound effect for when the ball is hit
    void PlayBallSoundEffect();
    // Load and play Pot sound
    void LoadPotSoundEffect();
    void PlayPotSoundEffect();
    // Load and play point sounds
    void LoadPointSoundEffect();
    void PlayPointSoundEffect();
    // Load and multiply point sounds
    void LoadMultiplySoundEffect();
    void PlayMultiplySoundEffect();
    // Load and multiply point sounds
    void LoadPowerSoundEffect();
    void PlayPowerSoundEffect();
    // Load go sounds
    void LoadGoSoundEffect();
    void PlayGoSoundEffect();

    void LoadAmazingSoundEffect();
    void PlayAmazingSoundEffect();
};

