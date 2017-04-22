#include <CoreSystems/InputSystem.hpp>
#include <CoreEvents/InputEvent.hpp>
#include <CoreComponents/CControllable.hpp>

namespace Kvant {

  InputSystem::InputSystem(ex::EntityManager& entity_manager) : m_entity_manager(entity_manager) {

  }

  InputSystem::~InputSystem() {

  }

  void InputSystem::configure(ex::EventManager& events) {
    events.subscribe<InputEvent>(*this);
  }

  void InputSystem::update (ex::EntityManager& entities, ex::EventManager&, ex::TimeDelta) {
    for (auto entity : entities.entities_with_components<CNode, CControllable>()) {
      auto controller = entity.component<CControllable>();
      controller->control(entity, SDL_Event());
    }
  }

  void InputSystem::receive (const InputEvent&) {
  }
}
