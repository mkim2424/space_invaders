#include "projection.h"

bool overlaps(Projection p1, Projection p2) {
    return !(p1.min > p2.max || p1.max < p2.min);
}
