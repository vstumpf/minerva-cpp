#include "core/ModeManager.hpp"

ModeManager::ModeManager(
	ModeType mode_type,
	const std::string& map_name,
	std::shared_ptr<Renderer> renderer)
	:	currentModeType_(mode_type),
	currentModeName_(map_name),
	renderer_(renderer)
{

}

void ModeManager::run() {
	currentMode_ = new LoginMode(renderer_);
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