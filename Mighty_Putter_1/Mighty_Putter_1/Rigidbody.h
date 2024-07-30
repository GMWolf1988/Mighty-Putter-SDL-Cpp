#pragma once

#include <string>
#include <SDL.h>

#include "Object.h"
#include "Vector.h"

class RigidBody : public Object
{
public:
    // Enumeration for the shape of the rigid body
    enum Shape { Circle, Polygon };

    // Set the dimensions of the rigid body
    void SetDimensions(Vector2 dimensions);

    // Getter for the shape of the rigid body
    Shape GetShape() const;

    // Change the linear velocity of the rigid body by a given amount
    void ChangeLinearVelocity(Vector2f amount);

    // Getter for the linear velocity of the rigid body
    Vector2f GetLinearVelocity() const;

    // Check if the rigid body is static (has infinite mass)
    bool IsStatic() const;

    // Getter for the radius of the rigid body (for circle shapes)
    float GetRadius() const;

    // Getter for the mass of the rigid body
    float GetMass() const;

    // Getter for the inverse mass of the rigid body
    float GetInverseMass() const;

    // Getter for the coefficient of restitution of the rigid body
    float GetRestitution() const;

    // Getter for an array of transformed vertices for polygon shapes
    Vector2f* GetTransformedVertices();

    // Getter for the number of vertices in the transformed vertex array
    size_t GetVertexCount() const;

    // Move the rigid body by a given amount
    void Move(Vector2f amount);

    // Move the rigid body to a given position
    void MoveTo(Vector2f position);

    // Add a force to the rigid body
    void AddForce(Vector2f force);

    // Check if the rigid body intersects with another rigid body,
    // and if so, return the normal of the collision and the depth of penetration
    bool DoesBodyIntersect(RigidBody& other, Vector2f& outNormal, float& outDepth);

    // Update function to be overridden by child classes
    virtual void Update(const InputState& input, double deltaTime);

protected:
    // Constructor that takes a pointer to an SDL_Renderer object,
    // a path to the sprite texture file,
    // a Vector2f object representing the position of the rigid body,
    // and an optional double representing the initial rotation of the rigid body
    RigidBody(SDL_Renderer* pRenderer, std::string spriteTexturePath, Vector2f position, double rotationDegrees);

    // Destructor for cleaning up dynamically allocated memory
    ~RigidBody();

    
     // Initialises this RigidBody as a static Circle.
     // radius The circle's radius.
     // radius The circle's density value (g/cm³).
     // return Whether the initialisation was successful.
    bool InitStaticCircle(float radius, float density);

    
      // Initialises this RigidBody as a Circle.
     // radius The circle's radius.
     // density The circle's density value (g/cm³).
     // restitution The circle's restitution coefficient.
     // return Whether the initialisation was successful.
    bool InitCircle(float radius, float density, float restitution);

    
    // Initialises this RigidBody as a static Box.
    // width The width of the box.
    // height The height of the box.
    // density The box's density value (g/cm³).
    // return Whether the initialisation was successful.
    bool InitStaticBox(float width, float height, float density);

    /**
     * @brief Initialises this RigidBody as a box-shaped Polygon.
     * @param width The width of the box.
     * @param height The height of the box.
     * @param density The box's density value (g/cm³).
     * @param restitution The box's restitution coefficient.
     * @return Whether the initialisation was successful.
     */
    bool InitBox(float width, float height, float density, float restitution);

    /**
     * @brief Updates vertices for Polygon shapes.
     */
    void UpdateVertices();

    Shape mShape;
    double mRotationRadians{ 0 };

    // Motion properties
    Vector2f mLinearVelocity;
    Vector2f mForce;
    float mLinearFriction{ 1.02f };
    float mStoppedEpsilon{ 0.1f };

    // Physical properties
    bool mIsStatic{ false };
    float mArea;
    float mDensity;
    float mMass;
    float mInverseMass;
    float mRestitution;

    // Circle-specific properties
    float mRadius;

    // Polygon-specific properties
    float mWidth;
    float mHeight;
    float mNewWidth;
    float mNewHeight;
    Vector2f mSizeSpeed;

    size_t mVertexCount{ 0 };
    Vector2f* mVertices;
    Vector2f* mTransformedVertices;
    bool mTransformUpdateRequired;

private:
    /**
     * @brief Checks for intersection between this RigidBody and a given Circle-shaped RigidBody using Separating Axis
     * Theorem (SAT). Outputs both the normal and depth of the intersection if there is one.
     * @param other The other RigidBody, assumed to be of Circle shape (returns false early if it isn't).
     * @param outNormal The intersection normal.
     * @param outDepth The intersection depth.
     * @return Whether there's an intersection.
     */
    bool DoesCircleIntersect(RigidBody& circle, Vector2f& outNormal, float& outDepth);

    /**
     * @brief Checks for intersection between this RigidBody and a given Polygon-shaped RigidBody using Separating Axis
     * Theorem (SAT). Outputs both the normal and depth of the intersection if there is one.
     * TODO: update this to support any polygon instead of just boxes.
     * @param other The other RigidBody, assumed to be of Polygon shape (returns false early if it isn't).
     * @param outNormal The intersection normal.
     * @param outDepth The intersection depth.
     * @return Whether there's an intersection.
     */
    bool DoesPolygonIntersect(RigidBody& polygon, Vector2f& outNormal, float& outDepth);
};
