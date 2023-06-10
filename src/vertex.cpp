#include "vertex.h"

Vertex::Vertex() : p({0, 0}), x(p[0]), y(p[1]) {}

Vertex::Vertex(Vertex const& other) : 
p({other.x, other.y}), x(p[0]), y(p[1]) {}

Vertex::Vertex(int const& x, int const& y) :
p({x,y}), x(p[0]), y(p[1]) {}

Vertex::Vertex(int id, int const& x, int const& y) :
id(id), p({x,y}), x(p[0]), y(p[1]) {}

bool Vertex::operator<(Vertex const& v) {
  return x < v.x ? true : (x > v.x) ? y < v.y : false;
}

int& Vertex::operator[](int index) {
  return p[index];
}

const int& Vertex::operator[](int index) const {
  return p[index];
}

Vertex& Vertex::operator=(Vertex const& other) {
  id = other.id;
  p = other.p;
  return *this;
}

int Vertex::getID() { return id; }
int Vertex::size() const { return p.size(); }
