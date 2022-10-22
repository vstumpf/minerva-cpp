#ifndef MINERVA_MODES_LOGINMODE_HPP_
#define MINERVA_MODES_LOGINMODE_HPP_

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "game_objects/RenderObject.hpp"
#include "modes/Mode.hpp"

class LoginMode : public Mode {
 public:
  LoginMode();

  void init() override;
  int run() override;
  void exit() override;

  void update();

 private:
  glm::vec3 playerPos{0.f, 0.f, 0.f};

  minerva::render::RenderObject growlithe_;
  minerva::render::RenderObject growlithe2_;
};

#endif  // MINERVA_MODES_LOGINMODE_HPP_
