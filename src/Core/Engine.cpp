#include <Core/Engine.hpp>

namespace Kvant {

  Engine::Engine () : m_game_config("../resources/config.yaml"), m_window(this), m_state_manager(this), m_log(spd::stdout_color_mt("log")) {
    m_log->info("Welcome to KvantEngine.");
    m_window.init();
  }

  Engine::~Engine () {
  }

  void Engine::run () {
    m_log->info("Entering main game loop");

    while (m_running) {
      auto time_point1(chrono::high_resolution_clock::now());
      events_phase();
      update_phase();
      draw_phase();

      auto time_point2(chrono::high_resolution_clock::now());
      auto elapsed_time(time_point2 - time_point1);
      m_dt = chrono::duration_cast<chrono::duration<float, milli>>(elapsed_time).count();
    }
    cleanup_phase();
  }

  void Engine::quit () {
    m_running = false;
  }

  void Engine::events_phase () {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (handle_quit_events(event)) break;
      m_state_manager.handle_events(event);
    }
  }

  void Engine::update_phase () {
    m_state_manager.update(m_dt);
  }

  void Engine::draw_phase () {
    glClearColor(0.0, 0.0, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_state_manager.draw(m_dt);

    SDL_GL_SwapWindow(m_window.get_window());
  }

  void Engine::cleanup_phase () {
    m_window.cleanup();
    m_state_manager.cleanup();
  }

  bool Engine::handle_quit_events (const SDL_Event& event) {
    if (event.type == SDL_QUIT) {
      m_running = false;
      return true;
    }

    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          m_running = false;
          return true;
          break;
        default:
          break;
      }
    }

    return false;
  }

}
