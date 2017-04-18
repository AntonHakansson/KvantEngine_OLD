// c++ standard libraries
#include <memory>

// Kvant
#include <Core/Engine.hpp>
#include <States/IntroState.hpp>

namespace spd = spdlog;
int main(int, char**) {

  auto engine = std::make_unique<Kvant::Engine>();
  engine->get_state_manager().push_state<IntroState>();
  engine->run();

  return 0;
}
