#ifndef MINERVA_CORE_GAMECLIENT_HPP_
#define MINERVA_CORE_GAMECLIENT_HPP_


#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <string>
#include <memory>

#include <render/Window.hpp>
#include <core/ModeManager.hpp>

namespace minerva {

class GameClient {
 public:
  GameClient();
  ~GameClient();

  bool Initialize();
  void Run();

 private:
  bool LoadConfiguration(const std::string& file_name);

 private:
	 std::shared_ptr<render::Window> window_{nullptr};
   std::shared_ptr<ModeManager> modeManager_{nullptr};

  bool fullScreen_{false};
  int window_width_{640};
  int window_height_{480};
  bool vsync_{false};
  unsigned int msaa_{0};
  std::string font_folder_{""};
};

}

#endif /* MINERVA_CORE_GAMECLIENT_HPP_ */
