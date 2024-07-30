#include <algorithm>
#include <cstdlib>
#include <math.h>

#include "RigidBody.h"
#include "Scalar.h"
#include "Transform.h"
#include "Collision.h"

// Set the dimensions of the rigid body
void RigidBody::SetDimensions(Vector2 dimensions)
{
    // Call the parent class's SetDimensions function to update the object's dimensions
    Object::SetDimensions(dimensions);

    // Set the width and height of the rigid body based on the new dimensions
    mWidth = dimensions.x;
    mHeight = dimensions.y;

    // Update the vertices of the rigid body to reflect the new dimensions
    UpdateVertices();
}

// Get the shape of the rigid body
RigidBody::Shape RigidBody::GetShape() const
{
    return mShape;
}

// Change the linear velocity of the rigid body by a given amount
void RigidBody::ChangeLinearVelocity(Vector2f amount)
{
    mLinearVelocity += amount;
}

// Get the current linear velocity of the rigid body
Vector2f RigidBody::GetLinearVelocity() const
{
    return mLinearVelocity;
}

// Check if the rigid body is static
bool RigidBody::IsStatic() const
{
    return mIsStatic;
}

// Get the radius of the rigid body
float RigidBody::GetRadius() const
{
    return mRadius;
}

// Get the mass of the rigid body
float RigidBody::GetMass() const
{
    return mMass;
}

// Get the inverse mass of the rigid body (1 / mass)
float RigidBody::GetInverseMass() const
{
    return mInverseMass;
}

// Get the restitution coefficient of the rigid body
float RigidBody::GetRestitution() const
{
    return mRestitution;
}

// Get a pointer to the transformed vertices of the rigid body
Vector2f* RigidBody::GetTransformedVertices()
{
    // If the transform update is required, update the vertices
    if (mTransformUpdateRequired)
    {
        // Create a transform based on the rigid body's position, rotation, and scale
        Transform transform = { mPosition.x, mPosition.y, (float)mRotationRadians };

        // Loop through each vertex in the rigid body's vertex array
        for (size_t i = 0; i < mVertexCount; ++i)
        {
            // Transform the vertex by the rigid body's transform
            Vector2f vertex = mVertices[i];
            mTransformedVertices[i] = vertex.Transform(transform);
        }

        // Set the transform update flag to false, since we've just updated the vertices
        mTransformUpdateRequired = false;
    }

    // Return a pointer to the transformed vertices
    return mTransformedVertices;
}

// Get the number of vertices in the rigid body
size_t RigidBody::GetVertexCount() const
{
    return mVertexCount;
}

// Move the rigid body by a given amount
void RigidBody::Move(Vector2f amount)
{
    // Call the parent class's Move function to update the object's position
    Object::Move(amount);

    // Set the transform update flag to true, since the object's position has changed
    mTransformUpdateRequired = true;
}

// Move the rigid body to a specific position
void RigidBody::MoveTo(Vector2f position)
{
    // Set the rigid body's position to the specified position
    mPosition = position;

    // Set the transform update flag to true, since the object's position has changed
    mTransformUpdateRequired = true;
}

// Add a force to the rigid body
void RigidBody::AddForce(Vector2f force)
{
    // Add the given force to the total force acting on the rigid body
    mForce += force;
}

// Check if this rigid body intersects with another rigid body, and calculate the normal and depth of the collision if it does
bool RigidBody::DoesBodyIntersect(RigidBody& other, Vector2f& outNormal, float& outDepth)
{
    // Check the shape of the other rigid body and call the appropriate intersection function
    switch (other.GetShape())
    {
    case Circle:
        return DoesCircleIntersect(other, outNormal, outDepth);
    case Polygon:
        return DoesPolygonIntersect(other, outNormal, outDepth);
    }

    // If the shape is unknown, return false
    return false;
}

// Update the rigid body's position and velocity based on its force, mass, and friction
void RigidBody::Update(const InputState& input, double deltaTime)
{
    // Update the linear velocity based on the current force acting on the rigid body
    mLinearVelocity += mForce * deltaTime;

    // Update the position based on the current linear velocity
    mPosition += mLinearVelocity * deltaTime;

    // Reset the force acting on the rigid body to zero
    mForce = { 0.f, 0.f };

    // TODO: replace this friction with something more realistic
    // Apply linear friction to the velocity if it is above a certain threshold
    if (abs(mLinearVelocity.x) > mStoppedEpsilon || abs(mLinearVelocity.y) > mStoppedEpsilon)
    {
        mLinearVelocity /= mLinearFriction;
    }
}

// Constructor for the rigid body class, which sets the initial rotation in radians
RigidBody::RigidBody(SDL_Renderer* pRenderer, std::string spriteTexturePath, Vector2f position, double rotationDegrees)
    : Object(pRenderer, spriteTexturePath, position, rotationDegrees)
{
    mRotationRadians = mRotationDegrees * M_DEG_TO_RAD;
}

// Destructor for the rigid body class, which frees any allocated memory for vertices
RigidBody::~RigidBody()
{
    if (mVertexCount > 0)
    {
        free(mVertices);
        free(mTransformedVertices);
    }
}

// Initialize a static rigid body in the shape of a circle
bool RigidBody::InitStaticCircle(float radius, float density)
{
    // Set the rigid body as static
    mIsStatic = true;

    // Initialize the circle shape with the given radius and density
    if (!InitCircle(radius, density, 0.f))
        return false;

    // Return true if initialization was successful
    return true;
}

// Initialize a rigid body in the shape of a circle
bool RigidBody::InitCircle(float radius, float density, float restitution)
{
    // TODO: validate inputs

    // Set the shape of the rigid body to a circle
    mShape = Shape::Circle;

    // Set the radius of the circle and calculate its area
    mRadius = radius;
    mArea = radius * radius * M_PI;

    // Set the density of the circle and calculate its mass and inverse mass
    mDensity = density;
    mMass = mArea * density;
    mInverseMass = 1.f / mMass;

    // Set the restitution coefficient of the circle
    mRestitution = clamp(restitution, 0.f, 1.f);

    // Return true if initialization was successful
    return true;
}

// Initialize a static rigid body in the shape of a box
bool RigidBody::InitStaticBox(float width, float height, float density)
{
    // Set the rigid body as static
    mIsStatic = true;

    // Initialize the box shape with the given width, height, and density
    if (!InitBox(width, height, density, 1.f))
        return false;

    // Return true if initialization was successful
    return true;
}

// Initialize a rigid body in the shape of a box
bool RigidBody::InitBox(float width, float height, float density, float restitution)
{
    // TODO: validate inputs

    // Set the shape of the rigid body to a polygon
    mShape = Shape::Polygon;

    // Calculate the area of the box and set its width and height
    mArea = width * height;
    mWidth = width;
    mHeight = height;

    // Calculate the density, mass, and inverse mass of the box
    mDensity = density;
    mMass = mArea * density;
    mInverseMass = 1.f / mMass;

    // Set the restitution coefficient of the box
    mRestitution = clamp(restitution, 0.f, 1.f);

    // Update the vertices of the box
    UpdateVertices();

    // Return true if initialization was successful
    return true;
}

// Update the vertices of the rigid body based on its shape and dimensions
void RigidBody::UpdateVertices()
{
    // TODO: make this support shapes other than boxes

    // If the rigid body doesn't have any vertices yet, allocate memory for them
    if (mVertexCount == 0)
    {
        mVertexCount = 4;
        mVertices = (Vector2f*)malloc(mVertexCount * sizeof(Vector2f));
        mTransformedVertices = (Vector2f*)malloc(mVertexCount * sizeof(Vector2f));
    }

    // Calculate the positions of the vertices based on the width and height of the rigid body
    float left = -mWidth / 2.f;
    float right = left + mWidth;
    float bottom = -mHeight / 2.f;
    float top = bottom + mHeight;

    mVertices[0] = { left, top };
    mVertices[1] = { right, top };
    mVertices[2] = { right, bottom };
    mVertices[3] = { left, bottom };

    // Set the transform update flag to true, since the vertices have changed
    mTransformUpdateRequired = true;
}

// Check if this circle intersects with another rigid body (either a circle or a polygon), and calculate the normal and depth of the collision if it does
bool RigidBody::DoesCircleIntersect(RigidBody& circle, Vector2f& outNormal, float& outDepth)
{
    // If the other rigid body is not a circle, return false
    if (circle.GetShape() != Shape::Circle)
        return false;

    // Check if the current rigid body is a circle or a polygon and call the appropriate intersection function
    switch (mShape)
    {
    case Circle:
        if (DoesCircleIntersectCircle(*this, circle, outNormal, outDepth))
            return true;
    case Polygon:
        if (DoesPolygonIntersectCircle(*this, circle, outNormal, outDepth))
            return true;
    }

    // If there is no intersection, return false
    return false;
}

// Check if this polygon intersects with another rigid body (either a circle or a polygon), and calculate the normal and depth of the collision if it does
bool RigidBody::DoesPolygonIntersect(RigidBody& polygon, Vector2f& outNormal, float& outDepth)
{
    // If the other rigid body is not a polygon, return false
    if (polygon.GetShape() != Shape::Polygon)
        return false;

    // Check if the current rigid body is a circle or a polygon and call the appropriate intersection function
    switch (mShape)
    {
    case Circle:
        if (DoesPolygonIntersectCircle(polygon, *this, outNormal, outDepth))
            return true;
    case Polygon:
        if (DoesPolygonIntersectPolygon(*this, polygon, outNormal, outDepth))
            return true;
    }

    // If there is no intersection, return false
    return false;
}