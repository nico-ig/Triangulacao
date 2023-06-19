#include <iostream>
#include "doctest.h"
#include "figures.h"

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
