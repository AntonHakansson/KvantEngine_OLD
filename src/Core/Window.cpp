#include <Core/Window.hpp>
#include <Core/Engine.hpp>

namespace Kvant {
  using namespace std;

  /******************************/
  /********    Window    ********/
  /******************************/
  bool Window::init () {
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      spdlog::get("log")->error("Failed to init SDL:\n{}", SDL_GetError());
      return false;
    }

    // Initialize SDL_Image
    auto img_flags = IMG_INIT_PNG | IMG_INIT_PNG | IMG_INIT_TIF;
    if (! (IMG_Init(img_flags) & img_flags)) {
      spdlog::get("log")->error("Failed to init SDL_Image:\n{}", IMG_GetError());
      return false;
    }

    // Create our window centered at 512x512 resolution
    auto config = m_engine->get_game_config().get<WindowConfig>();
    int flags = SDL_WINDOW_OPENGL | (config->fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    m_main_window = SDL_CreateWindow(
        config->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        config->width, config->height, flags);

    // Check that everything worked out okay
    if (!m_main_window) {
      namespace spd = spdlog;
      spdlog::get("log")->error("Unable to create window");
      Kvant::error::check_sdl_error(__LINE__);
      return false;
    }

    set_gl_attributes ();

    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval (1);

    // Create our opengl context and attach it to our window
    m_main_context = SDL_GL_CreateContext (m_main_window);

    // Init GLEW
    // Apparently, this is needed for Apple. Thanks to Ross Vander for letting me know
    #ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit ();
    #endif

    return true;
  }

  bool Window::set_gl_attributes () {
    // Set our OpenGL version.
    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Turn on double buffering with a 24bit Z buffer.
    // You may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

    // Enable face culling, I.e. save fragment shader calls by not rendering backside of face
    glEnable (GL_CULL_FACE);
    glCullFace (GL_BACK);
    glFrontFace (GL_CCW);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
  }

  void Window::cleanup () {
    // Delete our OpengL context
    SDL_GL_DeleteContext(m_main_context);

    // Destroy our window
    SDL_DestroyWindow(m_main_window);

    // Quit SDL_Image
    IMG_Quit();

    // Shutdown SDL 2
    SDL_Quit();
  }
}
