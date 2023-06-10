#include <vector>
#include <map>
#include <algorithm>

typedef struct Triangle {
  int id;
  std::vector<int> vertex;
  std::map<std::vector<int>, int> neighbours;
} Triangle;

int ID = 0;

Triangle make_triangle(std::vector<int> P) {
  Triangle T;
  T.id = ID;

  for ( int i = 1; i < 4; i++ ) {
    T.vertex[i] = P[i];
  }
  sort(T.vertex.begin(), T.vertex.end());

  for ( int i = 1; i < 3; i++ ) {
    T.neighbours[std::vector{T.vertex[i], T.vertex[i+1]}] = 0; 
  }

  std::vector<int> edge{T.vertex[3], T.vertex[1]};
  sort(edge.begin(), edge.end());
  T.neighbours[edge] = 0; 

  return T;
}

std::vector<Triangle> triangles;

bool has_edge(Triangle T, std::vector<int> edge) {
  return T.neighbours.count(edge) != 0;
}

int triangulation(std::vector<int> P) {
  if ( P.size() == 3 ) {
    ID++;
    triangles[ID] = make_triangle(P);
    return ID;
  }

  std::vector<int> diagonal(find_diagonal(P));
  std::vector<std::vector<int>> split = split_in_edge(diagonal);

  int id1 = triangulation(split[0]);
  int id2 = triangulation(split[1]);

  sort(diagonal.begin(), diagonal.end());
  triangles[id1].neighbours[diagonal] = id2;
  triangles[id2].neighbours[diagonal] = id1;

  std::vector<int> border{P[1], P[P.size()]};
  sort(border.begin(), border.end());
  return (has_edge(triangles[id1], border) ? id1 : id2);
}
