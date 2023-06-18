#ifndef __FIGURES__
#define __FIGURES__

#include "point.h"
#include "edge.h"
#include "polygon.h"

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);

bool operator==(const Edge& lhs, const Edge& rhs);
bool operator==(const Polygon& lhs, const Polygon& rhs);

#endif
