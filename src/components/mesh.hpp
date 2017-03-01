#pragma once


#include <vector>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <eigen3/Eigen/Dense>

#include <entitySystem.hpp>
#include <types/Vertex.hpp>
#include <types/Texture.hpp>
#include <components/Material.hpp>

namespace Kvant {
  using namespace Eigen;
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
                         (GLvoid*)0);
        // Vertex Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                         (GLvoid*)offsetof(Vertex, normal));
        // Vertex Texture Coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                         (GLvoid*)offsetof(Vertex, texCoord));

        glBindVertexArray(0);
      }

  };

}
