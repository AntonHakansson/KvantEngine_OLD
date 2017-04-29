#include <KvantEngine/CoreComponents/CControllable.hpp>
#include <KvantEngine/CoreComponents/CNode.hpp>

namespace Kvant {

  void CControllable::control(ex::Entity& entity, const SDL_Event&) {
    auto node = entity.component<CNode>();

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_D])
      node->m_position.x += 0.01;
    if (state[SDL_SCANCODE_A])
      node->m_position.x -= 0.01;
    if (state[SDL_SCANCODE_W])
      node->m_position.y += 0.01;
    if (state[SDL_SCANCODE_S])
      node->m_position.y -= 0.01;

  }
}
