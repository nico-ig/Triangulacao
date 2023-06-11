#include <iostream>
#include "figures.h"
#include <utility>

Point::Point() : p(std::make_pair(0, 0)), x(p.first), y(p.second) {}
Point::Point(const Point& other) : p(other.p), x(other.x), y(other.y) {}
Point::Point(const int& x, const int& y) : 
  p(std::make_pair(x, y)), x(p.first), y(p.second) {
}
Point& Point::operator=(const Point& other) {
  p = other.p;
  x = other.x;
  y = other.y;

  return *this;
}
bool operator==(const Point& lhs, const Point& rhs) {
  return (lhs.x == rhs.x && lhs.y == rhs.y);
}
bool operator!=(const Point& lhs, const Point& rhs) {
  return !(lhs.x == rhs.x && lhs.y == rhs.y);
}

Edge::Edge() {}
Edge::Edge(const Point& p1, const Point& p2) : a(p1), b(p2) {}
Edge::Edge(const std::initializer_list<Point>& init_list) : 
  a(*init_list.begin()), b(*(init_list.begin()+1)) {}
Point& Edge::operator[](int index) { 
  return index == 0 ? a : b; 
}
Edge& Edge::operator=(const Edge& other) {
  a = other.a;
  b = other.b;

  return *this;
}

Polygon::Polygon() {
}
Polygon::Polygon(const Polygon& poly) : 
  vertices(poly.vertices), edges(poly.edges) {
}
Polygon::Polygon(const std::initializer_list<Point>& init_list) : vertices(init_list) {
}
Point& Polygon::operator[](int index) { 
  return vertices[index];
}
const Point& Polygon::operator[](int index) const { 
  return vertices[index];
}
void Polygon::make_edges() {
  size_t i;
  for ( i = 0; i < vertices.size() - 1; i++ ) {
    edges.push_back(Edge({vertices[i], vertices[i+1]}));
  }
  edges.push_back(Edge({vertices[i], vertices[0]}));
}
int Polygon::size() const {
  return vertices.size();
}
void Polygon::push_back(const Point& p) {
  vertices.push_back(p);

  int last_edge = edges.size() - 1;
  if ( last_edge < 2 ) { return; }

  edges[last_edge] = Edge(vertices[last_edge], p);
  edges.push_back(Edge(p, vertices[0]));
}

bool operator==(const Polygon& lhs, const Polygon& rhs) {
  if ( lhs.size() != rhs.size() ) { 
    return false;
  }

  for ( int lhs_i = 0, rhs_i = 0; lhs_i < lhs.size(); lhs_i++, rhs_i++ ) {
    if ( lhs[lhs_i] != rhs[rhs_i] ) {
      return false;
    }
  }

  return true;
}
