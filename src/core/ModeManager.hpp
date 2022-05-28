#ifndef MINERVA_CORE_MODEMANAGER_HPP_
#define MINERVA_CORE_MODEMANAGER_HPP_

#include <string>
#include <memory>

#include "render/Renderer.hpp"

#include "modes/Mode.hpp"
#include "modes/LoginMode.hpp"

class ModeManager {
public:
	ModeManager(ModeType mode_type, const std::string& map_name, std::shared_ptr<Renderer> renderer);

	void run();
	void changeMode(ModeType mode_type, const std::string& map_name);
	void stop();
	Mode* getCurrentMode() const;

private:
	bool running_{false};
	Mode* currentMode_{nullptr};
	std::string currentModeName_;
	ModeType currentModeType_;
	std::string nextModeName_;
	ModeType nextModeType_;
	std::shared_ptr<Renderer> renderer_;
};

#endif  // MINERVA_CORE_MODEMANAGER_HPP_
