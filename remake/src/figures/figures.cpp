#include <iostream>
#include "figures.h"

bool operator==(const Point& lhs, const Point& rhs) {
  return (lhs.x == rhs.x && lhs.y == rhs.y);
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

bool operator!=(const Point& lhs, const Point& rhs) {
  return !(lhs.x == rhs.x && lhs.y == rhs.y);
}

