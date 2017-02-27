#include "window.hpp"

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

  void Window::loadConfig() {
    ifstream i{"../resources/config.json"};
    json j;
    i >> j;
    config = j["window"].get<WindowConfig>();

    // Log read data
    BOOST_LOG_TRIVIAL(info) << "Read window config. title: \"" << config.title << "\", width: " << config.width << ", height: " << config.height;
  }

  void Window::saveConfig() {
    ofstream o("../resources/config.json");
    json j;
    j["window"] = config;
    o << j;
  }

  /******************************/
  /********    Window    ********/
  /******************************/
  bool Window::init() {
    loadConfig();

    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      cout << "Failed to init SDL\n";
      return false;
    }

    // Create our window centered at 512x512 resolution
    mainWindow = SDL_CreateWindow(config.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      config.width, config.height, SDL_WINDOW_OPENGL);

      // Check that everything worked out okay
    if (!mainWindow) {
      std::cout << "Unable to create window\n";
      CheckSDLError(__LINE__);
      return false;
    }

    // Create our opengl context and attach it to our window
    mainContext = SDL_GL_CreateContext(mainWindow);

    setOpenGLAttributes();

    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

    // Init GLEW
    // Apparently, this is needed for Apple. Thanks to Ross Vander for letting me know
    #ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
    #endif

    return true;
  }

  bool Window::setOpenGLAttributes() {
    // Set our OpenGL version.
    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Turn on double buffering with a 24bit Z buffer.
    // You may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return true;
  }

  void Window::cleanup() {
    // Delete our OpengL context
    SDL_GL_DeleteContext(mainContext);

    // Destroy our window
    SDL_DestroyWindow(mainWindow);

    // Shutdown SDL 2
    SDL_Quit();
  }
}
