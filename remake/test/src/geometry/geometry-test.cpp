#include "doctest.h"
#include "geometry.h"

TEST_CASE("Geometry Singleton") {
  SUBCASE("Has only one instance") {
    Geometry *geometry1 = Geometry::getInstance();
    Geometry *geometry2 = Geometry::getInstance();
    
    CHECK(geometry1 == geometry2);
  }
}
