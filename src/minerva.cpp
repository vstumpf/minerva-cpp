#include <stdlib.h>

#define SDL_MAIN_HANDLED


#include "common/debug.hpp"
#include "core/GameClient.hpp"

int main(int argc, char* argv[]) {
#ifdef MINERVA_DEBUG
  spdlog::get(MINERVA_LOGGER_NAME)->set_level(spdlog::level::debug);
#endif

  GameClient game;

  if (!game.Initialize()) {
    return EXIT_FAILURE;
  }

  game.Run();

  return EXIT_SUCCESS;
}
