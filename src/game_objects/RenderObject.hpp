#ifndef MINERVA_GAMEOBJECT_RENDEROBJECT_HPP_
#define MINERVA_GAMEOBJECT_RENDEROBJECT_HPP_

#include <glm/glm.hpp>
#include "files/BmpResource.hpp"
#include "render/Camera.hpp"
#include "render/Surface.hpp"

namespace minerva::render {

/*
 * Render Objects are game objects that can be rendered.
 * These use the sprite shaders, so it will be billboarded.
 */
class RenderObject {
 public:
  RenderObject();

  void render(const Camera& view);

  void setPos(glm::vec3 position);
  const glm::vec3& getPos() const;

 protected:
  glm::vec3 pos_{0.f};
  BmpResource spriteResource_;
  Surface surface_;
};

}  // namespace minerva::render

#endif /* MINERVA_GAMEOBJECT_RENDEROBJECT_HPP_ */
