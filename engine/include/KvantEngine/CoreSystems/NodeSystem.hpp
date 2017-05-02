#pragma once

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <glm/glm.hpp>

// Third-party
#include <entityx/entityx.h>
#include <spdlog/spdlog.h>
#include <imgui/imgui.h>

// Kvant Headers
#include <KvantEngine/CoreComponents/CNode.hpp>
#include <KvantEngine/imgui/imgui_impl_sdl_gl3.h>

namespace Kvant {

  // forward declaration
  class Engine;

  class NodeSystem : public entityx::System<NodeSystem>, public entityx::Receiver<NodeSystem> {

  public:
    NodeSystem (Engine *engine);
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

    void draw_imgui_tree (entityx::EntityManager &entities);
    void draw_imgui_node (entityx::ComponentHandle<Kvant::CNode, entityx::EntityManager>& node);

    Engine *m_engine;

  };

}
