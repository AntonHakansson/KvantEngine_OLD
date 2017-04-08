#pragma once

#ifndef WINDOW_H
#define WINDOW_H

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
#include <util/error.hpp>

namespace Kvant {
  // for convenience
  using json = nlohmann::json;
  using namespace std;

  struct WindowConfig {
    unsigned int width, height;
    string title;
  };

  struct Window {
    bool init();
    bool set_gl_attributes();
    void cleanup();

    void load_config();
    void save_config();

    SDL_Window* get_window() const { return m_main_window; };
    const SDL_GLContext& get_context() const { return m_main_context; };
    const WindowConfig& get_config() const { return m_config; };

    private:
      SDL_Window *m_main_window;
      SDL_GLContext m_main_context;
      WindowConfig m_config;
  };
}

#endif
