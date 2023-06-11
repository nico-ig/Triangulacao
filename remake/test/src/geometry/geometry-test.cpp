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

TEST_CASE("Geometry Set Polygon") {
  std::cout << "Running: Geometry Set Polygon:";

  SUBCASE("Set empty polygon correctly") {
    std::cout << " [Set empty polygon correctly]";

    Geometry *geometry = Geometry::getInstance();
    Polygon polygon;
    
    geometry->setPolygon(polygon);
    CHECK(geometry->getPolygon() == polygon);
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
    geometry->setPolygon(p);
    int ori = geometry->orientation();
    
    CHECK(ori == Geometry::COLLINEAR);
  }

  SUBCASE("Clockwise") {
    std::cout << " [Clockwise]";
    Polygon p({{1, 1}, {2, 2}, {3, 1}});
    geometry->setPolygon(p);
    int ori = geometry->orientation();
    
    CHECK(ori == Geometry::CLOCKWISE);
  }

  SUBCASE("CounterClockwise") {
    std::cout << " [CounterClockwise]";
    Polygon p({{1, 1}, {3, 1}, {2, 2}});
    geometry->setPolygon(p);
    int ori = geometry->orientation();
    
    CHECK(ori == Geometry::COUNTERCLOCKWISE);

  }
  std::cout << "\n";
}

TEST_CASE("Make polygon clockwise") {
  std::cout << "Running: Make polygon clockwise\n";
  Geometry *geometry = Geometry::getInstance();

  Polygon p({{1, 1}, {3, 1}, {2, 2}});
  geometry->setPolygon(p);
  geometry->makeClockwise();

  int ori = geometry->orientation();
  CHECK(ori == Geometry::CLOCKWISE);
}

