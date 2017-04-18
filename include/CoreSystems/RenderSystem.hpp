#pragma once

// SDL2 Headers
#include <SDL2/SDL.h>

// Third-party
#include <entityx/entityx.h>

namespace Kvant {

  namespace ex = entityx;

  class RenderSystem : public ex::System<RenderSystem> {
  public:
    RenderSystem ();
    ~RenderSystem ();

    void set_render_root (ex::Entity root);
    void set_camera (ex::Entity camera);
    void update (ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta dt) override;

  private:
    void render_entity (ex::Entity entity);
    ex::Entity m_render_root, m_camera;
  };

}
