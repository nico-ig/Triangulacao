#include <iostream>
#include <algorithm>
#include "geometry.h"

Geometry* Geometry::instance = new Geometry();

Geometry::Geometry() {}

Geometry* Geometry::getInstance() {
  return instance;
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

int Geometry::orientation(const Polygon& poly) {
  const Point a = poly[0];
  const Point b = poly[1];
  const Point c = poly[2];

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

void Geometry::makeClockwise(Polygon& poly) {
  std::reverse(poly.begin(), poly.end());
}

std::vector<Polygon> Geometry::splitInEdge(const Polygon& poly, int a, int b) {
  std::vector<Polygon> split(2);

  split[0].push_back(poly[a]);
  split[0].push_back(poly[b]);
  for ( int i = poly.next(b); i != a; i = poly.next(i) ) {
    split[0].push_back(poly[i]);
  }

  for ( int i = a; i != poly.next(b); i = poly.next(i) ) {
    split[1].push_back(poly[i]);
  }

  for ( int i = 0; i < 2; i++ ) {
    split[i].make_edges();
  }

  return split;
}

