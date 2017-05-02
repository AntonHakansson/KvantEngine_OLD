#include <KvantEngine/CoreSystems/RenderSystem.hpp>
#include <KvantEngine/CoreComponents/CNode.hpp>
#include <KvantEngine/CoreComponents/CCamera.hpp>
#include <KvantEngine/CoreComponents/CMaterial.hpp>
#include <KvantEngine/CoreComponents/CMeshRenderer.hpp>

namespace Kvant {

  RenderSystem::RenderSystem (Engine* engine) {
    m_engine = engine;
    m_time_start = std::chrono::high_resolution_clock::now();
  }
  RenderSystem::~RenderSystem () {

  }

  void RenderSystem::set_render_root (ex::Entity root) {
    if (root.valid() && root.component<CNode>())
      m_render_root = root;
  }

  void RenderSystem::set_camera (ex::Entity camera) {
    if (camera.valid() && camera.component<CCamera>())
      m_camera = camera;
  }

  void RenderSystem::update (ex::EntityManager&, ex::EventManager&, ex::TimeDelta) {
    if (!m_render_root.valid() || !m_camera.valid()) return;
    if (!m_render_root.component<CNode>()) return;

    render_entity(m_render_root);
  }

  void RenderSystem::render_entity (ex::Entity entity) {
    auto node = entity.component<CNode>();
    auto camera = m_camera.component<CCamera>();
    if (!node || !camera) return;

    // Render children
    for (ex::Entity child : node->get_children()) {
      if (child.valid() && child.component<CNode>()) {
        render_entity (child);
      }
    }
    
    if (!node->is_active()) return;
    if (!node->is_visible()) return;

    // Use current m_material
    auto mesh_renderer = entity.component<CMeshRenderer> ();
    auto material = entity.component<CMaterial> ();

    // use entity material
    if (material) {
      // Activate Shader
      material->getProgram().use();

      // Set projection matrix
      material->getProgram().set_uniform("projection", camera->get_projection_transform(), GL_FALSE);

      // set the "camera" uniform in the vertex shader, because it's also not going to change
      material->getProgram().set_uniform("camera", camera->get_camera_transform(), GL_FALSE);

      // Set model matrix
      material->getProgram().set_uniform("model", node->get_world_transform());

      using namespace std;
      float time_seconds = chrono::duration_cast<chrono::duration<float, milli>>( chrono::high_resolution_clock::now() - m_time_start ).count()/1000.;
      material->getProgram().set_uniform("time", time_seconds);
    }

    // Draw Entity
    if (mesh_renderer) {
      // bind textures
      for (auto i{0u}; i < mesh_renderer->m_textures.size(); i++) {
        auto* state = m_engine->get_state_manager().peek_state();
        if (!state) break;

        auto *texture_manager = state->get_texture_resources();
        auto texture = texture_manager->get(mesh_renderer->m_textures[i]);
        if(texture) texture->bind(i);
      }

      // Draw mesh
      glBindVertexArray(mesh_renderer->m_vao);
      auto indices = mesh_renderer->get_indices();
      glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
    }
  }
}
