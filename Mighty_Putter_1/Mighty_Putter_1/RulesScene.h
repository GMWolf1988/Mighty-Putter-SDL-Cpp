#pragma once
#include "Scene.h"

// Define a RulesScene class that inherits from the Scene class
class RulesScene : public Scene
{
public:
    // Inherit constructors from the parent Scene class
    using Scene::Scene;

    // Destructor for cleaning up dynamically allocated memory
    ~RulesScene();

    // Override the Load function of the parent Scene class
    void Load() override;

    // Override the Update function of the parent Scene class
    // to take an InputState object and a delta time as arguments
    void Update(const InputState& input, double deltaTime) override;

    // Override the Draw function of the parent Scene class
    void Draw(double deltaTime) override;

private:
    // Texture for the rules splash image
    SDL_Texture* mSplashTexture;

    // Rectangles for the rules splash image and scrolling squares
    SDL_Rect mSplashRect;
    SDL_Rect mSquareRect;

    // Timer for how long to display the rules splash image
    float mSceneTimer{ 10.0f };

    // Speed at which to scroll the squares
    float mScrollSpeed{ 30.0f };

    // Size of the scrolling squares
    int mSquareSize{ 20 };
};
