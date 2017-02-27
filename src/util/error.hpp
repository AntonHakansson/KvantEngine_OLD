#pragma once

// SDL2 Headers
#include <SDL2/SDL.h>

static void CheckSDLError(int line = -1) {
  std::string error = SDL_GetError();

  if (error != "") {
    std::cout << "SLD Error : " << error << std::endl;

    if (line != -1)
    	std::cout << "\nLine : " << line << std::endl;

    SDL_ClearError();
  }
}
