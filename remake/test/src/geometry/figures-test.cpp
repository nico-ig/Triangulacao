#include <iostream>
#include "doctest.h"
#include "figures.h"

TEST_CASE("Initialization of figures") {
  std::cout << "Running: Initialization of figures:";

  SUBCASE("Create a point") {
    SUBCASE(" Create an empty point") {
      std::cout << " [Create an empty point]";

      Point p;
      CHECK(p.x == 0);
      CHECK(p.y == 0);
    }
  }

  SUBCASE("Create an edge") {
    SUBCASE("Create an empty edge") {
      std::cout <<" [Create an empty edge]";

      Edge edge;
      CHECK(edge[0].x == 0);
      CHECK(edge[0].y == 0);

      CHECK(edge[1].x == 0);
      CHECK(edge[1].y == 0);
    }
  }

  SUBCASE("Create a polygon") {
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
  }
  std::cout << "\n";
}

TEST_CASE("Operators overloading") {
  std::cout << "Running: Operators overloading:";
  SUBCASE("Polygon ==") {
    std::cout << " [Polygon ==]";

    Polygon p1({{1, 1}, {2, 2}, {3, 3}});
    Polygon p2({{1, 1}, {2, 2}, {3, 3}});
    Polygon p3({{1, 1}, {2, 2}, {3, 2}});
    Polygon p4({{1, 1}, {2, 2}});
    
    CHECK (p1 == p2);
    CHECK (!(p1 == p3));
    CHECK (!(p1 == p4));
  }

  std::cout << "\n";
}
