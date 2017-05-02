#include <KvantEngine/CoreSystems/NodeSystem.hpp>
#include <KvantEngine/CoreComponents/CMaterial.hpp>
#include <KvantEngine/States/State.hpp>
#include <KvantEngine/Core/Engine.hpp>

namespace Kvant {

  NodeSystem::NodeSystem (Engine* engine) {
    m_engine = engine;
  }

  NodeSystem::~NodeSystem () {

  }

  void NodeSystem::configure (entityx::EventManager& events) {
    events.subscribe<entityx::ComponentRemovedEvent<CNode>>(*this);
    events.subscribe<entityx::EntityDestroyedEvent>(*this);
  }

  void NodeSystem::update(entityx::EntityManager &entities,
                          entityx::EventManager &, entityx::TimeDelta) {

    draw_imgui_tree (entities);

    for (auto e : entities.entities_with_components<CNode>()) {
      if (e.component<CNode>()->is_active()) {
        assess_node_removals (e);
        assess_node_additions (e);

        update_world_transform (e);
      }
    }
  }

  void NodeSystem::receive (const entityx::ComponentRemovedEvent<CNode>& event) {
    auto entity = event.entity;
    auto node = event.component;

    if (node) {
      if (node->m_parent)
        node->m_parent.component<CNode>()->remove_child(entity);

      node->remove_children();
      assess_node_removals (entity);
    }
  }

  void NodeSystem::receive (const entityx::EntityDestroyedEvent& event) {
    auto entity = event.entity;
    auto node = entity.component<CNode>();

    if (node) {
      if (node->m_parent && node->m_parent.component<CNode>())
        node->m_parent.component<CNode>()->remove_child(entity);

      node->remove_children();
      assess_node_removals (entity);
    }
  }

  void NodeSystem::assess_node_removals (entityx::Entity entity) {
    if (!entity.valid()) return;

    auto node = entity.component<CNode>();
    if (!node) return;

    for (entityx::Entity dc : node->m_remove_children) {
      if (node->has_child(dc)) {
        node->m_children.erase(dc);
        if (dc) {
          for (entityx::Entity gc : dc.component<CNode>()->get_children()) {
            if (gc) {
              assess_node_removals (gc);
            }
          }
        }
      }
    }

    node->m_remove_children.clear();
  }

  void NodeSystem::assess_node_additions (entityx::Entity entity) {
    if (!entity.valid()) return;

    auto node = entity.component<CNode>();
    if(!node) return;

    for (auto ac : node->m_add_children) {
      if (ac.valid()) {
        if (!node->has_child(ac) && ac.component<CNode>() && entity != ac) {

          // Replace owner
          if (ac.component<CNode>()->m_parent)
            ac.component<CNode>()
                ->m_parent.component<CNode>()
                ->m_children.erase(ac);

          ac.component<CNode>()->m_parent = entity;
          node->m_children.insert(ac);

        }
      }
    }

    node->m_add_children.clear();
  }

  void NodeSystem::update_world_transform (entityx::Entity entity) {
    auto world_transform = glm::mat4();

    for (entityx::Entity node = entity; node.valid(); node = node.component<CNode>()->m_parent) {
      world_transform = node.component<CNode>()->get_transform() * world_transform;
    }

    entity.component<CNode>()->m_world_transform = world_transform;
  }

  void NodeSystem::draw_imgui_tree (entityx::EntityManager &entities) {
    auto* state = m_engine->get_state_manager().peek_state();
    if (state == nullptr) return;

    ImGui::Begin("Node Tree");
    if (ImGui::TreeNode("Layers")) {
      for (int i = 0; i < State::GameLayer::TOTAL; i++) {
        auto layer = state->get_layer(i);
        if (ImGui::TreeNode((void*)(intptr_t)i, "Layer %d", i)) {
          auto node = layer.component<CNode>();
          draw_imgui_node (node);
          ImGui::TreePop();
        }
      }
      ImGui::TreePop();
    }

    /*if (ImGui::CollapsingHeader("Stats")) {
      ImGui::Text("CNodes: " + std::to_string( entities.entities_with_components<CNode>() ));
    }*/

    ImGui::End();
  }

  void NodeSystem::draw_imgui_node(entityx::ComponentHandle<Kvant::CNode, entityx::EntityManager>& node) {

    bool isActive = node->is_active();
    ImGui::Checkbox("Active", &isActive);
    node->set_active(isActive);

    bool isVisible = node->is_visible();
    ImGui::Checkbox("Visible", &isVisible);
    node->set_visible(isVisible);

    ImGui::Spacing();

    ImGui::Columns(3, "transform_columns", true);
    ImGui::Separator();
    ImGui::Text("x");
    ImGui::NextColumn();
    ImGui::Text("y");
    ImGui::NextColumn();
    ImGui::Text("z");
    ImGui::NextColumn();
    ImGui::Columns(1);
    ImGui::Separator();
    // Position
    auto pos = node->get_position();
    float pos3f[3] = {pos.x, pos.y, pos.z};
    ImGui::DragFloat3("Position", pos3f, 0.01f);

    node->set_position(pos3f[0], pos3f[1], pos3f[2]);
    ImGui::Spacing();

    // Rotation
    auto rot = node->get_rotation();
    float rot3f[3] = {rot.x, rot.y, rot.z};
    ImGui::DragFloat3("Rotation", rot3f, 0.2f);

    node->set_rotation(rot3f[0], rot3f[1], rot3f[2]);
    ImGui::Spacing();

    // Scale
    auto scale = node->get_scale();
    float scale3f[3] = {scale.x, scale.y, scale.z};
    ImGui::DragFloat3("Scale", scale3f, 0.08f);

    node->set_scale(scale3f[0], scale3f[1], scale3f[2]);
    ImGui::Spacing();
    ImGui::Spacing();

    int id = 0;
    for (auto c : node->get_children()) {
      auto child_node = c.component<CNode>();
      auto child_name = child_node->name + " " + std::to_string(id);
      if (ImGui::TreeNode(child_name.c_str())) {
        draw_imgui_node(child_node);
        ImGui::TreePop();
      }
      ++id;
    }
  }
}
