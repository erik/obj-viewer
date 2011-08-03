#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>


#include "objloader.hpp"

int main(int argc, char** argv) {
  
  Model model;
  model.Load(argv[1]);

  sf::RenderWindow app(sf::VideoMode(800, 600), "OBJ Viewer", sf::Style::Default, sf::ContextSettings(32));

  app.SetFramerateLimit(60);

  glClearDepth(1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

  glEnable(GL_LIGHTING); 
  GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
  GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5, 1.0f };
  GLfloat specularLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  GLfloat position1[] = { -1.5f, 1.0f, -4.0f, 1.0f };

  // Assign created components to GL_LIGHT0
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, position1);

  glShadeModel(GL_SMOOTH);

  glEnable(GL_LIGHT0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0f, 1.0f, 1.0f, 500.0f);

  float xrot(0), yrot(0), zrot(0);
  float zoom = -20;
  bool wireframe = false;


  const sf::Input &input = app.GetInput();
  while(app.IsOpened()) {
    app.SetActive();
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, zoom);

    glRotatef(yrot, 1.f, 0.f, 0.f);
    glRotatef(xrot, 0.f, 1.f, 0.f);

    model.Render();
    
    glPopMatrix();

    if(input.IsKeyDown(sf::Key::Left)) {
      xrot += 5;
    }
    if(input.IsKeyDown(sf::Key::Right)) {
      xrot -= 5;
    }
    if(input.IsKeyDown(sf::Key::Up)) {
      yrot += 5;
    }
    if(input.IsKeyDown(sf::Key::Down)) {
      yrot -= 5;
    }

    sf::Event event;
    while(app.PollEvent(event)) {
      if(event.Type == sf::Event::Closed) {
        app.Close();
      } else if(event.Type == sf::Event::MouseWheelMoved) {
        zoom += event.MouseWheel.Delta;
      } else if(event.Type == sf::Event::Resized) {
        glViewport(0, 0, event.Size.Width, event.Size.Height);
      } else if(event.Type == sf::Event::KeyPressed) {
        if(event.Key.Code == sf::Key::Escape) {
          app.Close();
        } else if(event.Key.Code == sf::Key::W) {
          wireframe = !wireframe;
          if(wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
          } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
          }
        }
      }
    }

    app.Display();
  }

  return 0;
}
