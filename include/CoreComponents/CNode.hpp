#pragma once

// C++ Headers
#include <list>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// Third-party
#include <entityx/entityx.h>


namespace Kvant {


  class CNode : entityx::Component<CNode> {
    friend class NodeSystem;

  public:
    enum Tags {
      scene,
      GUI
    };

    CNode (const glm::vec3& position = glm::vec3(0.f, 0.f, 0.f),
            const glm::vec3& rotation = glm::vec3(0.f, 0.f, 0.f),
            const glm::vec3& scale = glm::vec3(1.f, 1.f, 1.f));

    CNode (const glm::vec2& position = glm::vec2(0.f, 0.f),
            const float angle = 0,
            const float scale = 1);

    CNode (const float x = 0, const float y = 0,
            const float angle = 0, const float scale = 1);

    ~CNode();

    glm::mat4 get_transform ();
    glm::mat4 get_world_transform () { return m_world_transform; };

    glm::vec3& get_position () { return m_position; }
    glm::vec3& get_rotation () { return m_rotation; }
    glm::vec3& get_scale () { return m_scale; }

    void set_position (glm::vec3& pos) { m_position = pos; }
    void set_position (glm::vec2& pos) { m_position = glm::vec3 (pos.x, pos.y, 0.f); }
    void set_position (float x, float y) { m_position = glm::vec3 (x, y, 0.f); }

    void set_rotation (glm::vec3& rot) { m_rotation = rot; }
    void set_rotation (float angle) { m_rotation = glm::vec3 (0.f, 0.f, glm::radians (angle)); }

    void set_scale (glm::vec3& scale) { m_scale = scale; }

    entityx::ComponentHandle<CNode> get_root_node ();
    entityx::ComponentHandle<CNode> get_parent_node ();
    entityx::Entity get_parent ();
    std::set<entityx::Entity> get_children ();

    void add_child (entityx::Entity child);
    void remove_child (entityx::Entity child);
    void remove_children ();
    bool has_child (entityx::Entity child);

    void add_tag (Tags tag);
    void remove_tag (Tags tag);
    bool has_tag (Tags tag);

    bool is_active () { return m_active; }
    bool is_visible () { return m_visible; }

  private:
    entityx::Entity m_parent;
    std::set<entityx::Entity> m_children,
                              m_add_children,
                              m_remove_children;

    std::set<Tags> m_tags;
    bool m_active{true},
          m_visible{true};

    glm::mat4 m_transform;
    glm::mat4 m_world_transform;

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

  };

}
