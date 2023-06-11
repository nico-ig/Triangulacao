#ifndef __GEOMETRY__
#define __GEOMETRY__

#include "figures.h"

class Geometry {
private:
  static Geometry* instance;
  Polygon* polygon;
  Geometry();

public:
  static Geometry* getInstance();
  void setPolygon(Polygon& poly);
  const Polygon& getPolygon();
  Polygon readPolygon();
};

#endif
