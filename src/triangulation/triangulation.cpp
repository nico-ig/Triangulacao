#include <iostream>
#include <algorithm>
#include "geometry.h"
#include "triangulation.h"

#define oo 112345

Triangle::Triangle() {
}

Triangle::Triangle(int id, const Polygon& poly) : id(id), vertices(poly.vertices) {
  neighbors.resize(4);

  sort(vertices.begin(), vertices.end(), 
       [](const Point& p1, const Point& p2) { return p1.id < p2.id; }
      );
  
  for ( int i = 0; i < 3; i++ ) {
    int next = (i+1) % 3;
    int previous = (i+2) % 3;
    Neighbor neighbor{ .id = 0, .e = {vertices[next], vertices[previous]} };
    neighbors[i+1] = neighbor;
  }
}

Triangulation::Triangulation(const Polygon& poly) : poly(poly) {
  Geometry *geometry = Geometry::getInstance();

  if ( geometry->orientation(this->poly) != Geometry::CLOCKWISE ) {
    geometry->makeClockwise(this->poly); }

  id = 0;
  makeTriangulation(this->poly, {});
}

Polygon Triangulation::polygon() {
  return poly;
}

Triangle& Triangulation::operator[](int index) {
  return T[index];
}

Triangle Triangulation::operator[](int index) const {
  return T[index];
}

int Triangulation::size() {
  return T.size();
}

void Triangulation::print() {
  std::cout << poly.size() << "\n";

  for ( int i = 0; i < poly.size(); i++ ) {
    std::cout << poly[i].x << " " << poly[i].y << "\n";
  }

  std::cout << T.size() << "\n";
  
  for ( size_t i = 0; i < T.size(); i++ ) {
    Triangle t = T[i];

    std::vector<Point> vertices = t.vertices;
    std::cout << vertices[0].id;
    for ( size_t j = 1; j < vertices.size(); j++ ) {
      std::cout << " " << vertices[j].id; 
    }

    std::vector<Neighbor> n = t.neighbors;
    std::cout << " " << n[1].id; 
    for ( size_t k = 2; k < n.size(); k++ ) {
      std::cout << " " << n[k].id; 
    }

    std::cout << "\n";
  }
}

int Triangulation::findEdgeInNeighbors(const Triangle& t, const Edge& e) {
  for ( int i = 1; i < 4; i++ ) {
    Neighbor n = t.neighbors[i];
    if ( n.e == e ) {
      return i;
    }
  }

  return 0;
}

void Triangulation::addNeighbor(Triangle& t, int edge_id, int neighbor_id) {
  t.neighbors[edge_id].id = neighbor_id; 
}

Edge Triangulation::findDiagonal(const Polygon& poly) {
  Geometry *geometry = Geometry::getInstance();

  int leftmost = geometry->findLeftmost(poly);
  int next = poly.next(leftmost);
  int previous = poly.previous(leftmost);

  Point pLeftmost = poly[leftmost];
  Point pNext = poly[next];
  Point pPrevious = poly[previous];
  
  Polygon ear({pLeftmost, pNext, pPrevious});

  Point closest_to_leftmost({oo, 0});

  for ( Point v : poly.vertices ) {
    if ( (v == pLeftmost) || (v == pPrevious) || (v == pNext) ) {
      continue;
    }

    if ( geometry->polygonContainsPoint(ear, v) ) {
      closest_to_leftmost = v < closest_to_leftmost ? v : closest_to_leftmost;
    }
  }

  Edge diagonal;
  if ( closest_to_leftmost != Point({oo, 0})) {
    diagonal = {closest_to_leftmost, pLeftmost};
  }
  else {
    diagonal = {pNext, pPrevious}; 
  }

  return diagonal;
}

int Triangulation::makeTriangulation(const Polygon& poly, const Edge& diagonal_parent) {
  Geometry *geometry = Geometry::getInstance();

  if (poly.size() == 3) {
    id++;
    T.push_back({id, poly});
    return id;
  }

  Edge diagonal = findDiagonal(poly);
  std::vector<Polygon> split = geometry->splitInEdge(poly, diagonal);

  std::vector<int> split_id(2);
  for ( int i = 0; i < 2; i++ ) { 
    split_id[i] = makeTriangulation(split[i], diagonal);
  }

  for ( int i = 0; i < 2; i++ ) {
    int triangle_id = split_id[i];

    Triangle& t = T[triangle_id - 1];
    int edge_id = findEdgeInNeighbors(t, diagonal);

    int neighbor_id = !i;
    addNeighbor(t, edge_id, split_id[neighbor_id]);
  }

  return findEdgeInNeighbors(T[split_id[0]-1], diagonal_parent) != 0 ? split_id[0] : split_id[1];
}
