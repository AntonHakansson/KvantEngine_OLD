#pragma once

#include <string>

#include <spdlog/spdlog.h>

// SDL2 Headers
#include <SDL2/SDL.h>


static void CheckSDLError(int line = -1) {
  using namespace std;
  string error = SDL_GetError();

  if (error != "") {
    spdlog::get("console")->error("SLD Error : " + error);

    if (line != -1)
    spdlog::get("console")->error("SLD Error Line: " + line);

    SDL_ClearError();
  }
}
