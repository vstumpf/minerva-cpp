#include <stdlib.h>

#define SDL_MAIN_HANDLED

#include "common/debug.hpp"
#include "core/GameClient.hpp"

int main(int argc, char* argv[]) {
#ifdef MINERVA_DEBUG
  spdlog::get(MINERVA_LOGGER_NAME)->set_level(spdlog::level::debug);
#endif

#ifdef MINERVA_GL_DEBUG
  spdlog::get(MINERVA_GL_LOGGER_NAME)->set_level(spdlog::level::debug);
#endif

  minerva::GameClient game;

  if (!game.initialize()) {
    return EXIT_FAILURE;
  }

  game.run();

  return EXIT_SUCCESS;
}
