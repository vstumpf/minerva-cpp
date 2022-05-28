

#include "modes/Mode.hpp"

Mode::Mode(std::shared_ptr<Renderer> renderer)
	: renderer_(renderer) {

}

bool Mode::getShouldLoop() const {
	return shouldLoop_;
}

void Mode::setShouldLoop(bool shouldLoop) {
	shouldLoop_ = shouldLoop;
}

