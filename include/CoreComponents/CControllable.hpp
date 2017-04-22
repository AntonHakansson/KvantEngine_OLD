#pragma once

// SDL2 Headers
#include <SDL2/SDL.h>

// Third-party
#include <spdlog/spdlog.h>
#include <entityx/entityx.h>

// Kvant Headers
#include <CoreEvents/InputEvent.hpp>

namespace Kvant {
  using namespace std;
  namespace ex = entityx;

  class CControllable : ex::Component<CControllable> {
  public:
    CControllable(bool enabled = true) : m_enabled(enabled) {}

    void control (ex::Entity& entity, const SDL_Event& event);

    void enable () { m_enabled = true; }
    void disable () { m_enabled = false; }

  private:
    bool m_enabled{true};
  };
}
