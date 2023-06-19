#ifndef __UTILS__
#define __UTILS__

#include <fstream>
#include <sstream>

void redirectCin(std::istream& mockInput);
void restoreCin();

void redirectCout(std::ofstream& mockOutput);
void restoreCout();

#endif
