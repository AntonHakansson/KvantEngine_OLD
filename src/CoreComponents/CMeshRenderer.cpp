#include <CoreComponents/CMeshRenderer.hpp>

namespace Kvant {
  CMeshRenderer::CMeshRenderer (const vector<Vertex>& _vertices, const vector<GLuint>& _indices, const vector<Texture>& _textures) {
    m_vertices = _vertices;
    m_indices = _indices;
    m_textures = _textures;
    setup_mesh ();
  }

  CMeshRenderer::~CMeshRenderer () {

  }

  void CMeshRenderer::setup_mesh () {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex),
                  &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint),
                  &m_indices[0], GL_STATIC_DRAW);

    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                     (GLvoid*)offsetof(Vertex, position.x));
    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                     (GLvoid*)offsetof(Vertex, normal.x));
    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                     (GLvoid*)offsetof(Vertex, tex_coord.x));

    glBindVertexArray(0);
  }
}
