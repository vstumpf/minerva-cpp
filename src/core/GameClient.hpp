#ifndef MINERVA_CORE_GAMECLIENT_HPP_
#define MINERVA_CORE_GAMECLIENT_HPP_

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <memory>
#include <string>

#include <core/ModeManager.hpp>
#include <render/Window.hpp>

namespace minerva {

class GameClient {
 public:
  GameClient();
  ~GameClient();

  bool initialize();
  void run();

 private:
  bool loadConfiguration(const std::string& fileName);

 private:
  std::shared_ptr<render::Window> window_{nullptr};
  std::shared_ptr<ModeManager> modeManager_{nullptr};

  bool fullScreen_{false};
  int windowWidth_{640};
  int windowHeight_{480};
  bool vsync_{false};
  unsigned int msaa_{0};
  std::string fontFolder_{""};
};

}  // namespace minerva

#endif /* MINERVA_CORE_GAMECLIENT_HPP_ */
