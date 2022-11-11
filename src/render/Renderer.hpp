#ifndef MINERVA_CORE_RENDERER_HPP_
#define MINERVA_CORE_RENDERER_HPP_

#include <chrono>
#include <cstdint>
#include <glm/glm.hpp>
#include <memory>

#include "render/Camera.hpp"
#include "render/GlProgram.hpp"
#include "render/GlShader.hpp"
#include "render/GlVBO.hpp"
#include "render/Surface.hpp"
#include "render/Window.hpp"
#include "render/pixel_format.hpp"

namespace minerva::render {

class Window;  // forward declare

struct RenderBlockSprite3d {
  Surface* surface_;    // surface to render, usually a sprite frame
  glm::vec3 position_;  // position in world coords
  glm::vec2 offset_;    // offset from position
  glm::vec2 size_;      // scale
  float color_[4];      // tint color to apply
};

class Renderer {
 public:
  Renderer(Window* window, PixelFormat pf = PixelFormat::A8R8G8B8);

  bool init();
  void setSize(uint32_t cx, uint32_t cy);

  void drawScene(const Camera& camera);
  void flip();
  void clear();

  void addSpriteRenderBlock(RenderBlockSprite3d renderBlock);

  glm::vec3 cameraPos{1.f};
  glm::vec3 cameraFront{1.f};
  glm::vec3 cameraUp{1.f};
  float cameraSpeed{1.05f};

 private:
  void drawSurfaces();
  void drawSprites(const Camera& camera);
  void drawGround(const Camera& camera);

  void clearRenderLists();

 private:
  Window* window_{nullptr};

  PixelFormat pf_;

  uint32_t width_{0};
  uint32_t height_{0};

  uint32_t frameCount_{0};
  uint32_t frameTick_{0};

  uint32_t halfWidth_;
  uint32_t halfHeight_;
  float aspectRatio_;
  float hpc_;
  float vpc_;
  float hratio_;
  float vratio_;
  float xoffset_;
  float yoffset_;
  float screenXFactor_;
  float screenYFactor_;
  uint32_t clearColor{0xFF000000};

  glm::mat4 projectionMatrix_;
  glm::mat4 projectionMatrix2d_;

  GlShader vertexShader_;
  GlShader fragmentShader_;
  GlProgram groundProgram_{};
  GlProgram surfaceProgram_{};
  GlProgram spriteProgram_{};
  GlVBO myVbo_;
  GlVBO spriteVbo_;
  GlVBO surfaceVbo_;

  minerva::files::BmpResource groundTexture_;
  minerva::files::BmpResource charInfoTexture_;

  std::vector<RenderBlockSprite3d> spriteRenderList_;

  decltype(std::chrono::high_resolution_clock::now()) startTime_;
};

}  // namespace minerva::render

#endif /* MINERVA_CORE_WINDOW_HPP_ */
