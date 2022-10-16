#ifndef MINERVA_CORE_MODEMANAGER_HPP_
#define MINERVA_CORE_MODEMANAGER_HPP_

#include <memory>
#include <string>

#include "modes/LoginMode.hpp"
#include "modes/Mode.hpp"

class ModeManager {
 public:
  ModeManager(ModeType modeType, const std::string& mapName);

  void run();
  void changeMode(ModeType modeType, const std::string& mapName);
  void stop();
  Mode* getCurrentMode() const;

 private:
  bool running_{false};
  Mode* currentMode_{nullptr};
  std::string currentModeName_;
  ModeType currentModeType_;
  std::string nextModeName_;
  ModeType nextModeType_;
};

#endif  // MINERVA_CORE_MODEMANAGER_HPP_
