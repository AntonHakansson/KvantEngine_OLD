#include <KvantEngine/CoreSystems/NodeSystem.hpp>
#include <KvantEngine/CoreComponents/CMaterial.hpp>

namespace Kvant {

  NodeSystem::NodeSystem () {

  }

  NodeSystem::~NodeSystem () {

  }

  void NodeSystem::configure (entityx::EventManager& events) {
    events.subscribe<entityx::ComponentRemovedEvent<CNode>>(*this);
    events.subscribe<entityx::EntityDestroyedEvent>(*this);
  }

  void NodeSystem::update(entityx::EntityManager &entities,
                          entityx::EventManager &, entityx::TimeDelta) {
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
}
