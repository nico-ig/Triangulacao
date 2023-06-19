#ifndef __TRIANGULATION__
#define __TRIANGULATION__

#include <vector>
#include <map>
#include "figures.h"

class Neighbor {
  public:
    int id;
    Edge e;
};

class Triangle {
  public:
    int id;
    std::vector<Point> vertices;
    std::vector<Neighbor> neighbors;
  
    Triangle();
    Triangle(int id, const Polygon& poly);
};

class Triangulation {
  protected:
    int id;
    Polygon poly;
    std::vector<Triangle> T;

    Edge findDiagonal(const Polygon& poly);
    int findEdgeInNeighbors(const Triangle& t, const Edge& e);
    void addNeighbor(Triangle& t, int edge_id, int neighbor_id);
    int makeTriangulation(const Polygon& p, const Edge& diagonal_parent);

  public:
    Triangle& operator[](int index);
    Triangle operator[](int index) const;

    Triangulation(const Polygon& poly);

    int size();
    Polygon polygon();
    void print();
};

#endif
