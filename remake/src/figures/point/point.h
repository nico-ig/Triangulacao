#ifndef __POINT__
#define __POINT__

#include <vector>

class Point {
public:
  std::vector<int> p;
  int& x, y;
  Point& operator=(const Point& other);
  int& operator[](int index);
  int operator[](int index) const;

  Point();
  Point(const Point& other);
  Point(const int& x, const int& y);
  Point(const std::initializer_list<int>& init_list);

  int size() const;
};

#endif
