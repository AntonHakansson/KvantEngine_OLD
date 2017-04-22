#pragma once

// SDL2 Headers
#include <SDL2/SDL.h>

// Third-party
#include <entityx/entityx.h>

namespace Kvant {

  namespace ex = entityx;

  struct InputEvent { 
    SDL_Event event;
    InputEvent(SDL_Event evt) : event(evt){}
  };
}
