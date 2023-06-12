#include <iostream>
#include "doctest.h"
#include "point.h"

TEST_CASE("Create a point") {
  std::cout << "Running: Create an empty point\n";

  Point p;
  CHECK(p.x == 0);
  CHECK(p.y == 0);
}
