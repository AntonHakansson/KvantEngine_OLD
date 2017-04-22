#include <States/State.hpp>

// Kvant Headers
#include <Core/Engine.hpp>
#include <CoreEvents/InputEvent.hpp>
#include <CoreComponents/CCamera.hpp>
#include <CoreComponents/CControllable.hpp>
#include <CoreSystems/NodeSystem.hpp>
#include <CoreSystems/RenderSystem.hpp>
#include <CoreSystems/InputSystem.hpp>

namespace Kvant {

  State::State() {}

  void State::init (Engine* engine) {
    m_engine = engine;

    auto resources = m_engine->get_game_config().get<ResourcesConfig>();
    m_texture_resources.set_base_path(resources->textures_path);

    // Setup core systems
    get_system_manager().add<NodeSystem> ();
    get_system_manager().add<RenderSystem> ();
    get_system_manager().add<InputSystem> (get_entity_manager());

    // Configure
    get_system_manager().configure ();

    //Setup layers.
  	for(int l = 0; l < State::GameLayer::TOTAL; l++) {
  		ex::Entity layer = get_entity_manager().create();
      layer.assign<CNode>(0.f, 0.f);
      m_layers.push_back(layer);
    }

    // Construct Cameras
    m_GUI_camera = get_entity_manager().create();
    m_GUI_camera.assign<CCamera>();

    m_game_camera = get_entity_manager().create();
    auto config = m_engine->get_game_config().get<WindowConfig>();
    m_game_camera.assign<CCamera>(glm::vec3(0.f, 0.f, 1.f), glm::radians(60.0f), config->width / config->height, 0.1f, 10.0f);
    m_game_camera.assign<CControllable>();

    on_init();
  }

  void State::cleanup () {
    on_cleanup();
  }

  void State::pause () {
    on_pause();
  }

  void State::resume () {
    on_resume();
  }

  void State::handle_events (SDL_Event& event) {
    get_event_manager().emit<InputEvent>(event);
    on_handle_events(event);
  }

  void State::update (const float dt) {
    get_system_manager().update<NodeSystem>(dt);
    get_system_manager().update<InputSystem>(dt);

    on_update(dt);
  }

  void State::draw (const float dt) {
    // Render game
    get_system_manager().system<RenderSystem>()->set_camera( m_game_camera );
    for (unsigned int l{0u}; l < GameLayer::UI; l++) {
      get_system_manager().system<RenderSystem>()->set_render_root( m_layers[l] );
      get_system_manager().update<RenderSystem>(dt);
    }

    // Render GUI
    get_system_manager().system<RenderSystem>()->set_camera( m_GUI_camera );
    for (unsigned int l{GameLayer::UI}; l < GameLayer::TOTAL; l++) {
      get_system_manager().system<RenderSystem>()->set_render_root( m_layers[l] );
      get_system_manager().update<RenderSystem>(dt);
    }

    on_draw(dt);
  }

  void State::add_to_layer (int layer, ex::Entity entity) {
    if(layer >= 0 && layer < State::GameLayer::TOTAL) {
      m_layers[layer].component<CNode>()->add_child(entity);
    }
  }

  ex::Entity State::get_layer (int layer) {
    if (layer >= 0 && layer < State::GameLayer::TOTAL)
        return m_layers[layer];

    ex::Entity empty;
    return empty;
  }
}
