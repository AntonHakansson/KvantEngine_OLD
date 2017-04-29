#pragma once

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <glm/glm.hpp>

// Third-party
#include <entityx/entityx.h>
#include <spdlog/spdlog.h>

// Kvant Headers
#include <KvantEngine/CoreComponents/CNode.hpp>

namespace Kvant {

  class NodeSystem : public entityx::System<NodeSystem>, public entityx::Receiver<NodeSystem> {

  public:
    NodeSystem ();
    ~NodeSystem ();

    void configure (entityx::EventManager& events) override;
    void update(entityx::EntityManager &entities, entityx::EventManager &events,
                entityx::TimeDelta dt) override;

    void receive (const entityx::ComponentRemovedEvent<CNode>& event);
    void receive (const entityx::EntityDestroyedEvent& event);

  private:
    void update_world_transform (entityx::Entity entity);

    void assess_node_removals (entityx::Entity entity);
    void assess_node_additions (entityx::Entity entity);

  };

}
