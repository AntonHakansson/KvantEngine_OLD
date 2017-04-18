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

// third-party Headers
#include <json/json.hpp>
#include <spdlog/spdlog.h>

// Kvant Headers
#include <util/Error.hpp>

namespace Kvant {
  // for convenience
  using json = nlohmann::json;
  using namespace std;
  using namespace Kvant;

  class Engine;

  struct WindowConfig {
    unsigned int width, height;
    string title;
  };

  struct Window {
    Window(Kvant::Engine* engine) : m_engine(engine) {}

    bool init ();
    bool set_gl_attributes ();
    void cleanup ();

    void load_config ();
    void save_config ();

    SDL_Window* get_window () const { return m_main_window; };
    const SDL_GLContext& get_context () const { return m_main_context; };
    const WindowConfig& get_config () const { return m_config; };

    private:
      SDL_Window *m_main_window;
      SDL_GLContext m_main_context;
      WindowConfig m_config;
      Engine* m_engine;
  };
}
