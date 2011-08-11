#include <iostream>
#include <string>

#include "objloader.hpp"
#include "window.hpp"


int main(int argc, char** argv) {
  
  if(argc < 2) {
    std::cerr << "Need to specify a file to render" << std::endl;
    return 1;
  }

  Window window;
  Model model;

  try {
    model.Load(argv[1]);
  } catch (std::string err) {
    std::cerr << "Error loading model: " << err << std::endl;
    return 1;
  }
  
  window.SetModel(model);
  window.Display();

  return 0;
}
