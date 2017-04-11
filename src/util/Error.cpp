#include <util/Error.hpp>

namespace Kvant {

  namespace error {

    void check_sdl_error(int line) {
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
