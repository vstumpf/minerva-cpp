#ifndef MINERVA_MODES_MODE_HPP_
#define MINERVA_MODES_MODE_HPP_

#include <memory>

#include "render/Camera.hpp"

enum class ModeType {
  LOGIN,
};

class Mode {
 public:
  Mode();
  virtual ~Mode() = default;

  virtual void init() = 0;
  virtual int run() = 0;
  virtual void exit() = 0;

  bool getShouldLoop() const;
  void setShouldLoop(bool shouldLoop);
  Camera& Mode::getCamera();

 private:
  bool shouldLoop_{true};
  Camera camera{};
};

#endif  // MINERVA_MODES_MODE_HPP_
