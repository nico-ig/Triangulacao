#ifndef __GEOMETRY__
#define __GEOMETRY__

#include "geometry.h"

Geometry* Geometry::instance = new Geometry();

Geometry* Geometry::getInstance() {
  return instance;
}
#endif
