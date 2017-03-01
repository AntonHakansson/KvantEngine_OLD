#pragma once

#include <eigen3/Eigen/Dense>

namespace Kvant {
  using namespace Eigen;

  struct Vertex {
    Vector3d position;
    Vector3d normal;
    Vector2d texCoord;
  };
}
