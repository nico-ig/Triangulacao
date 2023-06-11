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
  std::cout << "Running: Geometry Singleton\n";

  SUBCASE("Has only one instance") {
    std::cout << "\t Has only one instance\n";
    Geometry *geometry1 = Geometry::getInstance();
    Geometry *geometry2 = Geometry::getInstance();
    
    CHECK(geometry1 == geometry2);
  }

  std::cout << "\n";
}

TEST_CASE("Geometry Set Polygon") {
  std::cout << "Running: Geometry Set Polygon\n";

  SUBCASE("Set empty polygon correctly") {
    std::cout << "\t Set empty polygon correctly\n";

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
    geometry->readPolygon();
    restoreCin();

    //CHECK(polygon == mockPolygon);
  }

  std::cout << "\n";
}

