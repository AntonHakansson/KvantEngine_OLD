#pragma once

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <glm/glm.hpp>

// SDL2 Headers
#include <SDL2/SDL.h>

// Third-party
#include <entityx/entityx.h>
#include <spdlog/spdlog.h>

// Kvant Headers
#include <CoreComponents/CNode.hpp>
#include <CoreEvents/InputEvent.hpp>

namespace Kvant {

  namespace ex = entityx;

  class InputSystem : public ex::System<InputSystem>, public ex::Receiver<InputEvent> {

  public:
    InputSystem (ex::EntityManager& entity_manager);
    ~InputSystem ();
    void configure (ex::EventManager& events) override;
    void update (ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta dt) override;

    void receive (const InputEvent& event);

  private:
    ex::EntityManager& m_entity_manager;
  };

}
