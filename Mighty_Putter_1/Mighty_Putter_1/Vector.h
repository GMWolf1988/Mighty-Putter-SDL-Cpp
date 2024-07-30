#pragma once

#pragma once

#include <math.h>
#include <SDL.h>
#include "Transform.h"

// Define Vector2 as an alias for SDL_Point
typedef SDL_Point Vector2;

// Define a 2D vector struct with float components
struct Vector2f
{
    float x; // x component
    float y; // y component

    // Default constructor initializes x and y to 0
    Vector2f() : x(0.f), y(0.f) {}

    // Constructor that initializes x and y to given values
    Vector2f(float x, float y) : x(x), y(y) {}

    // Constructor that converts an SDL_Point to a Vector2f
    Vector2f(Vector2 vec2) : x((float)vec2.x), y((float)vec2.y) {}

    // Equality operator to compare a Vector2f to a float value
    bool operator==(const float value) const
    {
        return x == value && y == value;
    }

    // Inequality operator to compare a Vector2f to a float value
    bool operator!=(const float value) const
    {
        return !(*this == value);
    }

    // Addition operator to add two Vector2f objects together
    Vector2f operator+(const Vector2f& other) const
    {
        return Vector2f(x + other.x, y + other.y);
    }

    // Addition operator to add a float value to a Vector2f object
    Vector2f operator+(const float amount) const
    {
        return Vector2f(x + amount, y + amount);
    }

    // Addition assignment operator to add a Vector2f object to this object
    Vector2f& operator+=(const Vector2f& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Addition assignment operator to add a float value to this object
    Vector2f& operator+=(const float amount)
    {
        x += amount;
        y += amount;
        return *this;
    }

    // Negation operator to invert the signs of the x and y components
    Vector2f operator-() const
    {
        return Vector2f(-x, -y);
    }

    // Subtraction operator to subtract a Vector2f object from this object
    Vector2f operator-(const Vector2f& other) const
    {
        return Vector2f(x - other.x, y - other.y);
    }

    // Subtraction operator to subtract a float value from this object
    Vector2f operator-(const float amount) const
    {
        return Vector2f(x - amount, y - amount);
    }

    // Subtraction assignment operator to subtract a Vector2f object from this object
    Vector2f& operator-=(const Vector2f& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // Subtraction assignment operator to subtract a float value from this object
    Vector2f& operator-=(const float amount)
    {
        return *this += -amount;
    }

    // Multiplication operator to multiply two Vector2f objects together
    Vector2f operator*(const Vector2f& other) const
    {
        return Vector2f(x * other.x, y * other.y);
    }

    // Multiplication operator to multiply this object by a float factor
    Vector2f operator*(const float factor) const
    {
        return Vector2f(x * factor, y * factor);
    }

    // Division assignment operator to divide this object by a float factor
    Vector2f& operator/=(const float factor)
    {
        x /= factor;
        y /= factor;
        return *this;
    }

    // Length function to compute the length of this object as a vector
    float Length()
    {
        return sqrt(x * x + y * y);
    }

    // DistanceTo function to compute the distance to a target Vector2f object
    float DistanceTo(Vector2f target)
    {
        float deltaX = x - target.x;
        float deltaY = y - target.y;
        return sqrt(deltaX * deltaX + deltaY * deltaY);
    }

    // Normalised function to return a unit-length version of this object
    Vector2f Normalised()
    {
        float length = Length();
        return { x / length, y / length };
    }

    // Dot function to compute the dot product of this object with another Vector2f object
    float Dot(Vector2f other)
    {
        return x * other.x + y * other.y;
    }

    // Cross function to compute the cross product of this object with another Vector2f object
    float Cross(Vector2f other)
    {
        return x * other.y - y * other.x;
    }

    // Transform function to apply a transformation matrix to this object
    Vector2f Transform(Transform transform)
    {
        return Vector2f(
            transform.cosine * x - transform.sine * y + transform.positionX,
            transform.sine * x + transform.cosine * y + transform.positionY
        );
    }
};