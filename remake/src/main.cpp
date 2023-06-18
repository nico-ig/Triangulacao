#include "triangulation.h"

int main() {
    #if CCW
        Polygon poly({{15, 4}, {15, 20}, {1, 20}, {1, 4}});
    #else
        Polygon poly({{1, 4}, {1, 20}, {15, 20}, {15, 4}});
    #endif

    Triangulation T(poly);
    T.print();
}
