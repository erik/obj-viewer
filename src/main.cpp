#include "objloader.hpp"
#include "window.hpp"


int main(int argc, char** argv) {
  
  Window window;
  Model model;
  model.Load(argv[1]);
  
  window.SetModel(model);
  window.Display();

  return 0;
}
