#ifndef __POLYGON__
#define __POLYGON__

#include <vector>
#include "point.h"
#include "edge.h"

class Polygon {
public:
  std::vector<Point> vertices;
  std::vector<Edge> edges;

  Point& operator[](int index);
  const Point& operator[](int index) const;

  Polygon();
  Polygon(const Polygon& poly);
  Polygon(const std::initializer_list<Point>& init_list);

  std::vector<Point>::iterator begin();
  std::vector<Point>::iterator end();

  int next(const int& i) const;
  int previous(const int& i) const;
  int leftMost() const;
  int size() const;
  void make_edges();
  void push_back(const Point& p);
};

#endif
