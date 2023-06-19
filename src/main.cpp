#include "geometry.h"
#include "triangulation.h"

int main() {
    Geometry *geometry = Geometry::getInstance();
    Polygon poly = geometry->readPolygon();
    Triangulation T(poly);
    T.print();
}
