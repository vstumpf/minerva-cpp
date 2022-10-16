#include "core/ModeManager.hpp"

ModeManager::ModeManager(
	ModeType mode_type,
	const std::string& map_name)
	:	currentModeType_(mode_type),
	currentModeName_(map_name)
{

}

void ModeManager::run() {
	currentMode_ = new LoginMode();
	currentMode_->run();
	delete currentMode_;
}

void ModeManager::changeMode(ModeType mode_type, const std::string& map_name) {

}
void ModeManager::stop() {
	running_ = false;
}

Mode* ModeManager::getCurrentMode() const {
	return currentMode_;
}