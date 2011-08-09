#pragma once

#ifndef WINDOW_H_
#define WINDOW_H_

#include <SFML/Graphics.hpp>
#include "objloader.hpp"

struct WindowOptions {
  float zoom;
  float xRotation, yRotation;
  bool wireframe;

  WindowOptions() :
    zoom(-20.0f),
    xRotation(0.0f),
    yRotation(0.0f),
    wireframe(false) {
  };
  
};

class Window {
private:
  sf::RenderWindow mApplication;
  Model mModel;
  const sf::Input& mInput;
  struct WindowOptions mOptions;

  void InitGL();
  void UpdateInput();
  void Draw();

public:
  Window();

  // main event/display loop
  void Display();

  void SetModel(Model& m);  
};

#endif /* WINDOW_H_ */
