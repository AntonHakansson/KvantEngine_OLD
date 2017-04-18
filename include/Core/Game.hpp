#pragma once

// C++ Headers
#include <iostream>
#include <chrono>
#include <functional>
#include <vector>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <glm/glm.hpp>

// SDL2 Headers
#include <SDL2/SDL.h>

// Third party
#include <spdlog/spdlog.h>

// Kvant Headers
#include <Core/EntitySystem.hpp>
#include <Core/Window.hpp>

#include <Core/StateManager.hpp>
#include <CoreTypes/GameState.hpp>
#include <CoreTypes/Vertex.hpp>
#include <CoreTypes/Texture.hpp>
#include <CoreTypes/Shader.hpp>
#include <CoreComponents/Material.hpp>
#include <CoreComponents/Mesh.hpp>

namespace Kvant {

using namespace std;
using namespace Kvant;

using FrameTime = float;

constexpr float ft_step{1.f}, ft_slice{1.f};

enum game_layers : std::size_t {
  mesh_renderers,
  ui
};

//!Game class
struct Game {

  Entity& create_triangle() {
    auto& e(m_entity_manager.add_entity());
    e.add_component<CMaterial>( Shader{"../resources/shaders/default.vs", "../resources/shaders/default.frag"} );

    using namespace glm;

    vector<Vertex> vertices;
    vertices.push_back( Vertex{vec3{-0.5f, -0.5f, 0.0f}, vec3{1, 0, 0}, vec2{0, 0}} );
    vertices.push_back( Vertex{vec3{0.5f, -0.5f, 0.0f}, vec3{1, 0, 0}, vec2{0, 0}} );
    vertices.push_back( Vertex{vec3{0.0f, 0.5f, 0.0f}, vec3{1, 0, 0}, vec2{0, 0}} );

    vector<GLuint> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    vector<Texture> textures;

    e.add_component<CMeshFilter>(vertices, indices, textures);
    e.add_component<CMeshRenderer>();

    return e;
  }

  Game() : m_state_manager(this) {
    m_window.init();
    create_triangle();
  }

  void run() {
    spdlog::get("console")->info("Entering main game loop");
    while(m_running) {
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

  void events_phase() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        m_running = false;
        break;
      }

      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            m_running = false;
            break;
          default:
            break;
        }
      }

      m_state_manager.handle_events(m_dt);
    }
  }


  void update_phase() {
    m_current_slice += m_dt;
    for(; m_current_slice >= ft_slice; m_current_slice -= ft_slice) {
      m_entity_manager.refresh();
      m_entity_manager.update(ft_step);
      m_state_manager.update(m_dt);
    }
  }

  void draw_phase() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto& mesh_renderers(m_entity_manager.get_entities_by_group(game_layers::mesh_renderers));
    for(auto& mesh : mesh_renderers) {
      mesh->get_component<CMeshRenderer>().draw();
    }

    m_state_manager.draw(m_dt);

    SDL_GL_SwapWindow(m_window.get_window());
  }

  void cleanup_phase() {
    m_state_manager.cleanup();
    m_window.cleanup();
  }

  StateManager& get_state_manager() { return m_state_manager; }

private:
  Window m_window;
  StateManager m_state_manager;
  Manager m_entity_manager;
  bool m_running{true};
  FrameTime m_current_slice{0.f};
  FrameTime m_dt{0.f};
};

}
