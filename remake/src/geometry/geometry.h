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
  int orientation(const Polygon& poly);
  void makeClockwise(Polygon& poly);
  std::vector<Polygon> splitInEdge(const Polygon& poly, int a, int b);
};

#endif
