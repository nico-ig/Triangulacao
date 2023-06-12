#include <iostream>
#include "doctest.h"
#include "polygon.h"

TEST_CASE("Create a polygon") {
  std::cout << "Running: Create a polygon:";
  SUBCASE("Create an empty polygon") {
    std::cout << " [Create an empty polygon]";

    Polygon polygon;
    CHECK(polygon.vertices.size() == 0);
    CHECK(polygon.edges.size() == 0);
  }

  SUBCASE("Create polygon from list"){
    std::cout << " [Create polygon from list]";
    Polygon polygon({{1, 4}});

    CHECK (polygon[0].x == 1); 
    CHECK (polygon[0].y == 4); 
  }

  std::cout << "\n";
}
