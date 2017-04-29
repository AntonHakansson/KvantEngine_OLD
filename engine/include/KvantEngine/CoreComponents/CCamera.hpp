#pragma once

// SDL2 Headers
#include <SDL2/SDL.h>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// Third-party
#include <entityx/entityx.h>

namespace Kvant {

  namespace ex = entityx;

  class CCamera : public ex::Component<CCamera> {
  public:
    CCamera () {
      m_pos = glm::vec3(0.f, 0.f, 1.f);
      m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
      m_up = glm::vec3(0.0f, 1.0f, 0.0f);
      m_projection = glm::mat4();
    }
    CCamera(const glm::vec3 &pos, float fov, float aspect, float zNear,
            float zFar) {
      m_pos = pos;
      m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
      m_up = glm::vec3(0.0f, 1.0f, 0.0f);
      m_projection = glm::perspective(fov, aspect, zNear, zFar);
    }
    ~CCamera () {}

    glm::mat4 get_projection_transform () const {
		  return m_projection;
    }

    glm::mat4 get_camera_transform () const {
		  return glm::lookAt (m_pos, m_pos + m_forward, m_up);
    }

    void set_pos (const glm::vec3& pos) {
      m_pos = pos;
    }
    void set_pos (float x, float y, float z = 1) {
      m_pos = glm::vec3(x, y, z);
    }

  private:
    glm::mat4 m_projection;
  	glm::vec3 m_pos;
  	glm::vec3 m_forward;
    glm::vec3 m_up;
  };

}
