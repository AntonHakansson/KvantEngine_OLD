#pragma once

// C++ Headers
#include <vector>

// SDL2 Headers
#include <SDL2/SDL.h>

// Kvant Headers
#include <CoreTypes/GameState.hpp>
#include <Core/game.hpp>

namespace Kvant {
  
  using namespace std;
  
  struct StateManager {

    void cleanup() {
      // Cleanup all states
      while (!m_states.empty()) {
        m_states.back()->cleanup();
        m_states.pop_back();
      }
    }

    void change_state(GameState* state) {
      // cleanup current state
      if (!m_states.empty()) {
        m_states.back()->cleanup();
        m_states.pop_back();
      }

      // Store and init new state
      m_states.push_back(state);
      m_states.back()->init();
    }

    void push_state(GameState* state) {
      // Pause current state
      if (!m_states.empty()) {
        m_states.back()->pause();
      }

      // Store and init new state
      m_states.push_back(state);
      m_states.back()->init();
    }

    void pop_state() {
      // Cleaup current state
      if (!m_states.empty()) {
        m_states.back()->cleanup();
        m_states.pop_back();
      }

      // Resume previous state
      if (!m_states.empty()) {
        m_states.back()->resume();
      }
    }

    void handle_events(Kvant::Game* game, SDL_Event& event) {
      if (m_states.empty()) return;
      m_states.back()->handle_events(game, event);
    }
    void update(Kvant::Game* game, float ft) {
      if (m_states.empty()) return;
      m_states.back()->update(game, ft);
    }
    void draw(Kvant::Game* game) {
      if (m_states.empty()) return;
      m_states.back()->draw(game);
    }

    private:
      // Stores stack of states
      vector<GameState*> m_states;
  };
}
