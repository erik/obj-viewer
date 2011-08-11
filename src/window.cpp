#include "window.hpp"

#include <SFML/OpenGL.hpp>

Window::Window() :
  mApplication(sf::VideoMode(800, 600), "OBJ Viewer",
               sf::Style::Default,
               sf::ContextSettings(32)),
  mInput(mApplication.GetInput()) 
{
  mApplication.SetFramerateLimit(60);
}

void Window::Display()
{
  this->InitGL();

  while(mApplication.IsOpened()) {
    mApplication.SetActive();
    this->UpdateInput();
    this->Draw();
  }
}

void Window::SetModel(Model& m)
{
  mModel = m;
}

void Window::InitGL()
{
  glClearDepth(1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  
  glEnable(GL_COLOR_MATERIAL);  
  glEnable(GL_DEPTH_TEST);

  glDepthMask(GL_TRUE);

  glEnable(GL_LIGHTING); 
  GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
  GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5, 1.0f };
  GLfloat specularLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  GLfloat position1[] = {.5, 1., 1., 0.};

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
}

void Window::UpdateInput()
{

  if(mInput.IsKeyDown(sf::Key::Left)) {
    this->mSettings.xRotation += 5;
  }

  if(mInput.IsKeyDown(sf::Key::Right)) {
    this->mSettings.xRotation -= 5;
  }

  if(mInput.IsKeyDown(sf::Key::Up)) {
    this->mSettings.yRotation += 5;
  }

  if(mInput.IsKeyDown(sf::Key::Down)) {
    this->mSettings.yRotation -= 5;
  }

  sf::Event event;
  while(mApplication.PollEvent(event)) {

    if(event.Type == sf::Event::Closed) {
      mApplication.Close();
    }
    
    else if(event.Type == sf::Event::MouseWheelMoved) {
      this->mSettings.zoom += event.MouseWheel.Delta;
    }

    else if(event.Type == sf::Event::Resized) {
      glViewport(0, 0, event.Size.Width, event.Size.Height);
    }

    else if(event.Type == sf::Event::KeyPressed) {
    
      if(event.Key.Code == sf::Key::Escape) {
        mApplication.Close();
      }
      
      else if(event.Key.Code == sf::Key::W) {
        this->mSettings.wireframe = !this->mSettings.wireframe;
        
        if(this->mSettings.wireframe) {
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } 
        else {
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
      }

      else if(event.Key.Code == sf::Key::C) {
        this->mSettings.coloring = !this->mSettings.coloring;
        this->mModel.SetColorVerts(this->mSettings.coloring);
      }

      else if(event.Key.Code == sf::Key::N) {
        this->mSettings.normals = !this->mSettings.normals;
        this->mModel.SetDrawNormals(this->mSettings.normals);
      }

      else if(event.Key.Code == sf::Key::L) {
        this->mSettings.lighting = !this->mSettings.lighting;
        if(this->mSettings.lighting) {
          glEnable(GL_LIGHTING); 
        } else {
          glDisable(GL_LIGHTING); 
        }
      }

    }
  }
}

void Window::Draw()
{    
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glPushMatrix();

  glTranslatef(0.0f, 0.0f, this->mSettings.zoom);

  glRotatef(this->mSettings.yRotation, 1.f, 0.f, 0.f);
  glRotatef(this->mSettings.xRotation, 0.f, 1.f, 0.f);

  mModel.Render();
    
  glPopMatrix();  
  mApplication.Display();
}

