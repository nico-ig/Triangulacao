#include <iostream>
#include <sstream>
#include "doctest.h"
#include "geometry.h"

static std::streambuf* originalCin = std::cin.rdbuf();

void redirectCin(std::istringstream& mockInput) {
  std::cin.rdbuf(mockInput.rdbuf());
}

void restoreCin() {
  std::cin.rdbuf(originalCin);
}

TEST_CASE("Geometry Singleton") {
  std::cout << "Running: Geometry Singleton:";

  SUBCASE("Has only one instance") {
    std::cout << " [Has only one instance]";
    Geometry *geometry1 = Geometry::getInstance();
    Geometry *geometry2 = Geometry::getInstance();
    
    CHECK(geometry1 == geometry2);
  }

  std::cout << "\n";
}

TEST_CASE("Geometry Read Polygon") {
  std::cout << "Running: Geometry Read Polygon:";

  SUBCASE("Read empty polygon") {
    std::cout << " [Read empty polygon]";
    Geometry *geometry = Geometry::getInstance();

    std::istringstream mockInput("0");
    redirectCin(mockInput);
    Polygon polygon(geometry->readPolygon());
    restoreCin();

    CHECK(polygon.size() == 0);
  }

  SUBCASE("Read filled polygon") {
    std::cout << " [Read filled polygon]";
    Geometry *geometry = Geometry::getInstance();

    Polygon mockPolygon({{1, 4}, {1, 20}, {15, 20}, {15, 4}});
    std::istringstream mockInput("4\n1 4\n1 20\n15 20\n15 4");

    redirectCin(mockInput);
    Polygon polygon(geometry->readPolygon());
    restoreCin();

    CHECK(polygon == mockPolygon);
  }
  std::cout << "\n";
}

TEST_CASE("Orientation") {
  std::cout << "Running: Polygon orientation:";
  Geometry *geometry = Geometry::getInstance();

  SUBCASE("Collinear") {
    std::cout << " [Collinear]";

    Polygon p({{1, 1}, {1, 2}, {1, 3}});
    int ori = geometry->orientation(p);
    
    CHECK(ori == Geometry::COLLINEAR);
  }

  SUBCASE("Clockwise") {
    std::cout << " [Clockwise]";
    Polygon p({{1, 1}, {2, 2}, {3, 1}});
    int ori = geometry->orientation(p);
    
    CHECK(ori == Geometry::CLOCKWISE);
  }

  SUBCASE("CounterClockwise") {
    std::cout << " [CounterClockwise]";
    Polygon p({{1, 1}, {3, 1}, {2, 2}});
    int ori = geometry->orientation(p);
    
    CHECK(ori == Geometry::COUNTERCLOCKWISE);

  }
  std::cout << "\n";
}

TEST_CASE("Make polygon clockwise") {
  std::cout << "Running: Make polygon clockwise\n";
  Geometry *geometry = Geometry::getInstance();

  Polygon p({{1, 1}, {3, 1}, {2, 2}});
  geometry->makeClockwise(p);

  int ori = geometry->orientation(p);
  CHECK(ori == Geometry::CLOCKWISE);
}

TEST_CASE("Intersect") {
  std::cout << "Running: Edge intersect:";
  Geometry *geometry = Geometry::getInstance();
  Edge h({1,2}, {5,2});

  SUBCASE("Intersect normal") {
    std::cout << " [normal]";
    Edge e({2,1}, {2,4});
    CHECK(geometry->edgeIntersect(h, e) == true);
  }

  SUBCASE("Intersect collinear") {
    std::cout << " [collinear]";
    Edge e({2,2}, {7,2});
    CHECK(geometry->edgeIntersect(h, e) == true);
  }

  SUBCASE("Intersect one vertice belongs to the other edge") {
    std::cout << " [one vertice belongs to the other edge]";
    Edge e({1,1}, {1,4});
    CHECK(geometry->edgeIntersect(h, e) == true);
  }
  
  SUBCASE("Dont intersect") {
    std::cout << " [dont intersect]";
    Edge e({6,1}, {6,4});
    CHECK(geometry->edgeIntersect(h, e) == false);
  }

  std::cout << "\n";
}

TEST_CASE("Split polygon in two") {
  std::cout << "Running: Split polygon in two\n";
  Geometry *geometry = Geometry::getInstance();
  
  std::vector<Polygon> split_expected;
  split_expected.push_back({{2,1}, {3,4}, {1,1}});
  split_expected.push_back({{2,1}, {1,6}, {2,7}, {3,5}, {4,5}, {4,6}, {5,4} ,{3,4}});
  
  Polygon p({{1,1}, {2,1}, {1,6}, {2,7}, {3,5}, {4,5}, {4,6}, {5,4}, {3,4}});
  std::vector<Polygon> split = geometry->splitInEdge(p, {{2,1},{3,4}});

  for ( int i = 0; i < 2; i++ ) {
    for ( int j = 0; j < split_expected[i].size(); j++ ) {
      CHECK(split[i][j] == split_expected[i][j]);
    }
  }
}

TEST_CASE("Polygon contains point") {
  std::cout << "Running: Polygon contains point:";

  Polygon p({{1,1}, {2,1}, {1,6}, {2,7}, {3,5}, {4,5}, {4,6}, {5,4}, {3,4}});
  Geometry *geometry = Geometry::getInstance();
  
  SUBCASE("Contains in middle") {
    std::cout << " [Contains in middle]";
    CHECK(geometry->polygonContainsPoint(p, {2,6}) == true);
  }

  SUBCASE("Contains in edge") {
    std::cout << " [Contains in edge]";
    CHECK(geometry->polygonContainsPoint(p, {4,4}) == true);
  }

  SUBCASE("Does not contains") {
    std::cout << " [Does not contains]";
    CHECK(geometry->polygonContainsPoint(p, {3,3}) == false);
  }

  std::cout << "\n";
}
