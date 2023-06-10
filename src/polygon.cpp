#include <vector>
#include <algorithm>
#include "polygon.h"

#define oo 112345

Polygon::Polygon(const Polygon& other) : 
  edges(other.edges), vertices(other.vertices) {}

Polygon::Polygon(std::vector<Vertex> const& vertices) : vertices(vertices) {
  this->vertices.insert(this->vertices.begin(), {});
  makeEdges();
}

void Polygon::makeEdges() {
  edges.clear();
  edges.insert(edges.begin(), {});
  edges.push_back({vertices[1], vertices[2]});
  for ( size_t i = 2; i < vertices.size() - 1; i++ ) {
    edges.push_back({vertices[i], vertices[i+1]});
  }
  edges.push_back({vertices[vertices.size()-1], vertices[1]});
}

int Polygon::indexPrevious(int const& current) {
  return current == 1 ? vertices.size() : current - 1;
}

int Polygon::indexNext(int const& current) {
  return current == (int)vertices.size() ? 1 : current + 1;
}

int Polygon::findIndex(Vertex const& v) {
  return std::find(vertices.begin(), vertices.end(), v) - vertices.begin() + 1;
}

bool Polygon::containsVertex(Vertex const& v) {
  int cnt = 0;
  Edge h {v, {v.x, oo}};
  for ( Edge e : edges ) {
    if ( h.intersect(e) ) cnt++;
  }

  return cnt % 2;
}

Vertex Polygon::findLeftmost() {
  Vertex min(2, oo);
  for ( Vertex v : vertices )
    min = v < min ? v : min;

  return min;
}

void Polygon::pushBackVertex(Vertex const& v) {
  vertices.push_back(v);
}

std::pair<Polygon, Polygon> Polygon::splitInEgde(Edge const& edge) {
  int a = findIndex(edge.a);
  int b = findIndex(edge.b);

  std::pair<Polygon, Polygon> split;
  split.first.pushBackVertex(Vertex{});
  split.second.pushBackVertex(Vertex{});

  for ( int i = a; i != b + 1; i = indexNext(i) )
    split.first.pushBackVertex(vertices[i]);

  for ( int i = b; i != a; i = indexNext(i) ) 
    split.second.pushBackVertex(vertices[i]);

  split.first.makeEdges();
  split.second.makeEdges();

  return split;
}
