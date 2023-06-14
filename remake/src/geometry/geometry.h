#ifndef __GEOMETRY__
#define __GEOMETRY__

#include "figures.h"

class Geometry {
private:
  static Geometry* instance;
  Geometry();

public:
  enum Direction {
    COUNTERCLOCKWISE = -1,
    COLLINEAR = 0,
    CLOCKWISE = 1
  };
  static Geometry* getInstance();

  Polygon readPolygon();
  int findLeftmost(const Polygon& poly);
  int orientation(const Polygon& poly);
  void makeClockwise(Polygon& poly);
  bool edgeContainsCollinear(const Edge& ab, const Point& c);
  bool edgeIntersect(const Edge& ab, const Edge& cd);
  std::vector<Polygon> splitInEdge(const Polygon& poly, int a, int b);
  bool polygonContainsPoint(const Polygon& poly, const Point& a);
};

#endif
