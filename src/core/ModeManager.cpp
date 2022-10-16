#include "core/ModeManager.hpp"

ModeManager::ModeManager(ModeType modeType, const std::string& mapName)
    : currentModeType_(modeType), currentModeName_(mapName) {}

void ModeManager::run() {
  currentMode_ = new LoginMode();
  currentMode_->run();
  delete currentMode_;
}

void ModeManager::changeMode(ModeType modeType, const std::string& mapName) {}
void ModeManager::stop() {
  running_ = false;
}

Mode* ModeManager::getCurrentMode() const {
  return currentMode_;
}