#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <ctime>

#include "Ball.h"
#include "Scene.h"
#include "Texture.h"
#include "RulesScene.h"
#include "LevelOneScene.h"
#include "LevelTwoScene.h"
#include"LevelThreeScene.h"
#include"LevelFourScene.h"
#include"LevelFiveScene.h"



// init initialises SDL and creates a window
bool init();
// loop executes the game loop (captures input, updates game state, and renders to screen)
bool loop(double);
// kill frees memory, shuts down SDL, and exits
void kill();

// Declare a pointer to an SDL_Window object called pWindow
SDL_Window* pWindow;
// Declare a pointer to an SDL_Rect object called pViewport
SDL_Rect* pViewport;
// Declare a pointer to an SDL_Renderer object called pRenderer
SDL_Renderer* pRenderer;
// Declare a pointer to a Scene object called pCurrentScene
Scene* pCurrentScene;

// Declaring TTF font & surface
TTF_Font* pFont;
SDL_Surface* pTextSurface;
SDL_Texture* pTimerTexture;

SDL_Surface* pScoreSurface;
SDL_Texture* pScoreTexture;

// Timer & Colour
SDL_Rect timerRect;
SDL_Color timerTextColor;
// Score & Colour
SDL_Rect scoreRect;
SDL_Color scoreColor;
int currentScore{ 0 };
bool isHighScoreReached{ false };

// Game timer
float timeDelayTimer{ 10.f };
float timeRemainingTimer{ 45.0f };
const float kAddedTime{ 15.0f };

const int kWindowWidth{ 800 };
const int kWindowHeight{ 600 };
const float kTargetFramerate{ 60.0f };
const float kTargetFrametime{ 1000.0f / kTargetFramerate };

// Performance logging timer & event log
float perfLogTimer{ 1.f };
float eventLogTimer{ 1.f };

// Bool statements for Key presses
bool isMusicPlaying{ true };
bool isFullscreen{ false };
bool loggingEnabled{ false };
bool isMessagePrinted = false;
bool areSoundEffectsEnabled{ true };
bool areBallSoundEffectsEnabled{ true };

// Function to update the score based on the operation and points passed in
void UpdateScore(int points, const std::string& operation)
{
    // If the operation is "add", add the points to the current score
    if (operation == "add")
    {
        int newScore = currentScore + points;
        std::cout << currentScore << " + " << points << " = " << newScore << std::endl;
        currentScore = newScore;
    }
    // If the operation is "multiply", multiply the points by the current score
    else if (operation == "multiply")
    {
        int newScore = currentScore * points;
        std::cout << currentScore << " * " << points << " = " << newScore << std::endl;
        currentScore = newScore;
    }

    // If the current score is greater than or equal to 300 and the high score has not been reached yet
    if (currentScore >= 300 && !isHighScoreReached) 
    {
        // Add 15 seconds to the timer
        timeRemainingTimer += kAddedTime;
        std::cout << "\nHIGH SCORE ACHIEVED!... 15 Seconds Added to Timer!..." << std::endl;
        // Set the boolean value to true after adding time
        isHighScoreReached = true;
    }
}

int main(int argc, char** args)
{
    if (!init())
        return 1;

    // Main loop
    // `startTicks` and `endTicks` are used for comparing ticks (in milliseconds) to determine the time delta
    // (in seconds) between frames.
    // `startTime` and `endTime` are used for comparing high-resolution clock values provided by the OS
    // (usually microseconds or nanoseconds) to measure performance with a high degree of accuracy.
    Uint32 startTicks{ 0 };
    Uint32 endTicks{ 0 };
    Uint64 startTime{ 0 };
    Uint64 endTime{ 0 };
    Uint64 tickCount{ 0 };
    double deltaTimeSeconds{ 0 };
    float fpsCountTimer{ 0 };

    std::cout << "\033[33mWelcome to Mighty Putter!\033[0m" << std::endl;
    std::cout << "\n\033[32mPlease see the controls below to change enable logging and various other features:\033[0m" << std::endl;
    std::cout << "\n\033[36mL / I  - Enables / Disables Logging.\033[0m" << std::endl;
    std::cout << "\033[35mM - Enables / Disables Music.\033[0m" << std::endl;
    std::cout << "\033[36mS - Enables / Disables Sound Effects.\033[0m" << std::endl;
    std::cout << "\033[35mF - Enables / Disables Fullscreen.\033[0m" << std::endl;
    std::cout << "\033[36mQ- Quits the Game.\n\033[0m " << std::endl;

    while (true)
    {
        // Timestamp start of game loop
        startTicks = SDL_GetTicks();
        startTime = SDL_GetPerformanceCounter();

        // Execute game loop and break out if exit requested
        if (!loop(deltaTimeSeconds))
            break;

        // Timestamp end of game loop
        endTicks = SDL_GetTicks();
        endTime = SDL_GetPerformanceCounter();

        // Calculate deltas
        float frequency = (float)SDL_GetPerformanceFrequency();
        float elapsedTimeSeconds = (endTime - startTime) / frequency;
        float elapsedTimeMilliseconds = elapsedTimeSeconds * 1000.0f;
        deltaTimeSeconds = (endTicks - startTicks) / 1000.0f;

        // Cap framerate as necessary
        if (elapsedTimeMilliseconds > 0 && elapsedTimeMilliseconds < kTargetFrametime)
        {
            float delay = floor(kTargetFrametime - elapsedTimeMilliseconds);
            SDL_Delay(delay);

            // Update deltas to include the delay
            elapsedTimeMilliseconds += delay;
            deltaTimeSeconds += delay / 1000.0f;
        }

        // Log FPS and delta time every second
        if (loggingEnabled)
        {
            // Increment the tick count
            tickCount++;
            fpsCountTimer += elapsedTimeMilliseconds;
            if (fpsCountTimer > 1000.0f)
            {
                std::cout << "\n\033[31mFPS\033[0m: " << std::to_string(1000.0f / elapsedTimeMilliseconds) << std::endl;
                std::cout << "\033[94mDelta time\033[0m: " << std::to_string(deltaTimeSeconds) << std::endl;
                std::cout << "\033[35mTicks\033[0m: " << std::to_string(tickCount) << std::endl;
                fpsCountTimer = 0;
                tickCount = 0;
            }
        }
    }
    kill();
    return 0;
}

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Error initializing SDL: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        SDL_Log("Failed to initialize SDL_ttf: %s", TTF_GetError());
        return false;
    }

    pWindow = SDL_CreateWindow("Gareth Mason (07076286) Games Programming: Mighty Putter.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kWindowWidth, kWindowHeight, SDL_WINDOW_SHOWN);
    if (!pWindow)
    {
        SDL_Log("Error creating window: %s", SDL_GetError());
        return false;
    }

    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!pRenderer)
    {
        SDL_Log("Error creating renderer: %s", SDL_GetError());
        return false;
    }

    pFont = TTF_OpenFont("Content/Fonts/TFont.ttf", 32);
    if (!pFont)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        SDL_Log("Failed to initialize SDL_mixer: %s", Mix_GetError());
        return false;
    }

    Mix_Music* music = Mix_LoadMUS("Content/Audio/Main_Music.mp3");
    if (!music) 
    {
        SDL_Log("Failed to load music file: %s", Mix_GetError());
        return false;
    }

    Mix_PlayMusic(music, -1);
    bool isMusicPlaying = true;
    // Initialise viewport for windowed mode
    pViewport = new SDL_Rect;
    pViewport->x = 0;
    pViewport->y = 0;
    pViewport->w = kWindowWidth;
    pViewport->h = kWindowHeight;

    // Set up the first scene
    pCurrentScene = new RulesScene(pRenderer, pViewport, kWindowWidth, kWindowHeight);
    pCurrentScene->Load();

    return true;
}

bool loop(double deltaTime)
{
    // Timer size & position
    timerRect.x = 0;
    timerRect.y = 0;
    timerRect.w = 175;
    timerRect.h = 30;

    // Score Counter
    scoreRect.x = 650;
    scoreRect.y = 0;
    scoreRect.w = 90;
    scoreRect.h = 30;


    static InputState input;
    input.mWasMouseLeftPressed = false;
    input.mWasMouseLeftReleased = false;
    input.mWasMouseRightPressed = false;
    input.mWasMouseRightReleased = false;
    input.mHeldKeys = SDL_GetKeyboardState(NULL);

    Uint64 updateStartTicks{ 0 };
    Uint64 updateEndTicks{ 0 };
    Uint64 drawStartTicks{ 0 };
    Uint64 drawEndTicks{ 0 };
    Uint64 eventStartTicks{ 0 };
    Uint64 eventEndTicks{ 0 };

    // Event loop
    SDL_Event event;
    float frequency = (float)SDL_GetPerformanceFrequency();

    while (SDL_PollEvent(&event) != 0)
    {
        eventStartTicks = SDL_GetPerformanceCounter();
        switch (event.type)
        {
        case SDL_QUIT:
            return false;
        case SDL_MOUSEBUTTONDOWN:
            input.mWasMouseLeftPressed = event.button.button == SDL_BUTTON_LEFT;
            input.mWasMouseRightPressed = event.button.button == SDL_BUTTON_RIGHT;
            break;
        case SDL_MOUSEBUTTONUP:
            input.mWasMouseLeftReleased = event.button.button == SDL_BUTTON_LEFT;
            input.mWasMouseRightReleased = event.button.button == SDL_BUTTON_RIGHT;
            break;
        case SDL_MOUSEMOTION:
            input.mCursorPosition.x = event.motion.x - pViewport->x;
            input.mCursorPosition.y = event.motion.y - pViewport->y;
            break;
        case SDL_KEYDOWN:
        {
            // Get the current date and time
            time_t now = time(nullptr);
            char timeStr[80];
            struct tm timeInfo;
            localtime_s(&timeInfo, &now);
            strftime(timeStr, 80, "%Y-%m-%d %H:%M:%S", &timeInfo);

            // Print the key and action (pressed or released)
            std::cout << timeStr << " Key " << SDL_GetKeyName(event.key.keysym.sym) << " " << "pressed!" << std::endl;

            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                // Quits the game.
                std::cout << "\033[91mGame has been Exited!..\033[0m" << std::endl;
                return false;
            case SDLK_m:
                // Toggle music on/off
                if (isMusicPlaying)
                {
                    Mix_PauseMusic();
                    isMusicPlaying = false;
                    std::cout << "Music is Off!..." << std::endl;
                }
                else
                {
                    Mix_ResumeMusic();
                    isMusicPlaying = true;
                    std::cout << "Music is On!..." << std::endl;
                }
                break;

            case SDLK_s:
                // Toggle sound effects on/off
                if (areSoundEffectsEnabled)
                {
                    areSoundEffectsEnabled = false;
                    areBallSoundEffectsEnabled = false; // Disable ball sound effects
                    std::cout << "Sound Effects are Off!..." << std::endl;
                }
                else
                {
                    areSoundEffectsEnabled = true;
                    areBallSoundEffectsEnabled = true; // Enable ball sound effects
                    std::cout << "Sound Effects are On!..." << std::endl;

                }
                break;
            case SDLK_f:
                // Toggle fullscreen/windowed mode
                if (isFullscreen)
                {
                    SDL_SetWindowFullscreen(pWindow, 0);
                    isFullscreen = false;
                    SDL_SetWindowPosition(pWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

                    pViewport->x = 0;
                    pViewport->y = 0;
                }
                else
                {
                    SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    isFullscreen = true;

                    // Update the viewport
                    int w, h;
                    SDL_GetWindowSize(pWindow, &w, &h);

                    pViewport->x = (w / 2) - (kWindowWidth / 2);
                    pViewport->y = (h / 2) - (kWindowHeight / 2);
                }

                SDL_RenderSetViewport(pRenderer, pViewport);
                break;
            case SDLK_i:
            case SDLK_l:
                loggingEnabled = !loggingEnabled;
                std::cout << timeStr << " Logging " << (loggingEnabled ? "Enabled!..." : "Disabled!...") << std::endl;
                break;
            }
            break;
        }
        case SDL_KEYUP:
        {
            //// Print the key and action (pressed or released)
            //if (loggingEnabled && eventLogTimer <= 0.f)
            //{
            //    float eventDeltaMilliseconds = ((eventEndTicks - eventStartTicks) / frequency) * 1000.f;
            //    std::cout << "\033[32mEvent time: \033[0m" << eventDeltaMilliseconds << " ms" << std::endl;
            //    eventLogTimer = 1.f;
            //}
            break;
        }
        }
        eventEndTicks = SDL_GetPerformanceCounter();

        // Log the event time
        if (loggingEnabled && eventLogTimer <= 0.f)
        {
            float eventDeltaMilliseconds = ((eventEndTicks - eventStartTicks) / frequency) * 1000.f;
            std::cout << "\033[32mEvent time:\033[0m " << eventDeltaMilliseconds << " ms" << std::endl;
            eventLogTimer = 1.f;
        }
    }
     
    perfLogTimer -= deltaTime;
    eventLogTimer -= deltaTime;

	//float frequency = (float)SDL_GetPerformanceFrequency();
   
    updateStartTicks = SDL_GetPerformanceCounter();
    pCurrentScene->Update(input, deltaTime);
    updateEndTicks = SDL_GetPerformanceCounter();
    float updateDeltaMilliseconds = ((updateEndTicks - updateStartTicks) / frequency) * 1000.f;

    drawStartTicks = SDL_GetPerformanceCounter();
    pCurrentScene->Draw(deltaTime);
    drawEndTicks = SDL_GetPerformanceCounter();
	float drawDeltaMilliseconds = ((drawEndTicks - drawStartTicks) / frequency) * 1000.f;

    // Print update and draw times once per second
    if (loggingEnabled && perfLogTimer <= 0.f)
    {
        std::cout << "\033[31mUpdate time:\033[0m " << updateDeltaMilliseconds << " ms\n";
        std::cout << "\033[94mDraw time: \33[0m" << drawDeltaMilliseconds << " ms" << std::endl;
        perfLogTimer = 1.f;
    }

    // record the ticks before the operation and afrer.
    // - before ticks from the after ticks (ms) /1000

    if (timeDelayTimer > 0.f)
    {
        timeDelayTimer -= deltaTime;
        // do whatever you want to do with this timer, e.g. draw tex
    }

    else if (timeRemainingTimer > 0.f)
    {
        timeRemainingTimer -= deltaTime;
        // same again. draw text for the actual timer, set the colour to red if it's below 10.f, etc
        // Render remaining time
        char remainingText[22];
        char score[60];

        // Score font
        snprintf(score, sizeof(score), "Score: %d", currentScore);
        SDL_Color scoreColor = { 255, 255, 255, 255 };
        SDL_Surface* pScoreSurface = TTF_RenderText_Solid(pFont, score, scoreColor);
        SDL_Texture* pScoreTexture = SDL_CreateTextureFromSurface(pRenderer, pScoreSurface);
        SDL_RenderCopy(pRenderer, pScoreTexture, nullptr, &scoreRect);
        
        // Timer font
        snprintf(remainingText, sizeof(remainingText), "Remaining Time: %.1f", timeRemainingTimer);
        SDL_Color remainingTextColor = { 255, 255, 255, 255 };
        if (timeRemainingTimer < 10.f) 
        {
            remainingTextColor = { 255, 0, 0, 255 };
        }

        if (timeRemainingTimer < 10.f && !isMessagePrinted)
        {
            std::cout << "\n\033[91mHURRY UP! Only 10 seconds remaining!..\033[0m" << std::endl;
            isMessagePrinted = true;
        }

        SDL_Surface* pTextSurface = TTF_RenderText_Solid(pFont, remainingText, remainingTextColor);
        SDL_Texture* pTextTexture = SDL_CreateTextureFromSurface(pRenderer, pTextSurface);
        SDL_RenderCopy(pRenderer, pTextTexture, nullptr, &timerRect);

        // Free resources
        SDL_FreeSurface(pScoreSurface);
        SDL_DestroyTexture(pScoreTexture);
        SDL_FreeSurface(pTextSurface);
        SDL_DestroyTexture(pTextTexture);
    }
    else
    {
        // both timers have ended, so it's time to quit
        std::cout << "\033[91mGame Time has Expired!...\033[0m" << std::endl;
        return false;
    }

    // Present the updated window to the screen
    SDL_RenderPresent(pRenderer);

    Scene* pNextScene = pCurrentScene->GetNextScene();
    if (pNextScene != nullptr)
    {
        delete pCurrentScene; // unloads the scene via the destructor
        pCurrentScene = pNextScene;
        pCurrentScene->Load(); // loads the new scene ready for the next frame
    }

    return true;
}

void kill()
{
    delete pCurrentScene;
    TTF_CloseFont(pFont);
    SDL_DestroyTexture(pTimerTexture);
    SDL_FreeSurface(pTextSurface);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
    pRenderer = NULL;
    SDL_Quit();
}