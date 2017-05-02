#pragma once

// C++ Headers
#include <string>       // std::string
#include <fstream>      // std::ifstream
#include <ostream>      // std::ostream

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

// SDL2 Headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// third-party Headers
#include <spdlog/spdlog.h>

// Kvant Headers
#include <KvantEngine/util/Error.hpp>
#include <KvantEngine/Core/GameConfig.hpp>
#include <KvantEngine/imgui/imgui_impl_sdl_gl3.h>

namespace Kvant {
  // for convenience
  using namespace std;
  using namespace Kvant;

  class Engine;

  struct Window {
    Window(Kvant::Engine* engine) : m_engine(engine) {}

    bool init ();
    bool set_gl_attributes ();
    void cleanup ();

    void load_config ();
    void save_config ();

    SDL_Window* get_window () const { return m_main_window; };
    const SDL_GLContext& get_context () const { return m_main_context; };

    private:
      SDL_Window *m_main_window;
      SDL_GLContext m_main_context;
      Engine* m_engine;
  };
}
