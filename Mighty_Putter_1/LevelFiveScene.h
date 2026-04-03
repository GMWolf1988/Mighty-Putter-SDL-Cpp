#pragma once
#include "Scene.h"
#include "Ball.h"
#include "Wall.h"
#include "Barrier.h"
#include "Hole.h"
#include "PowerUps.h"
#include "Points.h"
#include "MultiplyPoints.h"
#include "FastMo.h"
#include "SlowMo.h"

// Define a LevelThreeScene class that inherits from the Scene class
class LevelFiveScene : public Scene
{
public:
    // Inherit constructors from the parent Scene class
    using Scene::Scene;

    // Destructor for cleaning up dynamically allocated memory
    ~LevelFiveScene();

    // Override the Load function of the parent Scene class
    void Load() override;

    // Override the Update function of the parent Scene class
    // to take an InputState object and a delta time as arguments
    void Update(const InputState& input, double deltaTime) override;

    // Override the Draw function of the parent Scene class
    void Draw(double deltaTime) override;

private:
    // Pointers to the ball, walls, barriers, holes, and power-ups in the scene
    Ball* mBall;
    Wall** mWalls;
    Barrier** mBarrier;
    Hole** mHole;
    PowerUps** mPowerUps;
    Points** mPoints;
    MultiplyPoints** mMulti;
    FastMo** mFastMo;
    SlowMo** mSlowMo;

    // Counts of the number of walls, barriers, holes, and power-ups in the scene
    size_t mWallCount;
    size_t mBarrierCount;
    size_t mHoleCount;
    size_t mPowerUpCount;
    size_t mPointsCount;
    size_t mMultiCount;
    size_t mFastCount;
    size_t mSlowCount;

    // Rect for drawing static elements in the scene
    SDL_Rect mDrawRect;

    // Arrays for storing the positions and dimensions of floor rects
    Vector2* mFloorPositions;
    Vector2* mFloorDimensions;
    size_t mFloorCount;

    double mTimer = 0.0; // elapsed time since the start of the game

    bool mMultiBonusAppeared = false; // flag to keep track of whether the bonus has appeared or not
    bool isPowerUpUsed = false;

    bool mIsFastMotionActive = false;
    double mFastMotionTimer = 0.0;
    const double FAST_MOTION_DURATION = 4.0; // in seconds

    bool mIsSlowMotionActive = false;
    double mSlowMotionTimer = 0.0;
    const double SLOW_MOTION_DURATION = 4.0; // in seconds

};
