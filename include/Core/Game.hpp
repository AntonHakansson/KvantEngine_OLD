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

// Kvant Headers
#include <Core/EntitySystem.hpp>
#include <Core/Window.hpp>

#include <Core/StateManager.hpp>
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

//!Game class
struct Game {

  enum groups : std::size_t {
    meshRenderers
  };

  Entity& create_triangle() {
    auto& e(m_manager.add_entity());
    e.add_component<CMaterial>( Shader{"../src/CoreShaders/default.vs", "../src/CoreShaders/default.frag"} );

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
    e.add_group(groups::meshRenderers);

    return e;
  }

  Game() {
    m_window.init();
    create_triangle();
  }

  void run() {
    while(m_running) {
      auto time_point1(chrono::high_resolution_clock::now());

      events_phase();
      update_phase();
      draw_phase();

      auto time_point2(chrono::high_resolution_clock::now());
      auto elapsed_time(time_point2 - time_point1);
      FrameTime ft{
          chrono::duration_cast<chrono::duration<float, milli>>(
              elapsed_time)
              .count()};

      m_last_ft = ft;
      // auto ftSeconds(ft / 1000.f);
      // auto fps(1.f / ftSeconds);
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

      m_state_manager.handle_events(this, event);
    }
  }


  void update_phase() {
    m_current_slice += m_last_ft;
    for(; m_current_slice >= ft_slice; m_current_slice -= ft_slice) {
      // m_manager.refresh();
      // m_manager.update(ft_step);
      m_state_manager.update(this, ft_step);
    }
  }

  void draw_phase() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
     
    auto& meshRenderers(m_manager.get_entities_by_group(groups::meshRenderers));
    for(auto& mesh : meshRenderers) {
      mesh->get_component<CMeshRenderer>().draw();
    }
    
    //m_state_manager.draw(this);
    
    SDL_GL_SwapWindow(m_window.get_window());
  }

  void cleanup_phase() {
    m_state_manager.cleanup();
    m_window.cleanup();
  }

private:
  Window m_window;
  StateManager m_state_manager;
  Manager m_manager;
  bool m_running;
  FrameTime m_last_ft{0.f}, m_current_slice{0.f};
};

}
