#pragma once

#include <iostream>
#include <chrono>
#include <functional>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

// SDL2 Headers
#include <SDL2/SDL.h>

#include "entitySystem.hpp"
#include "window.hpp"

using namespace std;

using FrameTime = float;

constexpr float ballRadius{10.f}, ballVelocity{0.8f};
constexpr float paddleWidth{60.f}, paddleHeight{20.f}, paddleVelocity{0.6f};
constexpr float blockWidth{60.f}, blockHeight{20.f};
constexpr int countBlocksX{11}, countBlocksY{4};
constexpr float ftStep{1.f}, ftSlice{1.f};

struct Game {
  Kvant::Window window;
  Manager manager;
  bool running;
  FrameTime lastFt{0.f}, currentSlice{0.f};

  Game() {
    window.init();
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

      auto ftSeconds(ft / 1000.f);
      auto fps(1.f / ftSeconds);
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
  }

  void cleanupPhase() {
    window.cleanup();
  }
};
