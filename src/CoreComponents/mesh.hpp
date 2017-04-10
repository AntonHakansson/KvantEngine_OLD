#pragma once

// C++ Headers
#include <vector>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Kvant Headers
#include <Core/entitySystem.hpp>
#include <CoreTypes/Vertex.hpp>
#include <CoreTypes/Texture.hpp>
#include <CoreComponents/Material.hpp>

namespace Kvant {
  
  using namespace std;

  struct MeshData {
    /* Mesh Data */
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
  };

  struct CMeshFilter : Component {

    CMeshFilter(const vector<Vertex>& _vertices, const vector<GLuint>& _indices, const vector<Texture>& _textures) : m_mesh_data{_vertices, _indices, _textures} {}
    CMeshFilter(const MeshData& _mesh_data) : m_mesh_data(_mesh_data) {}
 
    const MeshData& get_mesh_data() { return m_mesh_data; }

  private:
    MeshData m_mesh_data;
  };

  struct CMeshRenderer : Component {
    CMeshRenderer() {}

    void init() override {
      m_mesh_filter = &entity->get_component<CMeshFilter>();
      m_material = &entity->get_component<CMaterial>();
      setupMesh(); 
    }

    void draw() override {
      // User current m_material
      m_material->getProgram().use();
      
      //set the "projection" uniform in the vertex shader, because it's not going to change
      glm::mat4 projection = glm::perspective(glm::radians(50.0f), 512.0f/512.0f, 0.1f, 10.0f);
      m_material->getProgram().set_uniform("projection", projection, GL_FALSE);

      //set the "camera" uniform in the vertex shader, because it's also not going to change
      glm::mat4 camera = glm::lookAt(glm::vec3(0,0,-3), glm::vec3(0,0,0), glm::vec3(0,1,0));
      m_material->getProgram().set_uniform("camera", camera, GL_FALSE);

      glm::mat4 model = glm::mat4();
      m_material->getProgram().set_uniform("model", model);

      // Draw mesh
      glBindVertexArray(m_vao);
      auto& mesh_data = m_mesh_filter->get_mesh_data();
      glDrawElements(GL_TRIANGLES, mesh_data.indices.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
    }

    private:
      CMeshFilter* m_mesh_filter{nullptr};
      CMaterial* m_material{nullptr};

      /*  Render data  */
      GLuint m_vao, m_vbo, m_ebo;
      /*  Functions    */
      void setupMesh() {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        auto& mesh_data = m_mesh_filter->get_mesh_data();

        glBufferData(GL_ARRAY_BUFFER, mesh_data.vertices.size() * sizeof(Vertex),
                 &mesh_data.vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_data.indices.size() * sizeof(GLuint),
                 &mesh_data.indices[0], GL_STATIC_DRAW);

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
  };
}
