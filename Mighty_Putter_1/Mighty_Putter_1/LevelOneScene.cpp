#include "LevelOneScene.h"
#include "LevelTwoScene.h"
#include "Texture.h"
#include "Collision.h"
#include "Ball.h"

void UpdateScore(int points, const std::string& operation);

LevelOneScene::~LevelOneScene()
{
    // Delete dynamically allocated objects
    delete mBall;
    delete mMulti;

    for (size_t i = 0; i < mWallCount; ++i)
    {
        delete mWalls[i];
    }

    for (size_t i = 0; i < mBarrierCount; ++i)
    {
        delete mBarrier[i];
    }

    for (size_t i = 0; i < mHoleCount; ++i)
    {
        delete mHole[i];
    }

    for (size_t i = 0; i < mPowerUpCount; ++i)
    {
        delete mPowerUps[i];
    }

    for (size_t i = 0; i < mPointsCount; ++i)
    {
        delete mPoints[i];
    }

   /* for (size_t i = 0; i < mMultiCount; ++i)
    {
        delete mMulti[i];
    }*/

    for (size_t i = 0; i < mFastCount; ++i)
    {
        delete mFastMo[i];
    }

    for (size_t i = 0; i < mSlowCount; ++i)
    {
        delete mSlowMo[i];
    }

}

void LevelOneScene::Load()
{

    // Print loading messages to console
    std::cout << "\n\033[33mLevel One has Loaded!...\033[0m" << std::endl;
    std::cout << "\033[36mAll Sprites have loaded..\033[0m" << std::endl;
    std::cout << "\n\033[33m\nTimer of 45s started!...\033[0m" << std::endl;

    // Load the sound effects
    LoadWallSoundEffect();
    LoadPointSoundEffect();
    LoadPotSoundEffect();
    LoadMultiplySoundEffect();
    LoadPowerSoundEffect();
    LoadGoSoundEffect();
    PlayGoSoundEffect();
    LoadAmazingSoundEffect();

    // Create a ball and place it at the start of the course
    mBall = new Ball(mRenderer, { 200, 514 });
    mMulti = new MultiplyPoints(mRenderer, { 400, 278 });

    // Sets the variable m[]Count to 1. Then, it calls the malloc() function to allocate a block of memory of size m[]Count * sizeof([]*), 
    // where sizeof([]*) is the size of a pointer to a PowerUps

    // Create wall pieces
    mWallCount = 8;
    mWalls = (Wall**)malloc(mWallCount * sizeof(Wall*));
    mWalls[0] = new Wall(mRenderer, { 84.f, 350.f }, 90);
    mWalls[0]->SetDimensions({ 500, 32 });
    mWalls[1] = new Wall(mRenderer, { 400.f, 84.f });
    mWalls[1]->SetDimensions({ 664, 32 });
    mWalls[2] = new Wall(mRenderer, { 716.f, 350.f }, 90);
    mWalls[2]->SetDimensions({ 500, 32 });
    mWalls[3] = new Wall(mRenderer, { 600.f, 584.f });
    mWalls[3]->SetDimensions({ 200, 32 });
    mWalls[4] = new Wall(mRenderer, { 484.f, 450.f }, 90);
    mWalls[4]->SetDimensions({ 300, 32 });
    mWalls[5] = new Wall(mRenderer, { 400.f, 316.f });
    mWalls[5]->SetDimensions({ 138, 32 });
    mWalls[6] = new Wall(mRenderer, { 316.f, 450.f }, 90);
    mWalls[6]->SetDimensions({ 300, 32 });
    mWalls[7] = new Wall(mRenderer, { 200.f, 584.f });
    mWalls[7]->SetDimensions({ 200, 32 });

    // Set up floor piece arrays
    mFloorCount = 4;
    mFloorPositions = (Vector2*)malloc(mFloorCount * sizeof(Vector2));
    mFloorDimensions = (Vector2*)malloc(mFloorCount * sizeof(Vector2));
    mFloorPositions[0] = { 100, 300 };
    mFloorDimensions[0] = { 200, 300 };
    mFloorPositions[1] = { 100, 100 };
    mFloorDimensions[1] = { 300, 200 };
    mFloorPositions[2] = { 400, 100 };
    mFloorDimensions[2] = { 300, 200 };
    mFloorPositions[3] = { 500, 300 };
    mFloorDimensions[3] = { 200, 300 };

    // Create barriers
    mBarrierCount = 3;
    mBarrier = (Barrier**)malloc(mBarrierCount * sizeof(Barrier*));
    mBarrier[0] = new Barrier(mRenderer, { 115, 400 });
    mBarrier[0]->SetDimensions({ 25, 25 });
    mBarrier[0]->SetXRange(115.f, 275.f, { 200.f, 0.0f });
    mBarrier[1] = new Barrier(mRenderer, { 530, 400 });
    mBarrier[1]->SetDimensions({ 25, 25 });
    mBarrier[1]->SetXRange(530.f, 670.f, { 200.0f, 0.0f });
    mBarrier[2] = new Barrier(mRenderer, { 400, 120 });
    mBarrier[2]->SetDimensions({ 25, 25 });
    mBarrier[2]->SetYRange(120.f, 279.f, { 0.0f, 200.f });


    // PowerUp setup
    mPowerUpCount = 1;
    mPowerUps = (PowerUps**)malloc(mPowerUpCount * sizeof(PowerUps*));
    mPowerUps[0] = new PowerUps(mRenderer, { 550, 250 });
    mPowerUps[0]->SetDimensions({ 30, 30 });
    mPowerUps[0]->SetXPRange(550.f, 600.f, { 90.0f, 0.0f });

    // Points set up
    mPointsCount = 3;
    mPoints = (Points**)malloc(mPointsCount * sizeof(Points*));
    mPoints[0] = new Points(mRenderer, { 120, 350 });
    mPoints[0]->SetDimensions({ 30,30 });
    mPoints[0]->SetXPRange( 120.f, 275.f, {120.f ,0.f});
    mPoints[1] = new Points(mRenderer, { 530, 480 });
    mPoints[1]->SetDimensions({ 30,30 });
    mPoints[1]->SetXPRange(530.f, 670.f,{ 95.f ,0.f });
    mPoints[2] = new Points(mRenderer, { 400, 120 });
    mPoints[2]->SetDimensions({ 30,30 });

    //// Multiply set up
    //mMultiCount = 1;
    //mMulti = (MultiplyPoints**)malloc(mPointsCount * sizeof(MultiplyPoints*));
    //mMulti[0] = new MultiplyPoints(mRenderer, { 400, 278 });
    //mMulti[0]->SetDimensions({ 30,30 });

    // FastMo set up
    mFastCount = 1;
    mFastMo = (FastMo**)malloc(mFastCount * sizeof(FastMo*));
    mFastMo[0] = new FastMo(mRenderer, { 200, 150 });
    mFastMo[0]->SetDimensions({ 30,30 });
    mFastMo[0]->SetYRange(150.f, 200.f, { 0.f ,95.f });

    // SlowMo set up
    mSlowCount = 1;
    mSlowMo = (SlowMo**)malloc(mSlowCount * sizeof(SlowMo*));
    mSlowMo[0] = new SlowMo(mRenderer, { 200, 450 });
    mSlowMo[0]->SetDimensions({ 30,30 });

    // Create hole
    mHoleCount = 1;
    mHole = (Hole**)malloc(mHoleCount * sizeof(Hole*));
    mHole[0] = new Hole(mRenderer, { 600, 540 });
}

void LevelOneScene::Update(const InputState& input, double deltaTime)
{
    // Call base Update
    Scene::Update(input, deltaTime);

    mBall->Update(input, deltaTime);

    mMulti->Update(input, deltaTime);

    mTimer += deltaTime;

    //Update the Power-Up
    for (size_t i = 0; i < mPowerUpCount; i++)
    {
        mPowerUps[i]->Update(input, deltaTime);
    }

    //Update the Points
    for (size_t i = 0; i < mPointsCount; i++)
    {
        mPoints[i]->Update(input, deltaTime);
    }

    //Update the FastMo
    for (size_t i = 0; i < mFastCount; i++)
    {
        mFastMo[i]->Update(input, deltaTime);
    }

    //Update the SlowMo
    for (size_t i = 0; i < mSlowCount; i++)
    {
        mSlowMo[i]->Update(input, deltaTime);
    }

    // Check for collisions
   // Define a Vector2f variable called "normal"
    Vector2f normal;

    // Define a float variable called "depth"
    float depth;

    // Start a for loop that iterates over the number of walls in the scene
    for (size_t i = 0; i < mWallCount; ++i)
    {
        // Get a pointer to the ith wall in the scene
        Wall* pWall = mWalls[i];

        // Check if the ball is intersecting with the current wall
        // If it is, the normal and depth values will be updated accordingly
        if (pWall->DoesBodyIntersect(*mBall, normal, depth))
        {
            // Move the ball out of the wall by the depth amount along the normal vector
            mBall->Move(-normal * depth);
            mBall->CollisionDetected();

            // Play the wall hit sound effect
            PlayWallSoundEffect();
            std::cout << "\nWall hit by Ball!..." << std::endl;

            // Resolve the collision between the ball and the wall
            ResolveCollision(*mBall, *pWall, normal, depth);

        }
    }

    // Start a for loop that iterates over the number of barriers in the scene
    for (size_t i = 0; i < mBarrierCount; ++i)
    {

        // Get a pointer to the ith wall in the scene
        Barrier* pBarrier = mBarrier[i];

        if (mIsFastMotionActive)
        {
            // Speed up barriers if fast-motion effect is active
            mBarrier[i]->Update(input, deltaTime * 2);

            if (pBarrier->DoesBodyIntersect(*mMulti, normal, depth))
            {
                mMulti->mEnabled = false;
            }
        }
        else if (mIsSlowMotionActive)
        {
            // Slows down barriers if slow-motion effect is active
            mBarrier[i]->Update(input, deltaTime * 0.1);
        }
        else
        {
            mBarrier[i]->Update(input, deltaTime);
        }

        if (pBarrier->DoesBodyIntersect(*mBall, normal, depth))
        {
            // Move the ball out of the barrier by the depth amount along the normal vector
            mBall->Move(-normal * depth);
            mBall->CollisionDetected();

            // Play the wall hit sound effect
            PlayWallSoundEffect();
            std::cout << "\nBarrier hit by Ball!..." << std::endl;

            // Resolve the collision between the ball and the wall
            ResolveCollision(*mBall, *pBarrier, normal, depth);
        }        
         
    }

    if (mIsFastMotionActive)
    {
        mFastMotionTimer -= deltaTime;
        if (mFastMotionTimer <= 0.0)
        {
            mIsFastMotionActive = false;
        }
    }

    if (mIsSlowMotionActive)
    {
        mSlowMotionTimer -= deltaTime;
        if (mSlowMotionTimer <= 0.0)
        {
            mIsSlowMotionActive = false;
        }
    }

    // Start a for loop that iterates over the number of holes in the scene
    for (size_t i = 0; i < mHoleCount; ++i)
    {
        // Get a pointer to the ith hole in the scene
        Hole* pHole = mHole[i];
        if (pHole->DoesBodyIntersect(*mBall, normal, depth))
        {
            // Play the wall hit sound effect
            PlayPotSoundEffect();
            std::cout << "\nBall has been Potted!..." << std::endl;
            UpdateScore(5, "add");

            mNextScene = new LevelTwoScene(mRenderer, mViewport, mScreenWidth, mScreenHeight);
        }
    }

    // Start a for loop that iterates over the number of power-ups in the scene
    for (size_t i = 0; i < mPowerUpCount; ++i)
    {
        // Get a pointer to the ith power-up in the scene
        PowerUps* pPowerUps = mPowerUps[i];

        // Check if the ball is intersecting with the current power-up
        // If it is, the normal and depth values will be updated accordingly
        if (pPowerUps->DoesBodyIntersect(*mBall, normal, depth))
        {
            // Play the power-up collection sound effect
            PlayPowerSoundEffect();
            std::cout << "\nPower Shot Collected!..." << std::endl;
            std::cout << "\033[35mYour next shot will be double the Power!...\033[0m" << std::endl;

            mBall->mMultiplierEnabled = true;

            // Delete the power-up from the scene and free its memory
            delete pPowerUps;
            mPowerUps[i] = nullptr;

            // Shift the remaining power-ups in the array to remove the empty slot
            for (size_t j = i + 1; j < mPowerUpCount; ++j)
            {
                mPowerUps[j - 1] = mPowerUps[j];
            }

            // Decrement the count of power-ups in the scene
            mPowerUpCount--;

            // Break out of the loop since we found a collision and deleted a power-up
            break;
        }
    }

    // Start a for loop that iterates over the number of points in the scene
    for (size_t i = 0; i < mPointsCount; ++i)
    {
        // Get a pointer to the ith points in the scene
        Points* pPoints = mPoints[i];

        // Check if the ball is intersecting with the current point speite
        // If it is, the normal and depth values will be updated accordingly
        if (pPoints->DoesBodyIntersect(*mBall, normal, depth))
        {

            // Play the point collection sound effect
            PlayPointSoundEffect();
            std::cout << "\n2 Points Collected!..." << std::endl;
            UpdateScore(2, "add");

            // Delete the points from the scene and free its memory
          //  delete pPoints;
            mPoints[i] = nullptr;

            // Shift the remaining points in the array to remove the empty slot
            for (size_t a = i + 1; a < mPointsCount; ++a)
            {
                mPoints[a - 1] = mPoints[a];
            }

            // Decrement the count of points in the scene
            mPointsCount--;

            // Break out of the loop since we found a collision and deleted a points
            break;
        }
    }

    if (mMulti->DoesBodyIntersect(*mBall, normal, depth) && !multiplierCollected)
    {
        // Play the power-up collection sound effect
        PlayMultiplySoundEffect();
        std::cout << "\nx10 Multiplier Collect!..." << std::endl;
        // Update the score and store the updated score in the variable
        UpdateScore(10, "multiply");

        mMulti->mEnabled = false;

        multiplierCollected = true;
    }

    //// Start a for loop that iterates over the number of multiply in the scene
    //for (size_t i = 0; i < mMultiCount; ++i)
    //{
    //    // Get a pointer to the ith multiply in the scene
    //    MultiplyPoints* pMultiply = mMulti[i];

    //    // Check if the ball is intersecting with the current power-up
    //    // If it is, the normal and depth values will be updated accordingly
    //    if (pMultiply->DoesBodyIntersect(*mBall, normal, depth))
    //    {
    //        // Move the ball out of the power-up by the depth amount along the normal vector
    //        mBall->Move(-normal * depth);

    //        // Play the power-up collection sound effect
    //        PlayMultiplySoundEffect();
    //        std::cout << "\nx10 Multiplier Collect!..." << std::endl;
    //        // Update the score and store the updated score in the variable
    //        UpdateScore(10, "multiply");
    //        // Resolve the collision between the ball and the multiply
    //        ResolveCollision(*mBall, *pMultiply, normal, depth);

    //        // Delete the multiply from the scene and free its memory
    //        delete pMultiply;
    //        mMulti[i] = nullptr;

    //        // Shift the remaining multiply in the array to remove the empty slot
    //        for (size_t j = i + 1; j < mMultiCount; ++j)
    //        {
    //            mMulti[j - 1] = mMulti[j];
    //        }

    //        // Decrement the count of multiply in the scene
    //        mMultiCount--;

    //        // Break out of the loop since we found a collision and deleted a multiply
    //        break;
    //    }
    //}

    for (size_t i = 0; i < mFastCount; ++i)
    {
        // Get a pointer to the ith fastmo in the scene
        FastMo* pFastMo = mFastMo[i];

        // Check if the ball is intersecting with the current fast-mo
        // If it is, the normal and depth values will be updated accordingly
        if (pFastMo->DoesBodyIntersect(*mBall, normal, depth))
        {
            // Play the slow-mo collection sound effect
            PlayPowerSoundEffect();
            std::cout << "\nFast-Mo, Collected!..." << std::endl;
            std::cout << "Barriers speeding up for 4 seconds!..." << std::endl;

            // Enable fast-motion effect
            mIsFastMotionActive = true;
            mFastMotionTimer = FAST_MOTION_DURATION;

            // Delete the slow-mo from the scene and free its memory
            delete pFastMo;
            mFastMo[i] = nullptr;

            // Shift the remaining slow-mo in the array to remove the empty slot
            for (size_t j = i + 1; j < mFastCount; ++j)
            {
                mFastMo[j - 1] = mFastMo[j];
            }

            // Decrement the count of slow-mmo in the scene
            mFastCount--;

            // Break out of the loop since we found a collision and deleted a slow-mo
            break;
        }
    }

    for (size_t i = 0; i < mSlowCount; ++i)
    {
        // Get a pointer to the ith fastmo in the scene
        SlowMo* pSlowMo = mSlowMo[i];

        // Check if the ball is intersecting with the current fast-mo
        // If it is, the normal and depth values will be updated accordingly
        if (pSlowMo->DoesBodyIntersect(*mBall, normal, depth))
        {
            // Play the slow-mo collection sound effect
            PlayPowerSoundEffect();
            std::cout << "\nSlow-Mo, Collected!..." << std::endl;
            std::cout << "Barriers slowing down for 4 seconds!..." << std::endl;

            // Enable fast-motion effect
            mIsSlowMotionActive = true;
            mSlowMotionTimer = SLOW_MOTION_DURATION;

            // Delete the slow-mo from the scene and free its memory
            delete pSlowMo;
            mSlowMo[i] = nullptr;

            // Shift the remaining slow-mo in the array to remove the empty slot
            for (size_t j = i + 1; j < mSlowCount; ++j)
            {
                mSlowMo[j - 1] = mSlowMo[j];
            }

            // Decrement the count of slow-mmo in the scene
            mSlowCount--;

            // Break out of the loop since we found a collision and deleted a slow-mo
            break;
        }
    }
}

void LevelOneScene::Draw(double deltaTime)
{
    // Clear to dark green
    SDL_SetRenderDrawColor(mRenderer, 23, 99, 93, 255);
    SDL_RenderClear(mRenderer);

    // Draw the floor pieces
    for (size_t i = 0; i < mFloorCount; ++i)
    {
        Vector2 position = mFloorPositions[i];
        Vector2 size = mFloorDimensions[i];
        mDrawRect.x = position.x;
        mDrawRect.y = position.y;
        mDrawRect.w = size.x;
        mDrawRect.h = size.y;

        SDL_SetRenderDrawColor(mRenderer, 64, 219, 131, 255); // Light green
        SDL_RenderFillRect(mRenderer, &mDrawRect);
    }

    // Draw all sprites
    for (size_t i = 0; i < mWallCount; ++i)
    {
        mWalls[i]->Draw();
    }

    for (size_t i = 0; i < mBarrierCount; ++i)
    {
        mBarrier[i]->Draw();
    }

    for (size_t i = 0; i < mHoleCount; ++i)
    {
        mHole[i]->Draw();
    }

    for (size_t i = 0; i < mPowerUpCount; ++i)
    {
        mPowerUps[i]->Draw();
    }

    for (size_t i = 0; i < mPointsCount; ++i)
    {
        if (mTimer > 1.0)
        {
            mPoints[i]->Draw();
        }
    }

    //// Loop through the multi objects and draw each one
    //if (mTimer > 3.0)
    //{
    //    // Draw the mMulti objects
    //    for (size_t i = 0; i < mMultiCount; ++i)
    //    {
    //        mMulti[i]->Draw();
    //        
    //    }
    //}

    // Loop through the fastmo objects and draw each one
    for (size_t i = 0; i < mFastCount; ++i)
    {
        mFastMo[i]->Draw();
    }

    // Loop through the slowmo objects and draw each one
    for (size_t i = 0; i < mSlowCount; ++i)
    {
        mSlowMo[i]->Draw();
    }

    // Draw the ball
    mBall->Draw();

    if (mTimer > 3.0) 
    {
        mMulti->Draw();
    }    
}
