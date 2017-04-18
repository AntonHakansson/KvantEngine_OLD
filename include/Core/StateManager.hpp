#pragma once

// C++ Headers
#include <vector>
#include <memory>

// SDL2 Headers
#include <SDL2/SDL.h>

// Kvant Headers
#include <States/State.hpp>

namespace Kvant {

  using namespace std;

  class State;
  class Engine;
  struct StateManager {

    StateManager(Kvant::Engine* engine) : m_engine(engine) {}

    void cleanup ();

    template <typename T, typename... TArgs>
    void change_state (TArgs&&... _args) {
      // cleanup current state
      if (!m_states.empty()) {
        m_states.back()->cleanup();
        m_states.pop_back();
      }

      // Store and init new state
      m_states.emplace_back ( make_unique<T>(forward<TArgs>(_args)...) );
      m_states.back()->init(m_engine);
    }

    template <typename T, typename... TArgs>
    void push_state (TArgs&&... _args) {
      // Pause current state
      if (!m_states.empty()) {
        m_states.back()->pause();
      }

      // Store and init new state
      m_states.emplace_back ( make_unique<T>(forward<TArgs>(_args)...) );
      m_states.back()->init(m_engine);
    }

    void pop_state ();

    Kvant::State* peek_state () const { return m_states.back().get(); }

    void handle_events (SDL_Event& event);
    void update (const float dt);
    void draw (const float dt);

    private:
      // Stores stack of states
      vector<unique_ptr<Kvant::State>> m_states;

      // Local reference to game instance
      Kvant::Engine* m_engine;
  };
}
