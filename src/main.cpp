// c++ standard libraries

// Third party
#include <spdlog/spdlog.h>

// Kvant
#include <game.hpp>

namespace spd = spdlog;
int main(int, char**) {
  // Console logger with color
  auto console = spd::stdout_color_mt("console");
  console->info("Welcome to KvantEngine!");

  Kvant::Game{}.run();
  return 0;
}
