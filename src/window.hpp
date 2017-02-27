#pragma once

#ifndef WINDOW_H
#define WINDOW_H

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

// SDL2 Headers
#include <SDL2/SDL.h>

#define BOOST_LOG_DYN_LINK 1
#include <boost/log/trivial.hpp>


#include <string>       // std::string
#include <fstream>      // std::ifstream
#include <ostream>      // std::ostream

#include "third-party/json.hpp"
#include "util/error.hpp"

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
    bool setOpenGLAttributes();
    void cleanup();

    void loadConfig();
    void saveConfig();

    SDL_Window* getWindow() const { return mainWindow; };
    const SDL_GLContext& getContext() const { return mainContext; };
    const WindowConfig& getConfig() const { return config; };

    private:
      SDL_Window *mainWindow;
      SDL_GLContext mainContext;
      WindowConfig config;
  };
}

#endif
