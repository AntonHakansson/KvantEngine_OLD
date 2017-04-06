#pragma once


#include <vector>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <entitySystem.hpp>
#include <types/Vertex.hpp>
#include <types/Texture.hpp>
#include <components/Material.hpp>

namespace Kvant {
  using namespace std;
  struct MeshData {
    /* Mesh Data */
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
  };

  struct CMeshFilter : Component {
    MeshData meshData;

    CMeshFilter(const vector<Vertex>& _vertices, const vector<GLuint>& _indices, const vector<Texture>& _textures) : meshData{_vertices, _indices, _textures} {}
    CMeshFilter(const MeshData& _meshData) : meshData(_meshData) {}
  };

  struct CMeshRenderer : Component {
    CMeshFilter* meshFilter{nullptr};
    CMaterial* material{nullptr};

    CMeshRenderer() {}

    void init() override {
      meshFilter = &entity->getComponent<CMeshFilter>();
      material = &entity->getComponent<CMaterial>();
      setupMesh(); 
    }

    void draw() override {
      // User current material
      material->use();
      
      //set the "projection" uniform in the vertex shader, because it's not going to change
      glm::mat4 projection = glm::perspective(glm::radians(50.0f), 512.0f/512.0f, 0.1f, 10.0f);
      material->shader.setUniform("projection", projection, GL_FALSE);

      //set the "camera" uniform in the vertex shader, because it's also not going to change
      glm::mat4 camera = glm::lookAt(glm::vec3(0,0,-3), glm::vec3(0,0,0), glm::vec3(0,1,0));
      material->shader.setUniform("camera", camera, GL_FALSE);

      glm::mat4 model = glm::mat4();
      material->shader.setUniform("model", model);

      // Draw mesh
      glBindVertexArray(this->VAO);
      auto& meshData = this->meshFilter->meshData;
      glDrawElements(GL_TRIANGLES, meshData.indices.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
    }

    private:
      /*  Render data  */
      GLuint VAO, VBO, EBO;
      /*  Functions    */
      void setupMesh() {
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

        auto& meshData = this->meshFilter->meshData;

        glBufferData(GL_ARRAY_BUFFER, meshData.vertices.size() * sizeof(Vertex),
                 &meshData.vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData.indices.size() * sizeof(GLuint),
                 &meshData.indices[0], GL_STATIC_DRAW);

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
                         (GLvoid*)offsetof(Vertex, texCoord.x));

        glBindVertexArray(0);
      }
  };
}
