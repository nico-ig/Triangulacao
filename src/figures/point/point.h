#ifndef __POINT__
#define __POINT__

#include <vector>

class Point {
public:
  int id;
  std::vector<int> p;
  int& x; int& y;
  Point& operator=(const Point& other);
  bool operator<(Point const& v) const;
  int& operator[](int index);
  int operator[](int index) const;

  Point();
  Point(const Point& other);
  Point(const int& x, const int& y);
  Point(int id, const int& x, const int& y);
  Point(const std::initializer_list<int>& init_list);

  int size() const;
};

#endif
