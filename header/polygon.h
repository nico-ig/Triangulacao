#ifndef __POLYGON__
#define __POLYGON__

#include <vector>
#include "vertex.h"
#include "edge.h"

class Polygon {
  private:
    std::vector<Edge> edges;
    std::vector<Vertex> vertices;

  public:
    Polygon();
    Polygon(const Polygon& other);
    Polygon(std::vector<Vertex> const& vertices);

    void makeEdges();
    int indexPrevious(int const& current);
    int indexNext(int const& current);
    int findIndex(Vertex const& v);
    bool containsVertex(Vertex const& v);
    Vertex findLeftmost();
    void pushBackVertex(Vertex const& v);
    std::pair<Polygon, Polygon> splitInEgde(Edge const& edge);
};

#endif
