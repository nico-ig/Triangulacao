#ifndef __EDGE__
#define __EDGE__

#include "point.h"

class Edge {
public:
  Point a, b;
  Point& operator[](int index);
  Edge& operator=(const Edge& other);

  Edge();
  Edge(const Point& p1, const Point& p2);
  Edge(const std::initializer_list<Point>& init_list);
};

#endif
