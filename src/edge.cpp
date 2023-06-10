#include "edge.h"

Edge::Edge(Vertex const& a, Vertex const& b) :
e({a, b}), a(e[0]), b(e[1]) {}

Vertex& Edge::operator[](int index) {
  return e[index];
}

const Vertex& Edge::operator[](int index) const {
  return e[index];
}

int Edge::scalarProduct(Vertex const& c) {
  int scalar_product = 0;
  for ( int i = 0; i < c.size(); i++ ) 
    scalar_product += (b[i] - a[i]) * (c[i] - a[i]);

  return scalar_product;
}

int Edge::orientation(Vertex const& c) {
  int scalar_product = scalarProduct(c);
  return scalar_product > 0 ? 1 : (scalar_product < 0) ? 1 : 0;
}

bool Edge::containsCollinear(Vertex const& c) {
  for ( int i = 0; i < c.size(); i++ ) {
    if ( (a[i] > c[i]) || (b[i] < c[i]) ) return false;
  }

  return true;
}

bool Edge::intersect(Edge const& cd) {
  Vertex c = cd[0];
  Vertex d = cd[1];

  int o_abc = orientation(c);
  int o_abd = orientation(d);
  int o_cda = orientation(a);
  int o_cdb = orientation(b);

  if ( (o_abc != o_abd) && (o_cda != o_cdb) ) return true;
  if ( (o_abc!=0) || (o_abd!=0) || (o_cda!=0) || (o_cdb!=0) ) return false;
  return containsCollinear(c)|| containsCollinear(d);
}
