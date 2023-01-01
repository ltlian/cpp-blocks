#ifndef INPUT_LOADER_H
#define INPUT_LOADER_H

#include <fstream>

class InputLoader
{
  public:
  static std::string load(std::string fileName);
};

#endif