#ifndef __GEOMETRY__
#define __GEOMETRY__

#include "figures.h"

class Geometry {
private:
  static Geometry* instance;
  Polygon* polygon;
  Geometry();

public:
  enum Direction {
    COUNTERCLOCKWISE = -1,
    COLLINEAR = 0,
    CLOCKWISE = 1
  };
  static Geometry* getInstance();

  void setPolygon(Polygon& poly);
  const Polygon& getPolygon();
  Polygon readPolygon();
  int orientation();
  void makeClockwise();
  std::vector<Polygon> splitInEdge(int a, int b);
};

#endif
