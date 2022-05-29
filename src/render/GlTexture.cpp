#include "render/GlTexture.hpp"

GlTexture::GlTexture() : binded_target_(0) { glGenTextures(1, &texture_id_); }

GlTexture::~GlTexture() {
  if (texture_id_ != 0) {
    glDeleteTextures(1, &texture_id_);
  }
}

void GlTexture::bind(GLenum target) {
  glBindTexture(target, texture_id_);
  binded_target_ = target;
}

void GlTexture::unbind() {
  if (binded_target_ != 0) {
    glBindTexture(binded_target_, 0);
    binded_target_ = 0;
  }
}

GLuint GlTexture::texture_id() const { return texture_id_; }
