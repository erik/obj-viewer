#include "objloader.hpp"

#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdlib>

Model::Model() :
  mName("")
{
  mNormals.push_back(Normal(0, 0, 1));
}

void Model::Load(std::string filename) {
  std::fstream file(filename.c_str(), std::fstream::in);

  if(file.fail()) {
    throw "Unable to open file: '" + filename + "'";
  }

  std::string line;

  while(file.good()) {
    getline(file, line);
    std::stringstream stream(line, std::stringstream::in);
    
    std::string type;
    stream >> type;

    // comment / blank line
    if(type == "#" || type == "") {
      continue;
    }
    
    // vertex
    else if(type == "v") {
      float x, y, z, w;
      stream >> x >> y >> z >> w;
     
      Vertex v(x, y, z, w || 1.0f);
      this->mVertices.push_back(v);
    }

    // normal
    else if(type == "vn") {
      float i, j, k;
      stream >> i >> j >> k;
      
      Normal n(i, j, k);
      this->mNormals.push_back(n);
    }

    // face
    else if(type == "f") {
      Polygon polygon;

      char argsBuf[100];
      stream.getline(argsBuf, 100);
      std::stringstream tmp(argsBuf, std::stringstream::in);

      tmp.ignore(100, ' ');

      for(int i = 0; !tmp.eof(); ++i) {
        int v(0), t(0), n(1);

        tmp >> v;
        if(tmp.peek() == '/') {
          tmp.ignore(2, '/');
          // 1//2
          if(tmp.peek() == '/') {
            tmp.ignore(2, '/');
          } else {
            tmp >> t;
          }
          tmp >> n;
        }

        if(static_cast<unsigned long>(v) < this->mVertices.size() + 1) {
          polygon.vertexIndicies.push_back(v - 1);
        } else {
          std::cerr << "Vertex index out of bounds: " << v << std::endl;
        }

        if(static_cast<unsigned long>(n) < this->mNormals.size() + 1) {
          polygon.numIndicies++;
          polygon.normalIndicies.push_back(n - 1);
        } else {
          std::cerr << "Normal index out of bounds: " << n << std::endl;
        }
      }
      
      this->mFaces.push_back(polygon);

    }

    else {
      std::cerr << "Don't know what to do with line: '" << line << "'; skipping." << std::endl;
      continue;
    }

  }

  file.close();

}

void Model::Render() {
  char r = 0, g= 0, b= 0;
  for(unsigned long i = 0; i < mFaces.size(); ++i) {
    Polygon face = this->mFaces[i];
    
    if(face.numIndicies == 3) {
      glBegin(GL_TRIANGLES);
    } else if(face.numIndicies == 4){
      glBegin(GL_QUADS);
    } else {
      glBegin(GL_POLYGON);
    }
    
    for(int j = 0; j < face.numIndicies; ++j) {
      Vertex v = this->mVertices[face.vertexIndicies[j]];
      Normal n = this->mNormals[face.normalIndicies[j]];
      
      glColor3b(r, g, b);
      glNormal3f(n.i, n.j, n.k);
      glVertex4f(v.x, v.y, v.z, v.w);
      
      r = ++r % 128;
      g = ++g % 128;
      b = ++b % 128;
    }

    glEnd();
  }
}
