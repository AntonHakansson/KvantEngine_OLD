#pragma once

// C++ Headers
#include <string>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

namespace Kvant {
  using namespace std;

  struct Texture {
    GLuint id;
    string type;
  };
}
