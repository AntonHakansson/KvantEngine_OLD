#include <Core/StateManager.hpp>

namespace Kvant {

  void StateManager::cleanup () {
    // Cleanup all states
    while (!m_states.empty()) {
      m_states.back()->cleanup();
      m_states.pop_back();
    }
  }

  void StateManager::pop_state() {
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

  void StateManager::handle_events(SDL_Event& event) {
    if (m_states.empty()) return;
    m_states.back()->handle_events(event);
  }
  void StateManager::update(const float dt) {
    if (m_states.empty()) return;
    m_states.back()->update(dt);
  }
  void StateManager::draw(const float dt) {
    if (m_states.empty()) return;
    m_states.back()->draw(dt);
  }

}
