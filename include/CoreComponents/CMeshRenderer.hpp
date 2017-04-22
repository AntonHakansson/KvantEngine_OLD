#pragma once

// C++ Headers
#include <vector>
#include <memory>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <glm/glm.hpp>

// Third-party
#include <entityx/entityx.h>

// Kvant Headers
#include <CoreTypes/Vertex.hpp>
#include <CoreTypes/Texture.hpp>

namespace Kvant {

  using namespace Kvant;
  using namespace std;
  namespace ex = entityx;

  class CMeshRenderer : ex::Component<CMeshRenderer> {
    friend class RenderSystem;

  public:
    CMeshRenderer (const vector<Vertex>& _vertices, const vector<GLuint>& _indices, const vector<Texture>& _textures);
    ~CMeshRenderer ();

    const vector<Vertex>& get_vertices () { return m_vertices; }
    const vector<GLuint>& get_indices () { return m_indices; }
    const vector<shared_ptr<Texture>>& get_textures () { return m_textures; }

    void add_texture(shared_ptr<Texture> texture) {
      m_textures.push_back(texture);
    }

  private:
    /*  Render data  */
    GLuint m_vao, m_vbo, m_ebo;
    /* Mesh Data */
    vector<Vertex> m_vertices;
    vector<GLuint> m_indices;
    vector<shared_ptr<Texture>> m_textures;

    void setup_mesh ();
  };
}
