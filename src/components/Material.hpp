#pragma once

#include <string>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <types/Shader.hpp>
#include <entitySystem.hpp>

namespace Kvant {
  using namespace std;

  struct CMaterial : Component {
    Shader shader;
    CMaterial(const Shader _shader) : shader{_shader} { }

    void use() {
      this->shader.use();
    }
  };
}
