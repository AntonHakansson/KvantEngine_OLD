#pragma once

// C++ Header
#include <string>

// SDL2 Headers
#include <SDL2/SDL.h>

// Third-party Headers
#include <spdlog/spdlog.h>

// TODO: put in Kvant namespace and convert to boost style
namespace Kvant {
  namespace error { 
    static void check_sdl_error(int line = -1) {
      using namespace std;
      string error = SDL_GetError();

      if (error != "") {
        spdlog::get("console")->error("SLD Error : {}",  error);

        if (line != -1)
        spdlog::get("console")->error("SLD Error Line: {}", line);

        SDL_ClearError();
      }
    }
  }
}
