#pragma once

#include "RigidBody.h"


 // Checks for intersection between two Polygon - shaped RigidBody objects.
 // polygonA The first body.
 // polygonB The second body.
 // outNormal Normal output (if there's an intersection).
 // outDepth Depth output (if there's an intersection).
 // return Whether there's an intersection.
bool DoesPolygonIntersectPolygon(RigidBody& polygonA, RigidBody& polygonB, Vector2f& outNormal, float& outDepth);

 // Checks for intersection between a Polygon-shaped RigidBody and a Circle-shaped RigidBody.
 // polygonA The Polygon body.
 // polygonB The Circle body.
 // outNormal Normal output (if there's an intersection).
 // outDepth Depth output (if there's an intersection).
 // return Whether there's an intersection.
bool DoesPolygonIntersectCircle(RigidBody& polygon, RigidBody& circle, Vector2f& outNormal, float& outDepth);


// Checks for intersection between two Circle-shaped RigidBody objects.
// polygonA The first body.
// polygonB The second body.
// outNormal Normal output (if there's an intersection).
// outDepth Depth output (if there's an intersection).
// return Whether there's an intersection.
bool DoesCircleIntersectCircle(RigidBody& circleA, RigidBody& circleB, Vector2f& outNormal, float& outDepth);


// Utility function for projecting the given polygon vertices onto the given axis and outputting the minimum
// and maximum values. Part of the Separating Axis Theorem (SAT).
//  pVertices The array of vertices to project.
//  vertexCount The number of vertices in the array.
// axis The axis to project onto.
 // outMin The minimum value projected onto the axis.
 // outMax The maximum value projected onto the axis.
void ProjectPolygonOnAxis(Vector2f* pVertices, size_t vertexCount, Vector2f axis, float& outMin, float& outMax);

 // Utility function for projecting the given circle onto the given axis and outputting the minimum and maximum
 // values. Part of the Separating Axis Theorem (SAT).
 // centre The centre of the circle.
 // radius The radius of the circle.
 // axis The axis to project onto.
 // outMin The minimum value projected onto the axis.
 // outMax The maximum value projected onto the axis.
void ProjectCircleOnAxis(Vector2f centre, float radius, Vector2f axis, float& outMin, float& outMax);


 // Finds the closest vertex in the given array to a given point.
 // point The point to find the closest vertex to.
 // pVertices The array of vertices to test.
 // vertexCount The number of vertices in the array.
 // return The index of the closest vertex.
int FindClosestVertex(Vector2f point, Vector2f* pVertices, size_t vertexCount);


 // Finds the mean average of the given vertices.
 // pVertices The array of vertices.
 // vertexCount The number of vertices in the array.
 // return The mean vertex.
Vector2f FindMeanAverage(Vector2f* pVertices, size_t vertexCount);


 // Resolves collision between two bodies.
 // bodyA The first body.
 // bodyB The second body.
 // normal Collision normal.
 // depth Collision depth.
void ResolveCollision(RigidBody& bodyA, RigidBody& bodyB, Vector2f normal, float depth);