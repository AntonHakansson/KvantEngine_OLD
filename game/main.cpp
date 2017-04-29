// c++ standard libraries
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include <boost/filesystem.hpp>

// Kvant
#include <KvantEngine/Core/Engine.hpp>
#include "IntroState.hpp"
#include <KvantEngine/Core/GameConfig.hpp>
#include <KvantEngine/Core/ResourceManager.hpp>

#include <spdlog/spdlog.h>

using namespace Kvant;
namespace spd = spdlog;
int main(int, char**) {

  auto engine = std::make_unique<Kvant::Engine>("../resources/config.yaml");
  engine->get_state_manager().push_state<IntroState>();
  engine->run();

  return 0;
}
