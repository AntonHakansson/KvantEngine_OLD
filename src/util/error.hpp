#pragma once

// C++ Header
#include <string>

// SDL2 Headers
#include <SDL2/SDL.h>

// Third-party Headers
#include <spdlog/spdlog.h>

namespace Kvant {
  namespace error { 
    void check_sdl_error(int line = -1); 
  }
}
