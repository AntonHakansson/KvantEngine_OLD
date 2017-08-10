#pragma once

// C++ Headers
#include <string>

#include <boost/filesystem.hpp>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

// SDL2 Headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Third party
#include <spdlog/spdlog.h>

// Kvant Headers
#include <KvantEngine/CoreTypes/Resource.hpp>

namespace Kvant {
  using namespace std;

  struct Texture : public Resource {
    Texture (const ResourceHandle handle, const boost::filesystem::path& filepath) : Resource(handle, filepath) {
      glGenTextures(1, &m_id);
      glBindTexture(GL_TEXTURE_2D, m_id);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glBindTexture(GL_TEXTURE_2D, 0);

      load_image(filepath);
    }

    ~Texture () {
      glDeleteTextures(1, &m_id);
    }

    void load_image (const boost::filesystem::path& filepath) {
      string file = filepath.string();
      SDL_Surface *tex = IMG_Load(file.c_str());
      if(!tex) {
        spdlog::get("log")->error("Failed to load texture {} with error:\n {}", file, IMG_GetError());
        return;
      }

      if ( (tex->w & (tex->w-1)) != 0 ) {
        spdlog::get("log")->warn("Warning: {}'s width is not a power of 2", file);
      }
      if ( (tex->h & (tex->h-1)) != 0 ) {
        spdlog::get("log")->warn("Warning: {}'s height is not a power of 2", file);
      }

      auto number_of_colors = tex->format->BytesPerPixel;
      GLenum texture_format;
      switch (number_of_colors) {
        case 4:
          if (tex->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
          else
            texture_format = GL_BGRA;
          break;
        case 3:
          if (tex->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
          else
            texture_format = GL_BGR;
          break;
        default:
          spdlog::get("log")->warn("Warning: {} is not truecolor.. could lead to undefined behavior", file);
          texture_format = GL_RGB;
          break;
      }

      glBindTexture(GL_TEXTURE_2D, m_id);

      glTexImage2D(GL_TEXTURE_2D, 0, texture_format, tex->w, tex->h,
                    0, texture_format, GL_UNSIGNED_BYTE, tex->pixels);

      SDL_FreeSurface(tex);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    void bind (GLuint unit) {
      assert (unit <= 31);
      glActiveTexture (GL_TEXTURE0 + unit);
      glBindTexture (GL_TEXTURE_2D, m_id);
    }

    GLuint m_id{0};
  };
}
