#include "LevelFiveScene.h"
#include "LevelOneScene.h"
#include "Texture.h"
#include "Collision.h"

void UpdateScore(int points, const std::string& operation);

LevelFiveScene::~LevelFiveScene()
{
    // Delete dynamically allocated objects
    delete mBall;

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

    for (size_t i = 0; i < mMultiCount; ++i)
    {
        delete mMulti[i];
    }

    for (size_t i = 0; i < mFastCount; ++i)
    {
        delete mFastMo[i];
    }

    for (size_t i = 0; i < mSlowCount; ++i)
    {
        delete mSlowMo[i];
    }

}

void LevelFiveScene::Load()
{
    // Print loading messages to console
    std::cout << "\n\033[33mLevel Five has Loaded!...\033[0m" << std::endl;
    std::cout << "\033[36mAll Sprites have loaded..\033[0m" << std::endl;

    //Load Sound Effects
    LoadWallSoundEffect();
    LoadPointSoundEffect();
    LoadPotSoundEffect();
    LoadMultiplySoundEffect();
    LoadPowerSoundEffect();

    // Create a ball and place it at the start of the course
    mBall = new Ball(mRenderer, { 200, 514 });

    // Create wall pieces
    mWallCount = 16;
    mWalls = (Wall**)malloc(mWallCount * sizeof(Wall*));
    mWalls[0] = new Wall(mRenderer, { 84, 489 }, 90);
    mWalls[0]->SetDimensions({ 127, 32 });
    mWalls[1] = new Wall(mRenderer, { 373, 565 });
    mWalls[1]->SetDimensions({ 610, 32 });
    mWalls[2] = new Wall(mRenderer, { 685, 390 }, 90);
    mWalls[2]->SetDimensions({ 383, 32 });
    mWalls[3] = new Wall(mRenderer, { 450, 212 });
    mWalls[3]->SetDimensions({ 500, 32 });
    mWalls[4] = new Wall(mRenderer, { 200, 85 });
    mWalls[5] = new Wall(mRenderer, { 84,  199 }, 90);
    mWalls[5]->SetDimensions({ 260, 32 });
    mWalls[6] = new Wall(mRenderer, { 203, 410 });
    mWalls[6]->SetDimensions({ 270, 32 });
    mWalls[7] = new Wall(mRenderer, { 203, 340 });
    mWalls[7]->SetDimensions({ 270, 32 });
    mWalls[8] = new Wall(mRenderer, { 334, 375 }, 90);
    mWalls[8]->SetDimensions({ 102, 32 });
    mWalls[9] = new Wall(mRenderer, { 550, 375 }, 90);
    mWalls[9]->SetDimensions({ 102, 32 });
    mWalls[10] = new Wall(mRenderer, { 410, 375 }, 90);
    mWalls[10]->SetDimensions({ 102, 32 });
    mWalls[11] = new Wall(mRenderer, { 470, 340 });
    mWalls[11]->SetDimensions({ 150, 32 });
    mWalls[12] = new Wall(mRenderer, { 470, 410 });
    mWalls[12]->SetDimensions({ 150, 32 });
    mWalls[13] = new Wall(mRenderer, { 315, 111 }, 90);
    mWalls[13]->SetDimensions({ 83, 32 });
    mWalls[14] = new Wall(mRenderer, { 216, 183 }, 90);
    mWalls[14]->SetDimensions({ 70, 32 });
    mWalls[15] = new Wall(mRenderer, { 281, 164 });
    mWalls[15]->SetDimensions({ 100, 32 });

    // Set up floor piece arrays
    mFloorCount = 6;
    mFloorPositions = (Vector2*)malloc(mFloorCount * sizeof(Vector2));
    mFloorDimensions = (Vector2*)malloc(mFloorCount * sizeof(Vector2));
    mFloorPositions[0] = { 100, 425 };
    mFloorDimensions[0] = { 450, 125 };
    mFloorPositions[1] = { 550, 325 };
    mFloorDimensions[1] = { 120, 225 };
    mFloorPositions[2] = { 100, 200 };
    mFloorDimensions[2] = { 570,125 };
    mFloorPositions[3] = { 350, 325 };
    mFloorDimensions[3] = { 50, 100 };
    mFloorPositions[4] = { 100, 100 };
    mFloorDimensions[4] = { 100, 100 };
    mFloorPositions[5] = { 100, 100 };
    mFloorDimensions[5] = { 200, 50 };

    // Create barriers
    mBarrierCount = 5;
    mBarrier = (Barrier**)malloc(mBarrierCount * sizeof(Barrier*));
    mBarrier[0] = new Barrier(mRenderer, { 340, 300 });
    mBarrier[0]->SetDimensions({ 25, 25 });
    mBarrier[0]->SetXRange(320.f, 420.f, { 150.f, 0.f });
    mBarrier[1] = new Barrier(mRenderer, { 372, 448 });
    mBarrier[1]->SetDimensions({ 25, 25 });
    mBarrier[1]->SetYRange(448.f, 495.f, { 0.f, 75.f });
    mBarrier[2] = new Barrier(mRenderer, { 185, 180 });
    mBarrier[2]->SetDimensions({ 25, 25 });
    mBarrier[2]->SetXRange(125.f, 185.f, { 60.f, 0.f });
    mBarrier[3] = new Barrier(mRenderer, { 550, 448 });
    mBarrier[3]->SetDimensions({ 25, 25 });
    mBarrier[3]->SetYRange(448.f, 525.f, { 0.f, 110.f });
    mBarrier[4] = new Barrier(mRenderer, { 475, 300 });
    mBarrier[4]->SetDimensions({ 25, 25 });
    mBarrier[4]->SetYRange(250.f, 300.f, { 0.f, 110.f });


    // PowerUp setup
    mPowerUpCount = 1;
    mPowerUps = (PowerUps**)malloc(mPowerUpCount * sizeof(PowerUps*));
    mPowerUps[0] = new PowerUps(mRenderer, { 600, 350 });
    mPowerUps[0]->SetDimensions({ 30, 30 });
    mPowerUps[0]->SetXPRange(600.f, 620.f, { 100.f, 0.f });

    // Points set up
    mPointsCount = 3;
    mPoints = (Points**)malloc(mPointsCount * sizeof(Points*));
    mPoints[0] = new Points(mRenderer, { 130, 270 });
    mPoints[0]->SetDimensions({ 30,30 });
    mPoints[0]->SetXPRange(130.f, 200.f, { 120.f ,0.f });
    mPoints[1] = new Points(mRenderer, { 530, 510 });
    mPoints[1]->SetDimensions({ 30,30 });
    mPoints[1]->SetXPRange(530.f, 650.f, { 120.f ,0.f });
    mPoints[2] = new Points(mRenderer, { 520, 250 });
    mPoints[2]->SetDimensions({ 30,30 });
    mPoints[2]->SetXPRange(520.f, 550.f, { 120.f ,0.f });

    // Multiply set up
    mMultiCount = 1;
    mMulti = (MultiplyPoints**)malloc(mPointsCount * sizeof(MultiplyPoints*));
    mMulti[0] = new MultiplyPoints(mRenderer, { 372, 360 });
    mMulti[0]->SetDimensions({ 30,30 });

    // FastMo set up
    mFastCount = 1;
    mFastMo = (FastMo**)malloc(mFastCount * sizeof(FastMo*));
    mFastMo[0] = new FastMo(mRenderer, { 460, 530 });
    mFastMo[0]->SetDimensions({ 30,30 });
    mFastMo[0]->SetYRange(475.f, 530.f, { 0.f ,95.f });

    // SlowMo set up
    mSlowCount = 1;
    mSlowMo = (SlowMo**)malloc(mSlowCount * sizeof(SlowMo*));
    mSlowMo[0] = new SlowMo(mRenderer, { 259, 250 });
    mSlowMo[0]->SetDimensions({ 30,30 });
    mSlowMo[0]->SetYRange(250.f, 310.f, { 0.f ,160.f });

    // Create hole
    mHoleCount = 1;
    mHole = (Hole**)malloc(mHoleCount * sizeof(Hole*));
    mHole[0] = new Hole(mRenderer, { 265, 125 });
}

void LevelFiveScene::Update(const InputState& input, double deltaTime)
{
    // Call base Update
    Scene::Update(input, deltaTime);

    mBall->Update(input, deltaTime);

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

            mNextScene = new LevelOneScene(mRenderer, mViewport, mScreenWidth, mScreenHeight);
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

    // Start a for loop that iterates over the number of multiply in the scene
    for (size_t i = 0; i < mMultiCount; ++i)
    {
        // Get a pointer to the ith multiply in the scene
        MultiplyPoints* pMultiply = mMulti[i];

        // Check if the ball is intersecting with the current power-up
        // If it is, the normal and depth values will be updated accordingly
        if (pMultiply->DoesBodyIntersect(*mBall, normal, depth))
        {
            // Move the ball out of the power-up by the depth amount along the normal vector
            mBall->Move(-normal * depth);

            // Play the power-up collection sound effect
            PlayMultiplySoundEffect();
            std::cout << "\nx10 Multiplier Collect!..." << std::endl;
            // Update the score and store the updated score in the variable
            UpdateScore(10, "multiply");
            // Resolve the collision between the ball and the multiply
            ResolveCollision(*mBall, *pMultiply, normal, depth);

            // Delete the multiply from the scene and free its memory
            delete pMultiply;
            mMulti[i] = nullptr;

            // Shift the remaining multiply in the array to remove the empty slot
            for (size_t j = i + 1; j < mMultiCount; ++j)
            {
                mMulti[j - 1] = mMulti[j];
            }

            // Decrement the count of multiply in the scene
            mMultiCount--;

            // Break out of the loop since we found a collision and deleted a multiply
            break;
        }
    }

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

void LevelFiveScene::Draw(double deltaTime)
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
    // Loop through the multi objects and draw each one
    if (mTimer > 3.0)
    {
        // Draw the mMulti objects
        for (size_t i = 0; i < mMultiCount; ++i)
        {
            mMulti[i]->Draw();

        }
    }

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
}


