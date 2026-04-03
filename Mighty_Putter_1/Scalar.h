#pragma once

#include <algorithm>
#include <math.h>

// Define a constant conversion factor from degrees to radians
#define M_DEG_TO_RAD 0.01745329251f

// Define a template function to clamp a value between a lower and upper bound
template <typename T>
T clamp(const T& n, const T& lower, const T& upper) {
    // Return the value of n clamped between the lower and upper bounds
    return std::max(lower, std::min(n, upper));
}