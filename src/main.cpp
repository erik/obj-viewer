#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>


#include "objloader.hpp"

int main(int argc, char** argv) {
  
  Model model;
  model.Load("models/cube.obj");

  sf::RenderWindow app(sf::VideoMode(800, 600), "OBJ Viewer", sf::Style::Default, sf::ContextSettings(32));

  app.SetFramerateLimit(60);

  glClearDepth(1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

  glEnable(GL_LIGHTING); 
  GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
  GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };

  // Assign created components to GL_LIGHT0
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  

  glEnable(GL_LIGHT0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0f, 1.0f, 1.0f, 500.0f);

  
  float zoom = -200;

  sf::Clock clock;

  while(app.IsOpened()) {
    app.SetActive();
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, zoom);
    glRotatef(clock.GetElapsedTime() * 20.f, 1.f, 0.f, 0.f);
    glRotatef(clock.GetElapsedTime() * 20.f, 0.f, 1.f, 0.f);
    glRotatef(clock.GetElapsedTime() * 20.f, 0.f, 0.f, 1.f);

    model.Render();
    
    sf::Event event;
    while(app.PollEvent(event)) {
      if(event.Type == sf::Event::Closed) {
        app.Close();
      } else if(event.Type == sf::Event::MouseWheelMoved) {
        zoom += event.MouseWheel.Delta;
      } else if(event.Type == sf::Event::Resized) {
        glViewport(0, 0, event.Size.Width, event.Size.Height);
      }
    }

    app.Display();
  }

  return 0;
}
