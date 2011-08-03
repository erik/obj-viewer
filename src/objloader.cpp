#include "objloader.hpp"

#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model() :
  mName("")
{
}

void Model::Load(std::string filename) {
  std::fstream file(filename.c_str(), std::fstream::in);

  if(file.fail()) {
    std::cerr << "Unable to open file: " << filename << std::endl;
    throw;
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
      Triangle triangle;

      char argsBuf[100];
      stream.getline(argsBuf, 100);
      std::stringstream tmp(argsBuf, std::stringstream::in);

      for(int i = 0; i < 3; ++i) {
        int v(0), t(0), n(0);

        tmp >> v;
        tmp.ignore(2, '/');
        // 1//2
        if(tmp.peek() == '/') {
          tmp.ignore(2, '/');
        } else {
          tmp >> t;
        }
        tmp >> n;

        if(static_cast<unsigned long>(v) < this->mVertices.size() + 1) {
          triangle.vertexIndicies[i] = v - 1;
        } else {
          std::cerr << "Vertex index out of bounds: " << v << std::endl;
        }

        if(static_cast<unsigned long>(n) < this->mNormals.size() + 1) {
          triangle.normalIndicies[i] = n - 1;
        } else {
          std::cerr << "Normal index out of bounds: " << n << std::endl;
        }
      }
      
      this->mFaces.push_back(triangle);

    }

    else {
      std::cerr << "Don't know what to do with line: '" << line << "'; skipping." << std::endl;
      continue;
    }

  }

  file.close();

}

void Model::Render() {
    glBegin(GL_TRIANGLES);

    for(unsigned long i = 0; i < mFaces.size(); ++i) {
      Triangle face = this->mFaces[i];
      for(int j = 0; j < 3; ++j) {
        Vertex v = this->mVertices[face.vertexIndicies[j]];
        glVertex4f(v.x, v.y, v.z, v.w);
      }
    }

    glEnd();
}
