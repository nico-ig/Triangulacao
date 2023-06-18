#include <iostream>
#include <algorithm>
#include "geometry.h"

#define oo 112345

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

int Geometry::findLeftmost(const Polygon& poly) {
  int min = 0;
  for ( int i = 1; i < poly.size(); i++ ) 
    min = poly[i].x < poly[min].x ? i : min;

  return min;
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

int findPoint(const std::vector<Point>& v, const Point& a) {
  auto it = find(v.begin(), v.end(), a);
  return it - v.begin();
}

bool Geometry::edgeContainsCollinear(const Edge& ab, const Point& c) {
  Point a = ab[0];
  Point b = ab[1];

  for ( int i = 0; i < c.size(); i++ ) {
    int max = std::max(a[i], b[i]);
    int min = std::min(a[i], b[i]);
    if ( (c[i] > max) || (c[i] < min) ) {
      return false;
    }
  }

  return true;
}

bool Geometry::edgeIntersect(const Edge& ab, const Edge& cd) {
  Point a = ab[0];
  Point b = ab[1];
  Point c = cd[0];
  Point d = cd[1];

  int o_abc = orientation({a,b,c});
  int o_abd = orientation({a,b,d});
  int o_cda = orientation({c,d,a});
  int o_cdb = orientation({c,d,b});

  if ( (o_abc != o_abd) && (o_cda != o_cdb) ) return true;
  if ( (o_abc!=0) || (o_abd!=0) || (o_cda!=0) || (o_cdb!=0) ) return false;

  return edgeContainsCollinear(ab, c) || edgeContainsCollinear(ab, d);
}

std::vector<Polygon> Geometry::splitInEdge(const Polygon& poly, const Edge& e) {
  std::vector<Polygon> split(2);
  int a = findPoint(poly.vertices, e.a);
  int b = findPoint(poly.vertices, e.b);

  split[0].push_back(poly[a]);
  split[0].push_back(poly[b]);
  for ( int i = poly.next(b); i != a; i = poly.next(i) ) {
    split[0].push_back(poly[i]);
  }

  for ( int i = a; i != poly.next(b); i = poly.next(i) ) {
    split[1].push_back(poly[i]);
  }

  for ( int i = 0; i < e.a.size(); i++ ) {
    split[i].make_edges();
  }

  return split;
}

bool Geometry::polygonContainsPoint(const Polygon& poly, const Point& a) {
  int cnt = 0;

  Edge h {a, {oo, a.y}};
  for ( Edge e : poly.edges ) {
    if ( edgeIntersect(h, e) ) {
      if ( orientation({e.a, a, e.b}) == COLLINEAR ) {
        return edgeContainsCollinear(e, a); 
      }

      cnt++;
    }
  }

  return cnt % 2;
}
