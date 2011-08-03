#pragma once

#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include <vector>
#include <string>

struct Vertex {
  float x, y, z, w;

  Vertex(float _x, float _y, float _z, float _w = 1.0f) :
    x(_x), y(_y), z(_z), w(_w) {}
};

struct Normal {
  float i, j, k;

  Normal(float _i, float _j, float _k) : i(_i), j(_j), k(_k) {}
};

struct Triangle {
  int vertexIndicies[3];
  int normalIndicies[3];
};

class Model {
  std::string mName;

  std::vector<Vertex> mVertices;
  std::vector<Normal> mNormals;

  std::vector<Triangle> mFaces;

public:
  Model();

  void Load(std::string filename);

  void Render();
};

#endif /* OBJLOADER_H_*/
