#include <iostream>
#include "doctest.h"
#include "edge.h"

TEST_CASE("Create an empty edge") {
  std::cout << "Running: Create an empty edge\n";

  Edge edge;
  CHECK(edge[0].x == 0);
  CHECK(edge[0].y == 0);

  CHECK(edge[1].x == 0);
  CHECK(edge[1].y == 0);
}

