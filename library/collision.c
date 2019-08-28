#include <stdlib.h>
#include <math.h>
#include "collision.h"

// gets the norm of the edge between vertices p1 and p2
Vector get_axis(Vector p1, Vector p2) {
    Vector norm_edge = vec_norm(vec_subtract(p2, p1));
    return vec_normalize(norm_edge);
}

Projection get_projection(List *shape, Vector axis) {
    double min = vec_dot(*(Vector *) list_get(shape, 0), axis);
    double max = min;

    for (size_t i = 1; i < list_size(shape); i++) {
        double p = vec_dot(*(Vector *) list_get(shape, i), axis);
        
        if (p < min) {
            min = p;
        } else if (p > max) {
            max = p;
        }
    }
    return (Projection) {.min = min, .max = max};
}

bool projections_overlap(List *shape_primary, List *shape_secondary) {
    size_t shape_size = list_size(shape_primary);

    for (size_t i = 0; i < shape_size; i++) {
        Vector v1 = *(Vector *) list_get(shape_primary, i);
        Vector v2 = *(Vector *) list_get(shape_primary, (i + 1) % shape_size);
        Vector axis = get_axis(v1, v2);
        Projection p1 = get_projection(shape_primary, axis);
        Projection p2 = get_projection(shape_secondary, axis);
        
        if (!overlaps(p1, p2)) {
            return false;
        }
    }

    return true;
}

bool find_collision(List *shape1, List *shape2) {
    return projections_overlap(shape1, shape2) &&
        projections_overlap(shape2, shape1);
}
