#ifndef MINERVA_CORE_GAMECLIENT_HPP_
#define MINERVA_CORE_GAMECLIENT_HPP_

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <memory>
#include <string>

#include <core/ModeManager.hpp>
#include <render/Window.hpp>

namespace minerva {

/**
 * This is the game client
 * Handles the loading of the configuration file
 */
class GameClient {
 public:
  GameClient() = default;
  ~GameClient();

  bool initialize();
  void run();

 private:
  bool loadConfiguration(const std::string& fileName);

 private:
  std::shared_ptr<render::Window> window_{nullptr};
  std::shared_ptr<ModeManager> modeManager_{nullptr};

  std::string fontFolder_{""};
  int windowWidth_{640};
  int windowHeight_{480};
  unsigned int msaa_{0};
  bool fullScreen_{false};
  bool vsync_{false};
};

}  // namespace minerva

#endif /* MINERVA_CORE_GAMECLIENT_HPP_ */
