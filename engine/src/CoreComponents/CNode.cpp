#include <KvantEngine/CoreComponents/CNode.hpp>

namespace Kvant {


  CNode::CNode (const glm::vec3& position,
          const glm::vec3& rotation,
          const glm::vec3& scale)
      : m_position(position), m_rotation(rotation), m_scale(scale) {}

  CNode::CNode (const glm::vec2& position, const float angle, const float scale) {
    m_position = glm::vec3 (position.x, position.y, 0.f);
    m_rotation = glm::vec3 (0.f, 0.f, glm::radians (angle));
    m_scale = scale*glm::vec3(1, 1, 1);
  }

  CNode::CNode (const float x, const float y, const float angle, const float scale) {
    m_position = glm::vec3 (x, y, 0.f);
    m_rotation = glm::vec3 (0.f, 0.f, glm::radians (angle));
    m_scale = scale*glm::vec3(1, 1, 1);
  }

  CNode::~CNode () {

  }

  glm::mat4 CNode::get_transform () {
    glm::mat4 pos_matrix = glm::translate (m_position);

    glm::mat4 rot_x_matrix = glm::rotate (m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 rot_y_matrix = glm::rotate (m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 rot_z_matrix = glm::rotate (m_rotation.z, glm::vec3(0.f, 0.f, 1.f));
    glm::mat4 rot_matrix = rot_z_matrix * rot_y_matrix * rot_x_matrix;

    glm::mat4 scale_matrix = glm::scale (m_scale);

    return pos_matrix * rot_matrix * scale_matrix;
  }

  entityx::ComponentHandle<CNode> CNode::get_root_node () {
    if (!get_parent_node()->m_parent.valid())
      return get_parent_node();

    return get_parent_node()->get_root_node();
  }

  entityx::ComponentHandle<CNode> CNode::get_parent_node () {
      return m_parent.component<CNode>();
  }

  entityx::Entity CNode::get_parent () {
    return m_parent;
  }

  std::set<entityx::Entity> CNode::get_children () {
    return m_children;
  }

  void CNode::add_child (entityx::Entity child) {
      m_add_children.insert(child);
  }

  void CNode::remove_child (entityx::Entity child) {
    m_remove_children.insert(child);
  }

  void CNode::remove_children () {
    for (auto c : m_children) {
      remove_child (c);
    }
  }

  bool CNode::has_child (entityx::Entity child) {
      if (m_children.count(child) > 0)
        return true;
      else {
        for (auto c : m_children) {
          if (c.component<CNode>()->has_child(child))
            return true;
        }
      }

      return false;
  }

  void CNode::add_tag (Tags tag) {
    m_tags.insert (tag);
  }
  void CNode::remove_tag (Tags tag) {
    m_tags.erase (tag);
  }
  bool CNode::has_tag (Tags tag) {
    if (m_tags.count(tag) > 0)
      return true;

    return false;
  }

}
