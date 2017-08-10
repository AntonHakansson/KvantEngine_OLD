#include <KvantEngine/Core/Engine.hpp>

namespace Kvant {

  Engine::Engine (std::string config_dir) : m_game_config(config_dir), m_window(this), m_state_manager(this), m_log(spd::stdout_color_mt("log")) {
    m_log->info("Welcome to KvantEngine.");
    m_window.init();

    // bind imgui to window
    ImGui_ImplSdlGL3_Init (get_window().get_sdl_window());
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

      // Toggle debug menu
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F1) {
        m_imgui_state.show_debug_menu = !m_imgui_state.show_debug_menu;
      }

      ImGui_ImplSdlGL3_ProcessEvent(&event);
      m_state_manager.handle_events(event);
    }
  }

  void Engine::update_phase () {
    ImGui_ImplSdlGL3_NewFrame(get_window().get_sdl_window());
    m_state_manager.update(m_dt);
  }

  void Engine::draw_phase () {
    glClearColor(0.0, 0.0, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_state_manager.draw(m_dt);

    render_imgui();

    SDL_GL_SwapWindow(m_window.get_sdl_window());
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

  void Engine::render_imgui () {
    if (!m_imgui_state.show_debug_menu) return;
    ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);

    auto fps = 1./(m_dt/1000.);

    ImGui::Begin("KvantEngine Debug Menu");
    ImGui::Text("FPS: %f", fps);
    ImGui::Checkbox("ImGui test window", &m_imgui_state.show_imgui_debug);
    if (m_imgui_state.show_imgui_debug)
      ImGui::ShowTestWindow(&m_imgui_state.show_imgui_debug);

    ImGui::Checkbox("Node tree", &m_imgui_state.show_node_tree);
    ImGui::Checkbox("Inspector", &m_imgui_state.show_inspector);
    ImGui::End();

    ImGui::Render();
  }

}
