#pragma once

// C++ Headers

// SDL2 Headers
#include <SDL2/SDL.h>

// Kvant Headers
#include <CoreTypes/GameState.hpp>

struct IntroState : public Kvant::GameState {

  void init() override {

  }
 
  void cleanup() override {

  }
  
  void pause() override {
  
  }
 
  void resume() override {
  }

  void handle_events(Kvant::Game* game, SDL_Event& event) override {
  }
  void update(Kvant::Game* game, float ft) override {
  }
  void draw(Kvant::Game* game) override {
  }
};
