#include <iostream>
#include <fstream>
#include <sstream>

#include "utils-files.h"

static std::streambuf* originalCin = std::cin.rdbuf();
static std::streambuf* originalCout = std::cout.rdbuf();

void redirectCin(std::istream& mockInput) {
  std::cin.rdbuf(mockInput.rdbuf());
}

void restoreCin() {
  std::cin.rdbuf(originalCin);
}

void redirectCout(std::ofstream& mockOutput) {
  std::cout.rdbuf(mockOutput.rdbuf());
}

void restoreCout() {
  std::cout.rdbuf(originalCout);
}
