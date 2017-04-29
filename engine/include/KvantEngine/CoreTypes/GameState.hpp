#pragma once

// SDL2 Headers
#include <SDL2/SDL.h>

// Kvant Headers
#include <KvantEngine/Core/Engine.hpp>

namespace Kvant {

  // Forward declaration
  struct StateManager;

  struct GameState {

    virtual ~GameState() {};
    virtual void init() = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handle_events(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void draw(const float dt) = 0;

    void change_state(GameState* state);
  protected:
    StateManager* m_state_manager;

    friend struct StateManager;
  };
}
