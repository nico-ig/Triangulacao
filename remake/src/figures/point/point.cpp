#include "point.h"

Point::Point() : p(std::vector(2, 0)), x(p[0]), y(p[1]) {
}

Point::Point(const Point& other) : p(other.p), x(p[0]), y(p[1]) {
}

Point::Point(const int& x, const int& y) : p(2, 0), x(p[0]), y(p[1]) {
  this->x = p[0] = x;
  this->y = p[1] = y;
}

Point::Point(const std::initializer_list<int>& init_list) : 
  p(std::vector(2, 0)), x(p[0]), y(p[1]) {
  if ( init_list.size() < 2 ) { 
    return;
  }

  for ( size_t i = 0; i < init_list.size(); i++ ) {
    p[i] = init_list.begin()[i];
  }
  x = p[0];
  y = p[1]; 
}

Point& Point::operator=(const Point& other) {
  for ( int i = 0; i < other.size(); i++ ) {
     p[i] = other.p[i];
  }

  return *this;
}

int& Point::operator[](int index) {
  return p[index];
}

int Point::size() const {
  return p.size();
}

