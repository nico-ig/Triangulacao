#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include "doctest.h"
#include "utils-files.h"
#include "triangulation.h"
#include "geometry.h"

namespace fs = std::filesystem;


Polygon readPolygonFile(fs::path file_path) {
  Geometry *geometry = Geometry::getInstance();
  std::ifstream input_file(file_path);
  redirectCin(input_file);

  Polygon polygon(geometry->readPolygon());

  restoreCin();
  input_file.close();
  return polygon;
}

void createOutFile(Triangulation T, fs::path file_path) {
  std::ofstream input_file(file_path);
  redirectCout(input_file);

  T.print();

  restoreCout();
  input_file.close();
}

bool compareFiles(fs::path sol_path, fs::path out_path) {
  std::ifstream sol(sol_path);
  std::ifstream out(out_path);

  std::stringstream buffer_sol;
  buffer_sol << sol.rdbuf();

  std::stringstream buffer_out;
  buffer_out << out.rdbuf();

  return buffer_sol.str() == buffer_out.str();
}

void printDiff(fs::path sol_path, fs::path out_path) {
  std::cout << "\n";
  std::string sol_filename = sol_path.c_str();
  std::string out_filename = out_path.c_str();

  std::string command = "diff --color=always -y -W 80 " + sol_filename + " " + out_filename;
  system(command.c_str());
}

TEST_CASE("Triangulate polygons") {
  std::cout << "Running: Triangulate Polygons:";

  std::string dir_path = "./polygon-cases";
  for (const auto& entry : fs::directory_iterator(dir_path)) {

    fs::path path = entry.path();
    fs::path file_in_path = path;
    fs::path file_out_path = path.replace_extension(".out");
    fs::path file_sol_path = path.replace_extension(".sol");

    if ( !entry.is_regular_file() || file_in_path.extension() != ".in" ) {
      continue;
    }

    std::string test = file_in_path.filename();
    SUBCASE(test.c_str()) {
      std::cout << " [" << test << "]";
      Polygon poly_in = readPolygonFile(file_in_path);
      Triangulation T(poly_in);
      createOutFile(T, file_out_path);
      bool res = compareFiles(file_sol_path, file_out_path);

      if ( res == false ) {
        printDiff(file_sol_path, file_out_path);
      }

      CHECK(res == true);
      fs::remove(file_out_path);
    }
  }

  std::cout << "\n";
}
