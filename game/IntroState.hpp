#pragma once

// C++ Headers
#include <vector>
#include <string>

// SDL2 Headers
#include <SDL2/SDL.h>

// Third-party
#include <entityx/entityx.h>

// Kvant Headers
#include <KvantEngine/States/State.hpp>
#include <KvantEngine/CoreComponents/CNode.hpp>
#include <KvantEngine/CoreComponents/CMaterial.hpp>
#include <KvantEngine/CoreComponents/CMeshRenderer.hpp>
#include <KvantEngine/CoreComponents/CControllable.hpp>
#include <KvantEngine/CoreTypes/Vertex.hpp>
#include <KvantEngine/CoreTypes/Shader.hpp>

namespace ex = entityx;
using namespace Kvant;

struct IntroState : public Kvant::State {

  entityx::Entity create_triangle(float x, float y, float red, std::string file) {
    auto e = get_entity_manager().create();
    e.assign<CNode>(x, y);
    e.assign<CMaterial>( Shader{"../resources/shaders/default.vs", "../resources/shaders/default.frag"} );

    using namespace glm;

    vector<Vertex> vertices;
    vertices.push_back( Vertex{vec3{-0.5f, -0.5f, 0.0f}, vec3{red, 1, 0}, vec2{0.f, 0.f}} );
    vertices.push_back( Vertex{vec3{-0.5f, 0.5f, 0.0f}, vec3{red, 1, 0}, vec2{0.f, 1.f}} );
    vertices.push_back( Vertex{vec3{0.5f, 0.5f, 0.0f}, vec3{red, 1, 0}, vec2{1.f, 1.f}} );
    vertices.push_back( Vertex{vec3{0.5f, -0.5f, 0.0f}, vec3{red, 1, 0}, vec2{1.f, 0.f}} );

    vector<GLuint> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

    vector<string> textures = {file};

    e.assign<CMeshRenderer>(vertices, indices, textures);
    return e;
  }

  void on_init() override {
    spdlog::get("log")->info("Inside CIntroState");

    m_texture_resources.add("C.png");
    m_texture_resources.add("brick.png");

    auto e = create_triangle(0, 0, 1.0, "C.png");
    auto e2 = create_triangle(0.5, 0.5, 0.0, "brick.png");
    e2.component<CNode>()->set_rotation(-10.0f);
    e2.assign<CControllable>();
    // e.component<CNode>()->set_rotation(45.f);
    // e.component<CNode>()->add_child(e2);

    add_to_layer (State::GameLayer::FOREGROUND, e);
    add_to_layer(State::GameLayer::FOREGROUND, e2);
  }

  void on_cleanup() override {
  }

  void on_pause() override {
  }

  void on_resume() override {
  }

  void on_handle_events(SDL_Event&) override {
  }
  void on_update(const float ) override {
  }
  void on_draw(const float) override {
  }
};
