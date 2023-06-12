#include "edge.h"

Edge::Edge() {
}

Edge::Edge(const Point& p1, const Point& p2) : a(p1), b(p2) {
}

Edge::Edge(const std::initializer_list<Point>& init_list) : 
  a(init_list.begin()[0]), b(init_list.begin()[1]) {
}

Point& Edge::operator[](int index) { 
  return index == 0 ? a : b; 
}

Edge& Edge::operator=(const Edge& other) {
  a = other.a;
  b = other.b;

  return *this;
}

