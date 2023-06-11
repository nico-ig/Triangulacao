#include <iostream>
#include "doctest.h"
#include "figures.h"

TEST_CASE("Initialization of figures") {
  std::cout << "Running: Initialization of figures\n";

  SUBCASE("Create a point") {
    std::cout << "\t Create a point:";

    SUBCASE(" Create an empty point") {
      std::cout << " [Create an empty point]";

      Point p;
      CHECK(p.x == 0);
      CHECK(p.y == 0);
    }

    std::cout << "\n";
  }

  SUBCASE("Create an edge") {
    std::cout << "\t Create a edge:";

    SUBCASE("Create an empty edge") {
      std::cout <<" [Create an empty edge]";

      Edge edge;
      CHECK(edge[0].x == 0);
      CHECK(edge[0].y == 0);

      CHECK(edge[1].x == 0);
      CHECK(edge[1].y == 0);
    }

    std::cout << "\n";
  }

  SUBCASE("Create a polygon") {
    std::cout << "\t Create a polygon:";

    SUBCASE("Create an empty polygon") {
      std::cout << " [Create an empty polygon]";

      Polygon polygon;
      CHECK(polygon.vertices.size() == 0);
      CHECK(polygon.edges.size() == 0);
    }

    std::cout << "\n";
  }

  std::cout << "\n";
}

