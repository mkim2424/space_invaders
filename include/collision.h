#ifndef __COLLISION_H__
#define __COLLISION_H__

#include <stdbool.h>
#include "list.h"
#include "vector.h"
#include "projection.h"
#include "list.h"


// Returns a normalized axis as a vector given an edge of a shape (two vertices)
Vector get_axis(Vector p1, Vector p2);

// Returns projection of a given shape to a given axis
Projection get_projection(List *shape, Vector axis);

// Determines if projection of two shapes onto all the axis of shape_primary
// overlaps
bool projections_overlap(List *shape_primary, List *shape_secondary);


/**
 * Determines whether two convex polygons intersect.
 * The polygons are given as lists of vertices in counterclockwise order.
 * There is an edge between each pair of consecutive vertices,
 * and one between the first vertex and the last vertex.
 *
 * @param shape1 the first shape
 * @param shape2 the second shape
 * @return whether the shapes are colliding
 */
bool find_collision(List *shape1, List *shape2);


#endif // #ifndef __COLLISION_H__
