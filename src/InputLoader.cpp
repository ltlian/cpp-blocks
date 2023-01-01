#include "InputLoader.hpp"

std::string InputLoader::load(std::string fileName)
{
  std::string text;

  std::ifstream file(fileName);
  if (file.is_open())
  {
    std::string line;
    while (std::getline(file, line))
    {
      text += line;
    }
    file.close();
  }

  return text;
}