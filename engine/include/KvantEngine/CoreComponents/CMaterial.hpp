#pragma once

// C++ Headers
#include <string>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

// Third-party
#include <entityx/entityx.h>

// Kvant Headers
#include <KvantEngine/CoreTypes/Program.hpp>

namespace Kvant {
  using namespace std;
  namespace ex = entityx;

  class CMaterial : ex::Component<CMaterial> {
  public:
    CMaterial(const Shader _shader) : m_program{_shader} { }
    const Program& getProgram() const { return m_program; }
  private:
    Program m_program;
  };
}
