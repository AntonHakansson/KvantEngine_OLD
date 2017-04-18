#pragma once

// C++ Headers
#include <string>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

// SDL2 Headers
#include <SDL2/SDL.h>
#include <SDL_image.h>

// Third party
#include <spdlog/spdlog.h>

namespace Kvant {
  using namespace std;

  struct Texture {

    void load_image (string file) {
      SDL_Surface *tex = SDL_LoadBMP(file.c_str());
      if(!tex) {
        spdlog::get("log")->error("Failed to load texture {}", file);
        return;
      }

      glGenTextures(1, &m_id);
      glBindTexture(GL_TEXTURE_2D, m_id);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->w, tex->h,
                    0, GL_BGR, GL_UNSIGNED_BYTE, tex->pixels);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      SDL_FreeSurface(tex);
    }

    void bind (GLuint unit) {
      assert (unit <= 31);
      glActiveTexture (GL_TEXTURE0 + unit);
      glBindTexture (GL_TEXTURE_2D, m_id);
    }

    ~Texture () {
      glDeleteTextures(1, &m_id);
    }

    GLuint m_id{0};
    string m_type;
  };
}
