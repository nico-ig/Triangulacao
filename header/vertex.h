#ifndef __VERTEX__
#define __VERTEX__

#include <vector>

class Vertex {
 private:
  int id;
  std::vector<int> p;

public:
  const int& x, y;

  Vertex();
  Vertex(Vertex const& other);
  Vertex(int const& x, int const& y);
  Vertex(int id, int const& x, int const& y);

  bool operator<(Vertex const& v);
  int& operator[](int index);
  const int& operator[](int index) const;
  Vertex& operator=(Vertex const& other);

  int getID();
  int size() const;
};

#endif
