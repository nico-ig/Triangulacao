#include <iostream>
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
