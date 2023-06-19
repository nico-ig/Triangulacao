#include <iostream>
#include "figures.h"

bool operator==(const Point& lhs, const Point& rhs) {
  return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator!=(const Point& lhs, const Point& rhs) {
  return !(lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator==(const Edge& lhs, const Edge& rhs) {
  return (lhs.a==rhs.a && lhs.b==rhs.b) || (lhs.a==rhs.b && lhs.b==rhs.a);
}

bool operator==(const Polygon& lhs, const Polygon& rhs) {
  if ( lhs.size() != rhs.size() ) { 
    return false;
  }

  for ( int i = 0; i < lhs.size(); i++ ) {
    if ( lhs[i] != rhs[i] ) {
      return false;
    }
  }

  return true;
}

