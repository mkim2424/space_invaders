#ifndef __PROJECTION_H__
#define __PROJECTION_H__

#include <stdbool.h>

typedef struct {
    double min;
    double max;
} Projection;


// Determines if Projections p1 and p2 overlaps
bool overlaps(Projection p1, Projection p2);

#endif // #ifndef __PROJECTION_H__
