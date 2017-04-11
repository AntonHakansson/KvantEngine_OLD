#include <Core/Window.hpp>

namespace Kvant {
  using namespace std;
  using nlohmann::json;

  /******************************/
  /******** WindowConfig ********/
  /******************************/
  void to_json(json& j, const WindowConfig& w) {
    j = json{{"width", w.width}, {"height", w.height}, {"title", w.title}};
  }
  void from_json(const json& j, WindowConfig& w) {
    w.width = j["width"].get<unsigned int>();
    w.height = j["height"].get<unsigned int>();
    w.title = j["title"].get<string>();
  }

  void Window::load_config() {
    ifstream i{"../resources/config.json"};
    json j;
    i >> j;
    m_config = j["window"].get<WindowConfig>();

    // Log read data
    namespace spd = spdlog;
    spdlog::get("console")->info("Read window config. title: \"{}\", width: {}, height: {}",  m_config.title, m_config.width, m_config.height);
  }

  void Window::save_config() {
    ofstream o("../resources/config.json");
    json j;
    j["window"] = m_config;
    o << j;
  }

  /******************************/
  /********    Window    ********/
  /******************************/
  bool Window::init() {
    load_config();
    
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      spdlog::get("console")->error("Failed to init SDL");
      return false;
    }

    // Create our window centered at 512x512 resolution
    m_main_window = SDL_CreateWindow(m_config.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      m_config.width, m_config.height, SDL_WINDOW_OPENGL);

      // Check that everything worked out okay
    if (!m_main_window) {
      namespace spd = spdlog;
      spdlog::get("console")->error("Unable to create window");
      Kvant::error::check_sdl_error(__LINE__);
      return false;
    }

    set_gl_attributes();

    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

    // Create our opengl context and attach it to our window
    m_main_context = SDL_GL_CreateContext(m_main_window);

    // Init GLEW
    // Apparently, this is needed for Apple. Thanks to Ross Vander for letting me know
    #ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
    #endif

    return true;
  }

  bool Window::set_gl_attributes() {
    // Set our OpenGL version.
    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Turn on double buffering with a 24bit Z buffer.
    // You may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Enable face culling, I.e. save fragment shader calls by not rendering backside of face
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    return true;
  }

  void Window::cleanup() {
    // Delete our OpengL context
    SDL_GL_DeleteContext(m_main_context);

    // Destroy our window
    SDL_DestroyWindow(m_main_window);

    // Shutdown SDL 2
    SDL_Quit();
  }
}
