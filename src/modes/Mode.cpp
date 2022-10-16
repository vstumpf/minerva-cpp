

#include "modes/Mode.hpp"

Mode::Mode() {}

bool Mode::getShouldLoop() const {
  return shouldLoop_;
}

void Mode::setShouldLoop(bool shouldLoop) {
  shouldLoop_ = shouldLoop;
}

Camera& Mode::getCamera() {
  return camera;
}