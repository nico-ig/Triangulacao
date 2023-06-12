#include <iostream>
#include <algorithm>
#include "geometry.h"

Geometry* Geometry::instance = new Geometry();

Geometry::Geometry() : polygon(nullptr) {}

Geometry* Geometry::getInstance() {
  return instance;
}

void Geometry::setPolygon(Polygon& poly) {
  polygon = &poly;
}

const Polygon& Geometry::getPolygon() {
  return *polygon;  
}

Polygon Geometry::readPolygon() {
  Polygon polygon;
  int n;
  std::cin >> n;

  int x, y;
  while ( n-- ) {
    std::cin >> x >> y;
    polygon.push_back(Point(x, y));
  }

  return polygon;
}

int Geometry::orientation() {
  const Point a = (*polygon)[0];
  const Point b = (*polygon)[1];
  const Point c = (*polygon)[2];

  int product = (b.y-a.y)*(c.x-b.x) - (b.x-a.x)*(c.y-b.y);

  if ( product == 0 ) {
    return Geometry::COLLINEAR;
  }
  if ( product > 0 ) {
    return Geometry::CLOCKWISE;
  }
  else {
    return Geometry::COUNTERCLOCKWISE;
  }
}

void Geometry::makeClockwise() {
  std::reverse((*polygon).begin(), (*polygon).end());
}

std::vector<Polygon> Geometry::splitInEdge(int a, int b) {
  std::vector<Polygon> split(2);

  split[0].push_back((*polygon)[a]);
  split[0].push_back((*polygon)[b]);
  for ( int i = polygon->next(b); i != a; i = polygon->next(i) ) {
    split[0].push_back((*polygon)[i]);
  }

  for ( int i = a; i != polygon->next(b); i = polygon->next(i) ) {
    split[1].push_back((*polygon)[i]);
  }

  for ( int i = 0; i < 2; i++ ) {
    split[i].make_edges();
  }

  return split;
}

