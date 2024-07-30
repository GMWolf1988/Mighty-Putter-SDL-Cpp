#include "RulesScene.h"
#include "LevelOneScene.h"
#include "Texture.h"

RulesScene::~RulesScene()
{
    // Destroy the splash texture
    SDL_DestroyTexture(mSplashTexture);
    mSplashTexture = NULL;
}

void RulesScene::Load()
{
    // Get the texture size and calculate the rectangle for the splash image
    mSplashTexture = load_texture(mRenderer, "Content/Sprites/Rules.png");
    SDL_Point textureSize = get_texture_size(mSplashTexture);
    mSplashRect.x = (mScreenWidth - textureSize.x) / 2;
    mSplashRect.y = (mScreenHeight - textureSize.y) / 2;
    mSplashRect.w = textureSize.x;
    mSplashRect.h = textureSize.y;
}

void RulesScene::Update(const InputState& input, double deltaTime)
{
    // Call base Update
    Scene::Update(input, deltaTime);

    // Tick down the timer
    mSceneTimer -= (float)deltaTime;

    // When it ends, prepare the next scene (but don't load it yet - the main loop will handle that)
    if (mSceneTimer <= 0.0f)
        mNextScene = new LevelOneScene(mRenderer, mViewport, mScreenWidth, mScreenHeight);
}

void RulesScene::Draw(double deltaTime)
{
    // Clear to red
    SDL_SetRenderDrawColor(mRenderer, 196, 0, 72, 255);
    SDL_RenderClear(mRenderer);

    // Draw background
    for (int y = -mScreenHeight; y < mScreenHeight; y += mSquareSize)
    {
        for (int x = -mScreenWidth; x < mScreenWidth; x += mSquareSize)
        {
            mSquareRect.x = x + (int)(mScrollSpeed * mTime) % 500;
            mSquareRect.y = y + (int)(mScrollSpeed * mTime) % 500;
            mSquareRect.w = mSquareSize;
            mSquareRect.h = mSquareSize;

            if ((x / mSquareSize + y / mSquareSize) % 2 == 0)
            {
                SDL_SetRenderDrawColor(mRenderer, 64, 219, 131, 255); // Light green
            }
            else
            {
                SDL_SetRenderDrawColor(mRenderer, 54, 184, 110, 255); // Darker green
            }
            SDL_RenderFillRect(mRenderer, &mSquareRect);
        }
    }

    // Draw splash image
    SDL_RenderCopy(mRenderer, mSplashTexture, NULL, &mSplashRect);
}
