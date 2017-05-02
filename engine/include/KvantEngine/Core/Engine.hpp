#pragma once

// C++ Headers
#include <string>
#include <chrono>

// SDL2 Headers
#include <SDL2/SDL.h>

// Third party
#include <spdlog/spdlog.h>

// Kvant Headers
#include <KvantEngine/Core/GameConfig.hpp>
#include <KvantEngine/Core/StateManager.hpp>
#include <KvantEngine/Core/Window.hpp>
#include <KvantEngine/imgui/imgui_impl_sdl_gl3.h>

namespace Kvant {

  using namespace Kvant;
  namespace spd = spdlog;

  using Logger = std::shared_ptr<spd::logger>;

  class Engine {
  public:
    Engine (std::string config_dir);
    ~Engine ();

    void run ();
    void quit ();

    GameConfig& get_game_config () { return m_game_config; }
    StateManager& get_state_manager () { return m_state_manager; }
    Window& get_window () { return m_window; }
    Logger& get_logger () { return m_log; }

  private:
    void events_phase ();
    void update_phase ();
    void draw_phase ();
    void cleanup_phase ();

    bool handle_quit_events (const SDL_Event& event);

    GameConfig m_game_config;
    Window m_window;
    StateManager m_state_manager;
    Logger m_log;

    bool m_running {true};
    float m_dt {0.f};
  };

}
