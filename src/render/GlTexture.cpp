#include "render/GlTexture.hpp"

GlTexture::GlTexture() {
  glGenTextures(1, &textureId_);
}

GlTexture::~GlTexture() {
  if (textureId_ != 0) {
    glDeleteTextures(1, &textureId_);
  }
}

void GlTexture::bind(GLenum target) {
  glBindTexture(target, textureId_);
  bindedTarget_ = target;
}

void GlTexture::unbind() {
  if (bindedTarget_ != 0) {
    glBindTexture(bindedTarget_, 0);
    bindedTarget_ = 0;
  }
}

GLuint GlTexture::getTextureId() const {
  return textureId_;
}
