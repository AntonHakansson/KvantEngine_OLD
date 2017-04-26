#pragma once

// C++ Headers
#include <vector>

// SDL2 Headers
#include <SDL2/SDL.h>

// Third-party
#include <entityx/entityx.h>
#include <entityx/deps/Dependencies.h>

// Kvant Headers
#include <Core/ResourceManager.hpp>
#include <CoreTypes/Texture.hpp>

namespace Kvant {

  namespace ex = entityx;

  // Forward declarations
  class Engine;
  struct StateManager;

  class State {
  public:

    enum GameLayer {
      BACKGROUND = 0,
      MIDDLEGROUND,
      FOREGROUND,
      UI,
      TOTAL
    };

    State ();
    virtual ~State () {};
    void init (Engine* engine);
    void cleanup ();

    void pause ();
    void resume ();

    void handle_events (SDL_Event& event);
    void update (const float dt);
    void draw (const float dt);

    void add_to_layer (int layer, ex::Entity entity);
    ex::Entity get_layer (int layer);

    ex::EventManager& get_event_manager () { return m_entityx.events; }
    ex::EntityManager& get_entity_manager () { return m_entityx.entities; }
    ex::SystemManager& get_system_manager () { return m_entityx.systems; }

    const ResourceManager<Texture>& get_texture_resources() { return m_texture_resources; };

  protected:
    ex::EntityX m_entityx;
    std::vector<ex::Entity> m_layers;

    ex::Entity m_GUI_camera, m_game_camera;

    ResourceManager<Texture> m_texture_resources;

    Engine* m_engine;
    friend struct StateManager;

  private:

    virtual void on_init (){};
    virtual void on_cleanup (){};

    virtual void on_pause (){};
    virtual void on_resume (){};

    virtual void on_handle_events (SDL_Event&){};
    virtual void on_update (const float){};
    virtual void on_draw (const float){};

  };
}
