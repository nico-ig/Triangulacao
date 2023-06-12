#include "polygon.h"

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

int Polygon::next(const int& i) const {
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
