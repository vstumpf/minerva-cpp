#include "game_objects/RenderObject.hpp"

#include "common/debug.hpp"
#include "common/globals.hpp"
#include "render/Renderer.hpp"

namespace minerva::render {

RenderObject::RenderObject() : pos_() {
  spriteResource_ = minerva::globals::gResourceManager
                        ->getResource<minerva::files::BmpResource>(
                            "assets/sprites/growlithe.bmp");
  surface_.updateSprite(0, 0, spriteResource_->getWidth(),
                        spriteResource_->getHeight(), spriteResource_.get());
}

void RenderObject::render(const Camera& view) {
  RenderBlockSprite3d render_block{};

  render_block.surface_ = &surface_;
  render_block.position_ = pos_;
  render_block.offset_ = {0 / 35.f, (0 / 35.f) - 0.5f};
  render_block.size_ = {surface_.getWidth() / 35.f,
                        surface_.getHeight() / 35.f};
  render_block.color_[0] = 1.f;
  render_block.color_[1] = 1.f;
  render_block.color_[2] = 1.f;
  render_block.color_[3] = 1.f;

  minerva::globals::gRenderer->addSpriteRenderBlock(std::move(render_block));
}

void RenderObject::setPos(glm::vec3 position) {
  pos_ = std::move(position);
}

const glm::vec3& RenderObject::getPos() const {
  return pos_;
}

}  // namespace minerva::render