#include <iostream>
#include <map>

#include "doctest.h"
#include "geometry.h"
#include "triangulation.h"

class TestTriangulation : protected Triangulation {
public:
    TestTriangulation(const Polygon& poly) : Triangulation(poly) {};
    using Triangulation::findDiagonal;
};

TEST_CASE("Create Triangulation") {
  std::cout << "Running: Crate Triangulation:";
  Geometry *geometry = Geometry::getInstance();
  
  SUBCASE("Polygon is clockwise") {
    std::cout << " [Polygon is clockwise]";
    Polygon poly({{1, 4}, {1, 20}, {15, 20}, {15, 4}});
    Triangulation T(poly);

    CHECK(T.polygon() == poly);
  }

  SUBCASE("Polygon is counterclockwise") {
    std::cout << " [Polygon is counterclockwise]";
    Polygon poly({{1, 1}, {3, 1}, {2, 2}});
    Triangulation T(poly);

    CHECK(geometry->orientation(poly) == Geometry::COUNTERCLOCKWISE);
    CHECK(geometry->orientation(T.polygon()) == Geometry::CLOCKWISE);
    
    geometry->makeClockwise(poly);
    CHECK(T.polygon() == poly);
  }

  std::cout << "\n";
}

TEST_CASE("Find diagonal") {
  std::cout << "Running: Find diagonal:";
 
  SUBCASE("Neighbors are vertices of the diagonal") {
    std::cout << " [Neighbors are vertices of the diagonal]";
    Polygon p({{1,1}, {2,4}, {1,6}, {2,7}, {3,5}, {4,5}, {4,6}, {5,4}, {3,4}});
    TestTriangulation T(p);

    Edge diagonal_expected = {{2,4}, {3,4}}; 
    Edge diagonal = T.findDiagonal(p);
    
    CHECK(diagonal == diagonal_expected);
  }
  
  SUBCASE("Diagonal is the leftmost vertex") {
    std::cout << " [Diagonal is the leftmost vertex]";
    Polygon p({{3,3}, {2,2}, {3,1}, {1,2}});
    TestTriangulation T(p);

    Edge diagonal_expected = {{1,2}, {2,2}}; 
    Edge diagonal = T.findDiagonal(p);

    CHECK(diagonal == diagonal_expected);
  }

  std::cout << "\n";
}

TEST_CASE("Create triangle") {
  std::cout << "Running: Create triangle\n";

  Point v0(1, 1);
  Point v1(2, 4);
  Point v2(3, 4);
  
  Polygon poly({v1, v2, v0});
  Triangle t(1, poly);

  std::vector<Edge> edges_expected({{v2,v0}, {v0,v1}, {v1,v2}});

  CHECK(t.id == 1);

  for ( size_t i = 1; i < t.neighbors.size(); i++ ) {
    Neighbor n = t.neighbors[i]; 
    CHECK(n.id == 0);
    CHECK(n.e == edges_expected[i-1]);
  }
}

TEST_CASE("Triangulation") {
  std::cout << "Running: Triangulation:";

  Point p1(3,3);
  Point p2(2,2);
  Point p3(3,1);
  Point p4(1,2);

  Triangle t1(1, {p1, p2, p4});
  t1.neighbors = {{.id = 2, .e = {p2,p4} }, 
                  {.id = 0, .e = {p4,p1} },
                  {.id = 0, .e = {p1,p2} }
                 };

  Triangle t2(2, {p2, p3, p4});
  t2.neighbors = {{.id = 0, .e = {p3,p4} }, 
                  {.id = 1, .e = {p4,p2} },
                  {.id = 0, .e = {p2,p3} }
                 };

  std::vector<Triangle> triangulation_expected;
  triangulation_expected.push_back(t1);
  triangulation_expected.push_back(t2);

  Polygon poly({p1, p2, p3, p4});
  Triangulation T(poly);
 
  SUBCASE("Triangulation size") {
    std::cout << " [Triangulation size]";
    CHECK(T.size() == 2);
  }

  SUBCASE("Check id") {
    std::cout << " [Check id]";
    for ( size_t i = 0; i < triangulation_expected.size(); i++ ) {
      Triangle t = T[i];
      Triangle t_expected = triangulation_expected[i];

      CHECK(t.id == t_expected.id);
    }
  }

  SUBCASE("Check vertices") {
    std::cout << " [Check vertices]";
    for ( size_t i = 0; i < triangulation_expected.size(); i++ ) {
      Triangle t = T[i];
      Triangle t_expected = triangulation_expected[i];

      for ( int j = 0; j < 3; j++ ) {
        CHECK(t.vertices[j] == t_expected.vertices[j]);
      }
    }
  }

  SUBCASE("Check neighbours") {
    std::cout << " [Check neighbours]";
    for ( size_t i = 0; i < triangulation_expected.size(); i++ ) {
      Triangle t = T[i];
      Triangle t_expected = triangulation_expected[i];

      for ( int k = 0; k < 3; k++ ) {
        Neighbor n = t.neighbors[k+1];
        Neighbor n_expected = t_expected.neighbors[k];

        CHECK(n.id == n_expected.id);
        CHECK(n.e == n_expected.e);
      }
    }
  }

  std::cout << "\n";
}
