#pragma once

// SDL2 Headers
#include <SDL2/SDL.h>

// Kvant Headers
#include <Core/Game.hpp>

namespace Kvant {

  struct Game;

  struct GameState {
    
    virtual void init() = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handle_events(Kvant::Game* game, SDL_Event& event) = 0;
    virtual void update(Kvant::Game* game, float ft) = 0;
    virtual void draw(Kvant::Game* game) = 0;

    protected: GameState() {};
  };
}
