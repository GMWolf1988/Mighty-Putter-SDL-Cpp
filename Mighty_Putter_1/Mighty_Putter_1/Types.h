#pragma once

#include <SDL.h>

#include "Vector.h"

// Define a struct to represent the input state
struct InputState
{
    Vector2 mCursorPosition; // The position of the cursor on the screen
    bool mWasMouseLeftPressed; // Whether the left mouse button was pressed in the previous frame
    bool mWasMouseLeftReleased; // Whether the left mouse button was released in the previous frame
    bool mWasMouseRightPressed; // Whether the right mouse button was pressed in the previous frame
    bool mWasMouseRightReleased; // Whether the right mouse button was released in the previous frame
    const unsigned char* mHeldKeys; // Pointer to an array of booleans indicating which keys are currently held down
};