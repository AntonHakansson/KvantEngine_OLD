// c++ standard libraries
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include <boost/filesystem.hpp>

// Kvant
#include <Core/Engine.hpp>
#include <States/IntroState.hpp>
#include <Core/GameConfig.hpp>
#include <Core/ResourceManager.hpp>

#include <spdlog/spdlog.h>

using namespace Kvant;

class TestResource : public Resource {
public:
  TestResource (const ResourceHandle handle, const boost::filesystem::path& filepath) : Resource(handle, filepath) {
    m_details = filepath.string();
  }

  ~TestResource () {
  }

  std::string get_details () { return m_details; }

private:
  std::string m_details;
};

namespace spd = spdlog;
int main(int, char**) {

  auto engine = std::make_unique<Kvant::Engine>();
  engine->get_state_manager().push_state<IntroState>();
  engine->run();

  return 0;
}
