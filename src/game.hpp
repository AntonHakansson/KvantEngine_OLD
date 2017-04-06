#pragma once

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

#include <entitySystem.hpp>
#include <window.hpp>

#include <types/Vertex.hpp>
#include <types/Texture.hpp>
#include <types/Shader.hpp>
#include <components/Material.hpp>
#include <components/mesh.hpp>

using namespace std;
using namespace Kvant;

using FrameTime = float;

constexpr float ftStep{1.f}, ftSlice{1.f};

struct Game {
  Kvant::Window window;
  Manager manager;
  bool running;
  FrameTime lastFt{0.f}, currentSlice{0.f};

  enum groups : std::size_t {
    meshRenderers
  };

  Entity& createTriangle() {
    auto& e(manager.addEntity());
    e.addComponent<CMaterial>( Shader{"../src/shaders/default.vs", "../src/shaders/default.frag"} );

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

    e.addComponent<CMeshFilter>(vertices, indices, textures);
    e.addComponent<CMeshRenderer>();
    e.addGroup(groups::meshRenderers);

    return e;
  }

  Game() {
    window.init();
    createTriangle();
  }

  void run() {
    while(running) {
      auto timePoint1(chrono::high_resolution_clock::now());

      inputPhase();
      updatePhase();
      drawPhase();

      auto timePoint2(chrono::high_resolution_clock::now());
      auto elapsedTime(timePoint2 - timePoint1);
      FrameTime ft{
          chrono::duration_cast<chrono::duration<float, milli>>(
              elapsedTime)
              .count()};

      lastFt = ft;

      // auto ftSeconds(ft / 1000.f);
      // auto fps(1.f / ftSeconds);
    }

    cleanupPhase();
  }

  void inputPhase() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        running = false;
        break;
      }

      if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
  					running = false;
  					break;
          case SDLK_r:
            glClearColor(1.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(window.getWindow());
            break;
          default:
            break;
        }
      }

    }
  }


  void updatePhase() {
    currentSlice += lastFt;
    for(; currentSlice >= ftSlice; currentSlice -= ftSlice) {
      manager.refresh();
      manager.update(ftStep);
    }
  }

  void drawPhase() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    auto& meshRenderers(manager.getEntitiesByGroup(groups::meshRenderers));
    for(auto& mesh : meshRenderers) {
      mesh->getComponent<CMeshRenderer>().draw();
    }
    
    SDL_GL_SwapWindow(window.getWindow());
  }

  void cleanupPhase() {
    window.cleanup();
  }
};
