#include <types/GameState.hpp>

namespace Kvant {
  void GameState::change_state(Game* game, GameState* state) {
    game->change_state(state); 
  }
}

