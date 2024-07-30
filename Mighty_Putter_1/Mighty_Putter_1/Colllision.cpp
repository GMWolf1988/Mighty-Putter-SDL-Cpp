#include <limits>
#include "Collision.h"

// Function that checks if two polygons intersect and returns the normal vector of the minimum translation vector and the depth of the overlap
bool DoesPolygonIntersectPolygon(RigidBody& polygonA, RigidBody& polygonB, Vector2f& outNormal, float& outDepth)
{
    // Check if both objects are polygons
    if (polygonA.GetShape() != RigidBody::Shape::Polygon || polygonB.GetShape() != RigidBody::Shape::Polygon)
        return false;

    // Initialize output parameters
    outNormal = Vector2f();
    outDepth = std::numeric_limits<float>::max();

    // Loop over each edge of polygonA
    Vector2f* pVerticesA = polygonA.GetTransformedVertices();
    size_t vertexCountA = polygonA.GetVertexCount();
    Vector2f* pVerticesB = polygonB.GetTransformedVertices();
    size_t vertexCountB = polygonB.GetVertexCount();
    for (size_t i = 0; i < vertexCountA; ++i)
    {
        Vector2f vertex1 = pVerticesA[i];
        Vector2f vertex2 = pVerticesA[(i + 1) % vertexCountA];

        // Calculate the edge and axis
        Vector2f edge = vertex2 - vertex1;
        Vector2f axis = { -edge.y, edge.x };
        axis = axis.Normalised();

        // Project both polygons onto the axis and check for overlap
        float minA, maxA, minB, maxB;
        ProjectPolygonOnAxis(pVerticesA, vertexCountA, axis, minA, maxA);
        ProjectPolygonOnAxis(pVerticesB, vertexCountB, axis, minB, maxB);
        if (minA >= maxB || minB >= maxA)
            return false;

        // Update output parameters with axis and depth of overlap
        float axisDepth = std::min(maxB - minA, maxA - minB);
        if (axisDepth < outDepth)
        {
            outNormal = axis;
            outDepth = axisDepth;
        }
    }

    // Repeat process for each edge of polygonB
    for (size_t i = 0; i < vertexCountB; ++i)
    {
        Vector2f vertex1 = pVerticesB[i];
        Vector2f vertex2 = pVerticesB[(i + 1) % vertexCountB];

        // Calculate the edge and axis
        Vector2f edge = vertex2 - vertex1;
        Vector2f axis = { -edge.y, edge.x };
        axis = axis.Normalised();

        // Project both polygons onto the axis and check for overlap
        float minA, maxA, minB, maxB;
        ProjectPolygonOnAxis(pVerticesA, vertexCountA, axis, minA, maxA);
        ProjectPolygonOnAxis(pVerticesB, vertexCountB, axis, minB, maxB);
        if (minA >= maxB || minB >= maxA)
            return false;

        // Update output parameters with axis and depth of overlap
        float axisDepth = std::min(maxB - minA, maxA - minB);
        if (axisDepth < outDepth)
        {
            outNormal = axis;
            outDepth = axisDepth;
        }
    }

    // Return true to indicate that the polygons intersect
    return true;
}

bool DoesPolygonIntersectCircle(RigidBody& polygon, RigidBody& circle, Vector2f& outNormal, float& outDepth)
{
    // Check if both shapes are correct types
    if (polygon.GetShape() != RigidBody::Shape::Polygon || circle.GetShape() != RigidBody::Shape::Circle)
        return false;

    // Initialize output parameters
    outNormal = Vector2f();
    outDepth = std::numeric_limits<float>::max();

    // Initialize temporary variables for calculations
    Vector2f axis = Vector2f();
    float minA, maxA, minB, maxB;

    // Get vertices of polygon and center and radius of circle
    Vector2f* pVertices = polygon.GetTransformedVertices();
    size_t vertexCount = polygon.GetVertexCount();
    Vector2f circleCentre = circle.GetPosition();
    float circleRadius = circle.GetRadius();

    // Check collision for each edge of polygon
    for (int i = 0; i < vertexCount; i++)
    {
        Vector2f vertex1 = pVertices[i];
        Vector2f vertex2 = pVertices[(i + 1) % vertexCount];

        Vector2f edge = vertex2 - vertex1;
        Vector2f axis = { -edge.y, edge.x };
        axis = axis.Normalised();

        ProjectPolygonOnAxis(pVertices, vertexCount, axis, minA, maxA);
        ProjectCircleOnAxis(circleCentre, circleRadius, axis, minB, maxB);

        if (minA >= maxB || minB >= maxA)
        {
            return false;
        }

        float axisDepth = std::min(maxB - minA, maxA - minB);

        if (axisDepth < outDepth)
        {
            outNormal = axis;
            outDepth = axisDepth;
        }
    }

    // Check collision for closest vertex of polygon to circle center
    int closestIndex = FindClosestVertex(circleCentre, pVertices, vertexCount);
    Vector2f closestPoint = pVertices[closestIndex];

    axis = closestPoint - circleCentre;
    axis = axis.Normalised();

    ProjectPolygonOnAxis(pVertices, vertexCount, axis, minA, maxA);
    ProjectCircleOnAxis(circleCentre, circleRadius, axis, minB, maxB);

    if (minA >= maxB || minB >= maxA)
    {
        return false;
    }

    float axisDepth = std::min(maxB - minA, maxA - minB);

    if (axisDepth < outDepth)
    {
        outDepth = axisDepth;
        outNormal = axis;
    }

    // Check collision direction and flip normal if needed
    Vector2f polygonCentre = FindMeanAverage(pVertices, vertexCount);
    Vector2f direction = polygonCentre - circleCentre;

    if (direction.Dot(outNormal) < 0.f)
    {
        outNormal = -outNormal;
    }

    return true;
}

bool DoesCircleIntersectCircle(RigidBody& circleA, RigidBody& circleB, Vector2f& outNormal, float& outDepth)
{
    // Check if both objects are circles
    if (circleA.GetShape() != RigidBody::Shape::Circle || circleB.GetShape() != RigidBody::Shape::Circle)
        return false;

    // Initialize output variables
    outNormal = Vector2f();
    outDepth = 0.f;

    // Calculate the distance between the two circles and the sum of their radii
    float distance = circleA.GetPosition().DistanceTo(circleB.GetPosition());
    float radii = circleA.GetRadius() + circleB.GetRadius();

    // If the distance is greater than or equal to the sum of the radii, they do not intersect
    if (distance >= radii) return false;

    // Calculate the collision normal and depth
    outNormal = (circleB.GetPosition() - circleA.GetPosition()).Normalised();
    outDepth = radii - distance;

    return true;
}

// Project a polygon onto a given axis, returning the minimum and maximum values of the projection
void ProjectPolygonOnAxis(Vector2f* pVertices, size_t vertexCount, Vector2f axis, float& outMin, float& outMax)
{
    // Initialize outMin and outMax to their respective limits
    outMin = std::numeric_limits<float>::max();
    outMax = std::numeric_limits<float>::lowest();

    // Loop through all vertices of the polygon
    for (size_t i = 0; i < vertexCount; ++i)
    {
        // Get the current vertex and its projection onto the axis
        Vector2f vertex = pVertices[i];
        float projection = vertex.Dot(axis);

        // Update outMin and outMax if necessary
        if (projection < outMin) { outMin = projection; }
        if (projection > outMax) { outMax = projection; }
    }
}

void ProjectCircleOnAxis(Vector2f centre, float radius, Vector2f axis, float& outMin, float& outMax)
{
    // Calculate the direction of the axis and its scaled vector with the radius
    Vector2f direction = axis.Normalised();
    Vector2f directionAndRadius = direction * radius;

    // Calculate the two points where the circle intersects the axis
    Vector2f p1 = centre + directionAndRadius;
    Vector2f p2 = centre - directionAndRadius;

    // Project the two points onto the axis and return the minimum and maximum values
    outMin = p1.Dot(axis);
    outMax = p2.Dot(axis);

    // Swap the values if the minimum is greater than the maximum
    if (outMin > outMax)
    {
        float t = outMin;
        outMin = outMax;
        outMax = t;
    }
}

int FindClosestVertex(Vector2f point, Vector2f* pVertices, size_t vertexCount)
{
    // Find the closest vertex to the given point and return its index
    int result = -1;
    float minDistance = std::numeric_limits<float>::max();

    for (size_t i = 0; i < vertexCount; ++i)
    {
        Vector2f vertex = pVertices[i];
        float distance = vertex.DistanceTo(point);

        if (distance < minDistance)
        {
            minDistance = distance;
            result = i;
        }
    }

    return result;
}

Vector2f FindMeanAverage(Vector2f* pVertices, size_t vertexCount)
{
    // Calculate the mean average of the vertices and return it as a vector
    float sumX = 0.f;
    float sumY = 0.f;

    for (size_t i = 0; i < vertexCount; ++i)
    {
        Vector2f vertex = pVertices[i];
        sumX += vertex.x;
        sumY += vertex.y;
    }

    return { sumX / (float)vertexCount, sumY / (float)vertexCount };
}

void ResolveCollision(RigidBody& bodyA, RigidBody& bodyB, Vector2f normal, float depth)
{
    // Calculate the relative velocity between the two bodies
    Vector2f relativeVelocity = bodyB.GetLinearVelocity() - bodyA.GetLinearVelocity();

    // If the bodies are moving away from each other, there is no collision
    if (relativeVelocity.Dot(normal) > 0.f) return;

    // Calculate the impulse for changing velocity based on elasticity and mass
    float elasticity = std::min(bodyA.GetRestitution(), bodyB.GetRestitution());
    float j = -(1.f + elasticity) * relativeVelocity.Dot(normal);
    j /= bodyA.GetInverseMass() + bodyB.GetInverseMass();
    Vector2f impulse = normal * j;

    // Apply the impulse to the bodies if they're not static
    if (!bodyA.IsStatic()) bodyA.ChangeLinearVelocity(-(impulse * bodyA.GetInverseMass()));
    if (!bodyB.IsStatic()) bodyB.ChangeLinearVelocity(impulse * bodyB.GetInverseMass());
}