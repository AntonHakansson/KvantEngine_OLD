#pragma once

// C++ Headers

// SDL2 Headers
#include <SDL2/SDL.h>

// Kvant Headers
#include <CoreTypes/GameState.hpp>

struct IntroState2 : public Kvant::GameState {

  void init() override {
    spdlog::get("console")->info("Inside CIntroState");
  }

  void cleanup() override {

  }

  void pause() override {

  }

  void resume() override {
  }

  void handle_events(const float) override {
  }
  void update(const float) override {
  }
  void draw(const float) override {
  }
};
