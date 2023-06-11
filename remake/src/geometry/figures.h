#ifndef __FIGURES__
#define __FIGURES__

#include <vector>
#include <utility>

class Point {
public:
  std::pair<int, int> p;
  int& x, y;
  Point& operator=(const Point& other);

  Point();
  Point(const Point& other);
  Point(const int& x, const int& y);
};

class Edge {
public:
  Point a, b;
  Point& operator[](int index);
  Edge& operator=(const Edge& other);

  Edge();
  Edge(const Point& p1, const Point& p2);
  Edge(const std::initializer_list<Point>& init_list);
};

class Polygon {
public:
  std::vector<Point> vertices;
  std::vector<Edge> edges;

  Point& operator[](int index);
  const Point& operator[](int index) const;

  Polygon();
  Polygon(const Polygon& poly);
  Polygon(const std::initializer_list<Point>& init_list);

  int size() const;
  void make_edges();
  void push_back(const Point& p);
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);

bool operator==(const Polygon& lhs, const Polygon& rhs);
#endif
