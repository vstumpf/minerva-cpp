#ifndef MINERVA_CORE_MODEMANAGER_HPP_
#define MINERVA_CORE_MODEMANAGER_HPP_

#include <memory>
#include <string>

#include "modes/LoginMode.hpp"
#include "modes/Mode.hpp"

/**
 * Handle the current mode and switching to the next
 * Things like Login, Char Select, each Map
 */
class ModeManager {
 public:
  ModeManager(ModeType modeType, const std::string& mapName);

  void run();
  void changeMode(ModeType modeType, const std::string& mapName);
  void stop();
  Mode* getCurrentMode() const;

 private:
  std::string currentModeName_{};
  std::string nextModeName_{};
  Mode* currentMode_{nullptr};
  ModeType currentModeType_{};
  ModeType nextModeType_{};
  bool running_{false};
};

#endif  // MINERVA_CORE_MODEMANAGER_HPP_
