#pragma once

// C++ Headers
#include <string>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

// Kvant Headers
#include <CoreTypes/Program.hpp>
#include <Core/entitySystem.hpp>

namespace Kvant {
  using namespace std;

  struct CMaterial : Component {
    CMaterial(const Shader _shader) : m_program{_shader} { }
    const Program& getProgram() const { return m_program; }
  private:
    Program m_program;
  };
}
