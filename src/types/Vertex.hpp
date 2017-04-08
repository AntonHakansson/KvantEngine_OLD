#pragma once

// OpenGL / glew Headers
#include <glm/glm.hpp>

namespace Kvant {
  using namespace glm;

  struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 tex_coord;
  };
}
