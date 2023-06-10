#ifndef __EDGE__
#define __EDGE__

#include <vector>
#include "vertex.h"

class Edge {
  private:
    std::vector<Vertex> e;
    
  public:
    Vertex& a, b;
    
    Edge(Vertex const& a, Vertex const& b);

    Vertex& operator[](int index);
    const Vertex& operator[](int index) const;

    /*
     * Calculates the orientation of the triangle made by the edge and a vertex
     * @return 0 if collinear, 1 if clockwise and -1 if counterclockwise.
     */
    int orientation(Vertex const& c);
    int scalarProduct(Vertex const& c);

    bool containsCollinear(Vertex const& c);
    bool intersect(Edge const& cd);
};

#endif
