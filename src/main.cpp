#define BOOST_LOG_DYN_LINK 1
#include <boost/log/trivial.hpp>
#include "game.hpp"

int main() {
  BOOST_LOG_TRIVIAL(info) << "Kvant Engine Start";
  Game{}.run();
  return 0;
}
