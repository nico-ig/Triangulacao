#ifndef __EDGE__
#define __EDGE__

#include "point.h"

class Edge {
public:
  Point a, b;

  Point& operator[](int index);
  Point operator[](int index) const;
  Edge& operator=(const Edge& other);

  Edge();
  Edge(const Edge& other);
  Edge(const Point& p1, const Point& p2);
  Edge(const std::initializer_list<Point>& init_list);
};

#endif
