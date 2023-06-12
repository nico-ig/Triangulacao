#include <iostream>
#include "figures.h"
#include <utility>

Point::Point() : p(std::vector(2, 0)), x(p[0]), y(p[1]) {}
Point::Point(const Point& other) : p(other.p), x(p[0]), y(p[1]) {}
Point::Point(const int& x, const int& y) : p(2, 0), x(p[0]), y(p[1]) {
  this->x = p[0] = x;
  this->y = p[1] = y;
}
Point::Point(const std::initializer_list<int>& init_list) : 
  p(std::vector(2, 0)), x(p[0]), y(p[1]) {
  if ( init_list.size() < 2 ) { 
    return;
  }

  for ( size_t i = 0; i < init_list.size(); i++ ) {
    p[i] = init_list.begin()[i];
  }
  x = p[0];
  y = p[1]; 
}
Point& Point::operator=(const Point& other) {
  for ( int i = 0; i < other.size(); i++ ) {
     p[i] = other.p[i];
  }

  return *this;
}
int& Point::operator[](int index) {
  return p[index];
}
int Point::size() const {
  return p.size();
}

Edge::Edge() {}
Edge::Edge(const Point& p1, const Point& p2) : a(p1), b(p2) {}
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

Polygon::Polygon() {
}
Polygon::Polygon(const Polygon& poly) : 
  vertices(poly.vertices), edges(poly.edges) {
}
Polygon::Polygon(const std::initializer_list<Point>& init_list) : vertices(init_list){
}
Point& Polygon::operator[](int index) { 
  return vertices[index];
}
const Point& Polygon::operator[](int index) const { 
  return vertices[index];
}
std::vector<Point>::iterator Polygon::begin() {
  return vertices.begin();
}
std::vector<Point>::iterator Polygon::end() {
  return vertices.end();
}
int Polygon::next(const int& i) {
  return (i == (int)vertices.size() - 1)? 0 : i + 1;
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

bool operator==(const Point& lhs, const Point& rhs) {
  return (lhs.x == rhs.x && lhs.y == rhs.y);
}
bool operator!=(const Point& lhs, const Point& rhs) {
  return !(lhs.x == rhs.x && lhs.y == rhs.y);
}
bool operator==(const Polygon& lhs, const Polygon& rhs) {
  if ( lhs.size() != rhs.size() ) { 
    return false;
  }

  for ( int i = 0; i < lhs.size(); i++ ) {
    if ( lhs[i] != rhs[i] ) {
      return false;
    }
  }

  return true;
}
