#include <CoreTypes/GameState.hpp>

namespace Kvant {
  void GameState::change_state(GameState* state) {
    if(m_state_manager == nullptr) return;
    m_state_manager->change_state(state);
  }
}
